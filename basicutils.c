#ifdef __cplusplus
extern "C" {
#endif

#include "./basicutils.h"

#include "./strings.c"
#include "./rollingcharbuffer.c"
#include "./printer.c"
#include "./memo.c"

#include "./threadmanager.c"
#include "./keyring.c"

#include "./manageddoublevoid.c"
#include "./linklist.c"



void generalKnock( pthread_mutex_t * const door ){
	int sleepTimer = 0;
	int sleepTime = 0;
	while( pthread_mutex_trylock( door ) ){
		if(sleepTimer > 1000){printf("%p is hanging...", door);};
		if(verbosity > 4){printf("knocking (%p)...\n", door);};
		if(sleepTimer < 1000){++sleepTimer;};
		sleepTime = round((float)(rand() * sleepTimer)/(float)INT_MAX);
		sleepTime = sleepTime * sleepTime;
		usleep(sleepTime);
	} 
	if(verbosity > 3){printf("opened %p\n", door);};
	return;
}

int randomSleep( int maxSleep ){
	int r = rand();
	int sleep = floor(((float)maxSleep*(float)r)/(float)INT_MAX); 
	usleep(sleep);
	return sleep;
}


const char addWithoutDuplicate(const char * const value, char ** array, int * size){
	/*if(*size > 6){
	*	printf("%p %i\n", size, *size);
	*	exit(1);
	*}
	* */
	
	
	int newSize = *size + 1;
	char * oldArray = *array;
	char * newArray = (char *)malloc(newSize);

	for(int i = 0; i < *size; ++i){
		if( oldArray[i] == *value ){
			free(newArray);
			return '\0';
		}
		newArray[i] = oldArray[i];
	}
	newArray[*size] = *value;

/*	free(*array);*/

	*array = newArray;
	*size = newSize;
	
	return '\1';
}

char *packWithChildren( const struct StringTree trunk ) {
	return NULL;
}



#ifdef __cplusplus
}
#endif
