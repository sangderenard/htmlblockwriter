#ifdef __cplusplus
extern "C" {
#endif

struct RollingCharBuffer * initializeRollingCharBuffer( long size, int * framerate ){
	struct RollingCharBuffer * newCharBuffer = (struct RollingCharBuffer *)malloc(sizeof(struct RollingCharBuffer));
	
	pthread_mutex_init( &(newCharBuffer->bufferKey), NULL );
	pthread_mutex_lock( &(newCharBuffer->bufferKey) );
	newCharBuffer->buffer = (char **)malloc(sizeof(char *) * size);
	newCharBuffer->size = size;
	newCharBuffer->close = 0;
	newCharBuffer->currentReadIndex = 0;
	newCharBuffer->currentWriteIndex = 1;
	if( framerate == NULL ){
		newCharBuffer->framerate = 1;
	}
	for(int i = 0; i < size; ++i){
		newCharBuffer->buffer[i] = NULL;
	}
	
	pthread_mutex_unlock( &(newCharBuffer->bufferKey) );
	return newCharBuffer;
}

/* 
 * 
 * cache rolls over when overfull, read happens at oldest location, gets
 * swept along with write, and the printer thread will be picking things
 * up to feed to the console
 * 
 * 
 * */
void RollingCharBufferClose( struct RollingCharBuffer * buffer ){
	pthread_mutex_lock( &(buffer->bufferKey) );
	buffer->close = 1;
	pthread_mutex_unlock( &(buffer->bufferKey) );
}

char * readFromBuffer( struct RollingCharBuffer * buffer ){
	char * bufferLine = (buffer->buffer)[buffer->currentReadIndex];
	/*printf("read%i,%s\nwrite%i,%s", buffer->currentReadIndex, (buffer->buffer)[buffer->currentReadIndex],
	*		buffer->currentWriteIndex, (buffer->buffer)[buffer->currentWriteIndex]);
	*/
	char * returnValue = NULL;
	if( bufferLine != NULL ){
		returnValue = stringCopy( bufferLine );
	}
	++(buffer->currentReadIndex);
		if(buffer->currentReadIndex == buffer->size){
			buffer->currentReadIndex = 0;
		}
	return returnValue;
}

void writeToCharBuffer( struct RollingCharBuffer * buffer, char * input ){
	pthread_mutex_lock( &(buffer->bufferKey) );
	if( buffer->currentWriteIndex == buffer->size ){
		buffer->currentWriteIndex = 0;
	}
	
	if( buffer->currentReadIndex == buffer->currentWriteIndex ){
		++(buffer->currentReadIndex);
		if(buffer->currentReadIndex == buffer->size){
			buffer->currentReadIndex = 0;
		}
	}
	if( (buffer->buffer)[buffer->currentWriteIndex] != NULL ){
		free( (buffer->buffer)[buffer->currentWriteIndex] );
	}
	(buffer->buffer)[buffer->currentWriteIndex] = input;
	++(buffer->currentWriteIndex);
	pthread_mutex_unlock( &(buffer->bufferKey) );
}

#ifdef __cplusplus
}
#endif
