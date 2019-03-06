
#ifdef __cplusplus
extern "C" {
#endif



void * printScreen( void * arg ){
	struct RollingCharBuffer * screen = (RollingCharBuffer *)arg;

	while( screen != NULL ){
		char * printLine = readFromBuffer( screen );
		if( printLine != NULL ){
			printf("%s", printLine);
		}
		usleep( screen->framerate );
		
	}

}

 
#ifdef __cplusplus
}
#endif
