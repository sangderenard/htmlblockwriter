#ifdef __cplusplus
extern "C" {
#endif

struct RollingCharBuffer * initializeRollingCharBuffer( long size, int * framerate ){
	struct RollingCharBuffer * newCharBuffer = (struct RollingCharBuffer *)malloc(sizeof(struct RollingCharBuffer));
	
	pthread_mutex_init( &(newCharBuffer->bufferKey), NULL );
	newCharBuffer->buffer = (char **)malloc(sizeof(char *) * size);
	newCharBuffer->size = size;
	newCharBuffer->currentReadIndex = 0;
	newCharBuffer->currentWriteIndex = 0;
	if( framerate == NULL ){
		newCharBuffer->framerate = 1000;
	}
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


char * readFromBuffer( struct RollingCharBuffer * buffer ){
	pthread_mutex_lock( &(buffer->bufferKey) );
	char * bufferLine = (buffer->buffer)[buffer->currentReadIndex];
	char * returnValue = NULL;
	if( bufferLine != NULL ){
		returnValue = stringCopy( bufferLine );
		++(buffer->currentReadIndex);
		if(buffer->currentReadIndex == buffer->size){
			buffer->currentReadIndex = 0;
		}
	}
	pthread_mutex_unlock( &(buffer->bufferKey) );
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
	pthread_mutex_unlock( &(buffer->bufferKey) );
}

#ifdef __cplusplus
}
#endif
