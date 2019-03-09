
#ifdef __cplusplus
extern "C" {
#endif



void * printScreen( void * arg ){
	struct RollingCharBuffer * screen = (RollingCharBuffer *)arg;

	while( screen->close != 1 ){
		char * printLine = readFromBuffer( screen );
		pthread_mutex_unlock( &(screen->bufferKey) );
		if( printLine != NULL ){
			printf("%s", printLine);
		}
		free( printLine );
		
		usleep( screen->framerate );
		if( screen->close != 1 ){
			pthread_mutex_lock( &(screen->bufferKey) );
		}
	}

	pthread_mutex_lock( &(screen->bufferKey) );
	for( int i = 0; i < screen->size; ++i){
		if( screen->buffer[i] != NULL ){
			free( screen->buffer[i] );
		}
	}
	free( screen->buffer );
	pthread_mutex_unlock( &(screen->bufferKey) );
	
}

 
#ifdef __cplusplus
}
#endif
