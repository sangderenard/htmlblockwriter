#ifdef __cplusplus
extern "C" {
#endif


struct FunctionSet DoubleVoidFunctionSet;

char updateDoubleVoid(struct ManagedDoubleVoid * const me){
	int firstTime = 0;
	if(me->previousLength == 0){
		firstTime = 1;
	}
	
	long requiredLength;
	size_t requiredSize;
	
	struct timeval now;
	gettimeofday(&now, NULL);
	int urgency = me->needUpdate;
	int frequencyModifier = 1;
	int wait = (now.tv_usec - me->timeSinceUpdated.tv_usec);
	int cliffDistance = me->maxLength - me->length;
	if( cliffDistance < 1 ){
		frequencyModifier = 10;
		++(me->hitTheCliffCount);
		for( int i = 0; i < me->hitTheCliffCount; ++i ){
			frequencyModifier = frequencyModifier * 2;
		}

	}else{
		if( wait < 0 ){ 
			wait = 1001;
		}else if( wait > 5000 ){
			wait = 5001;
		}
		else if( wait < 1000 && firstTime == 0 ){

			if( wait < 100 ){
				frequencyModifier = 10;
			}else{
				frequencyModifier = 1 + floor((me->resizeCount + 1) / (wait / 1000.0));
			}
		}
		
		frequencyModifier = (1 + floor(frequencyModifier * ( (1 + urgency) / 1.3 )));
	}
	
	if(verbosity > 2 || verbosity > 1 && frequencyModifier > 1){
		printf("the modifier is set to %i based on wait %i and distance to cliff %i\n", frequencyModifier, wait, me->maxLength - me->length);
	}

	switch( me->temperment ){
		case DOUBLEVOIDCONSERVATIVE:
			requiredLength = frequencyModifier * me->length + DOUBLEVOIDMINIMUMBUFFER;
			if(verbosity > 2){
				printf("%i\n", (int)requiredLength);
				printf("%i\n", frequencyModifier);
				printf("%i\n", me->length);
				
				printf("%i, i, %i\n\n\n", (int)requiredLength, frequencyModifier, me->length);
			}
			requiredSize = ( requiredLength * sizeof(void *) );
			
			if( (1+urgency) * requiredSize >= me->size ){
				
				volatile void ** newSelf = (volatile void **)malloc( requiredSize );
				
				if( verbosity > 1 ||  verbosity > 0 && me->length > 1 ){
					printf("resizing to %i, because length is %i and maxlength is %i\n", requiredLength, me->length, (int)me->maxLength );
				}
				
				for(int i = 0; i < me->previousLength; i++){
					if(verbosity > 2){
						printf("I'm copying %i with value %p", i, (me->self)[i]);
					}
					newSelf[i] = (me->self)[i];
				}
				
				free(me->self);
				
				/* can everything stop interrupting me for long enough 
				 * that I can get a hold of wtf needs fixing here */
				
				for(int j = me->length; j < requiredLength; j++){
					newSelf[j] = NULL; /*(volatile void *)malloc(sizeof(void**));*/
				}
			
				me->maxLength = requiredLength;
				me->size = requiredSize;
				
				me->self = newSelf;
			}else{
				printf("request rejected, %i no larger than %i to justify %i\n", (int)((1+(urgency)) * requiredSize), (int)me->size, (int)requiredSize ); 
			}
	}
	
	gettimeofday((timeval *)&(me->timeSinceUpdated), NULL);
	me->needUpdate = 0;
	
	return 0;
}

/* this function, like any initialization, sets the default values in the struct so that
 * they don't have to be manually instantiated each time an array is to be used*/

volatile void * initializeDoubleVoid(struct ManagedDoubleVoid * me, const int * const bufferLength, struct ThreadManagerCache * theCache ){
		me->func = &DoubleVoidFunctionSet;
		me->theCache = theCache;
		int initialLength = 1;
		if(!(bufferLength == NULL)){
			initialLength = *bufferLength;
		}
		DoubleVoidThreadManagerHandshake( me, theCache );
		
		DoubleVoidKnock( me );
		
		me->resizeCount = 0;
		gettimeofday((timeval *)&(me->timeSinceUpdated), NULL);
		me->deleteBehavior = -1;
		me->needUpdate = .1;
		me->size = sizeof(void *)*initialLength;
		me->maxLength = initialLength;
		me->hitTheCliffCount = 0;
		me->length = 0;
		me->method = DOUBLEVOIDLINEAR;
		me->temperment = DOUBLEVOIDCONSERVATIVE;
		me->self = (volatile void**)malloc(sizeof(void*)*initialLength);
		
		if(verbosity == 1){
			printf("created array data at %p\n", me->self);
		}
		
		DoubleVoidRelease( me );
		
		return me->self;
}


int DoubleVoidRelease(struct ManagedDoubleVoid * const me){
	
	if(verbosity > 4){
		printf("doublevoidKnock unlock %p\n", me->myThreadControlLock);
	}
	pthread_mutex_unlock(me->myThreadControlLock);
}

int DoubleVoidKnock(struct ManagedDoubleVoid * const me){
	generalKnock( me->myThreadControlLock );
	return 1;
}


char DoubleVoidPush(void * self, void * value){
	struct ManagedDoubleVoid * me = (struct ManagedDoubleVoid *)self;
	
	/*printf("I'm putting %p at index %i\n", value, me->length);*/
	volatile void ** storageLocation = (volatile void **)doubleVoid( me, me->length );
	*storageLocation = (volatile void *)value;
	/*printf("%p stores %p\n", storageLocation, *storageLocation );*/
	
}

void * DoubleVoidPop(void * self, const int count){
	struct ManagedDoubleVoid * me = (struct ManagedDoubleVoid *)self;
	void ** returnValues;
	void * returnValue;
	if(count > 1){
		returnValues = (void **)(malloc(sizeof(void *) * count));
	}
	
	
	me->needUpdate = 0;
	if(count > 1){
		for( int i = 0; i < count; ++i ){ 
			/*printf("I'm looking at index %i", me->length-1 );*/
			volatile void ** returnLocation = (volatile void **)doubleVoid( me, me->length-1 );
			returnValues[i] = (void *)*returnLocation;
			/*free((void *)(me->self[i]));*/
			*returnLocation = NULL;
			me->previousLength = me->length;
			--(me->length);
		}
	}else{
		volatile void ** returnLocation = (volatile void **)doubleVoid( me, me->length-1 );
		returnValue = (void *)*returnLocation;
		*returnLocation = NULL;
		me->previousLength = me->length;
		--(me->length);
	}
	
	if(count > 1){
		return (void *)returnValues;
	}else{
		return returnValue;
	}
}

void * DoubleVoidGet(void * self, const int index){
	struct ManagedDoubleVoid * me = (struct ManagedDoubleVoid *)self;
	
	
	volatile void ** returnLocation = (volatile void **)doubleVoid( me, index );
	void * returnValue = (void *)*returnLocation;
	
	
	return returnValue;
}

char DoubleVoidSet(void * self, const int index, void * input){
	struct ManagedDoubleVoid * me = (struct ManagedDoubleVoid *)self;
	
	
	
	volatile void ** storageLocation = (volatile void **)doubleVoid( me, index );
	if( me->deleteBehavior == -1 && *storageLocation != NULL ){
		free( (void *)*storageLocation );
	}
	*storageLocation = (volatile void *)input;
	
	
}

char DoubleVoidShift(void * self, void * input){
	/*
	 * do I move the whole array, which is madness
	 * or do I offset the index, which is complex
	 * or do I map the indexes, which is wasteful
	 * 
	 * moving the whole array is simple. just make a new one
	 * and move the old one, but it requires twice the memory
	 * 
	 * offsetting the index isn't immediately intuitively clear to me
	 * 
	 * the only time the index matters is when these calls are made
	 * if I intervene at the right point, the offset won't matter
	 * to any of the more complicated low level functions
	 * 
	 * but the length will need to be calculated properly
	 * without shrinking the array and cutting off the end
	 */
}
void * DoubleVoidUnshift(void * self, const int count){
	
}

/* data structures which have the standard function set are expected
 * to have a function set pointer, which will need instantiation
 * as a global variable to avoid having to make copies and carry them
 * around
 * 
 * 
 * 
 * char (*splice)(void *, const int, const int, void *, const int, const int);
 * 
 * */
 
char DoubleVoidSplice(void * self, const int beginOnIndex, const int entriesToDelete, 
						void * other, const int otherBeginOnIndex, const int otherEntriesToInsert ){
	struct ManagedDoubleVoid * me = (struct ManagedDoubleVoid *)self;
	/*printf("splice on %p, at %i, for %i entries\n", me, beginOnIndex, entriesToDelete);*/
	size_t newSize;
	int newMaxLength;
	
	int newLength = me->length - entriesToDelete + otherEntriesToInsert;
	
	
	volatile void ** newSelf;
	
	if( newLength > me->maxLength ){
		newMaxLength = me->maxLength - entriesToDelete + otherEntriesToInsert;
		newSize = me->size - (entriesToDelete * sizeof(void *) ) + (otherEntriesToInsert * sizeof(void *) );
		newSelf = (volatile void **)malloc(newSize);
	}else{
		newSelf = me->self;
	}
	
	int i;
	if( newSelf != me->self ){
		for(i = 0; i < beginOnIndex; ++i){
			newSelf[i] = me->self[i];
		}
	}else{
		i = beginOnIndex;
	}
	int j = i;
	for(; i < beginOnIndex + entriesToDelete; ++i){
		if(me->deleteBehavior == -1){
			/*printf("freeing entry %p, %i of %i\n", (me->self)[i], i, beginOnIndex+entriesToDelete);*/
			free((void *)(me->self[i]));
		}else{
			(me->self[i]) = NULL;
		}
	}
	for(int k = 0; j < beginOnIndex + otherEntriesToInsert; ++j, ++k){
		newSelf[j] = ((struct ManagedDoubleVoid *)other)->self[otherBeginOnIndex+k];
	}
	if( newSelf != me->self ){
		for(; i < me->length; ++i, ++j){
			newSelf[j] = me->self[i];
		}
		free(me->self);
		me->maxLength = newMaxLength;
		me->size = newSize;
		me->self = newSelf;
		for(; i < newMaxLength; ++i){
			(me->self)[i] = NULL;
		}
	}

	me->length = newLength;

}

void defineDoubleVoidFunctions(){
	DoubleVoidFunctionSet.get = &DoubleVoidGet;
	DoubleVoidFunctionSet.set = &DoubleVoidSet;
		
	DoubleVoidFunctionSet.push = &DoubleVoidPush;
	DoubleVoidFunctionSet.pop = &DoubleVoidPop;
	DoubleVoidFunctionSet.shift = &DoubleVoidShift;
	DoubleVoidFunctionSet.unshift = &DoubleVoidUnshift;

	DoubleVoidFunctionSet.splice = &DoubleVoidSplice;
}


/* Garbage collection on this project is getting out of hand and needs
 * addressing soon. The basic data structures are working, so 
 * proper management of allocated memory should probably be addressed
 * before adding new proposed functions and structs.
 * 
 * */

void DoubleVoidDestruct(struct ManagedDoubleVoid * const me){

	if( me->self != NULL ){
		/*free(me->myThreadControlLock);
		*free(me->myThreadControlPostbox->contents);
		*free(me->myThreadControlPostbox);
		*/
		
		pthread_mutex_lock( me->myPostbox->mailboxKey );
		pthread_mutex_lock( me->myThreadControlLock );
		me->myThreadControlPostbox->contents->type = MEMOKEYRETURN;
		me->myThreadControlPostbox->contents->memoMutex = me->myThreadControlPostbox->mailboxKey;
		me->myPostbox->contents->type = MEMOKEYRETURN;
		me->myPostbox->contents->memoMutex = me->myPostbox->mailboxKey;
		me->myThreadControlPostbox->contents->contents = me->myThreadControlPostbox;
		me->myPostbox->contents->contents = me->myPostbox;


		free(me->self);
		
		printf("returning thread control key %p\n", me->myThreadControlLock);
		postMemo( me->myThreadControlPostbox->contents, me->theCache );
		printf("returning postbox key %p\n", me->myPostbox->mailboxKey);	
		postMemo( me->myPostbox->contents, me->theCache );
		pthread_mutex_unlock( me->myThreadControlLock );
		pthread_mutex_unlock( me->myPostbox->mailboxKey );
		
		
		
	}
}

void DoubleVoidDestructRecursive(struct ManagedDoubleVoid * const me){
	/*printf("destroying a doublevoid");*/
	me->deleteBehavior = -1;
	me->func->splice( me, 0, me->length, NULL, 0, 0 );
	DoubleVoidDestruct( me );
}

/* doubleVoid is the low level function for obtaining indexes, and 
 * implicitly triggering udpates of memory allocation or signaling
 * the need for such, using updateDoubleVoid and scheduleupdateetc...*/

volatile void * doubleVoid(struct ManagedDoubleVoid * const me, const int i){
	
	
	
	if(verbosity > 1){
		printf("entering doublevoid looking for index %i out of %i\n", i, me->length);
	}
	if( i < me->length ){
		volatile void * returnValue = (volatile void*)(&((me->self)[i]));
		if(verbosity > 1){
			printf("%p is the location inside the array.\n", &(me->self[i]));
			printf("returning %p within allocation\n", returnValue);
		}
		return returnValue;
	}else if( i < me->maxLength ){
		me->previousLength = me->length;
		me->length  = i + 1;
		
		
		volatile void * returnValue = (volatile void*)(&((me->self)[i]));
		if(verbosity > 1){
			printf("%p is the location inside the array.\n", &(me->self[i]));
			printf("returning %p within allocation\n", returnValue);
		}
		return returnValue;
	}else{
		me->previousLength = me->length;
		me->length = i + 1;
		updateDoubleVoid(me);
	
		
		volatile void * returnValue = (volatile void*)(&((me->self)[i]));
		if(verbosity > 1){
			printf("%p is the location inside the array.\n", &(me->self[i]));
			printf("returning %p after new allocation\n", returnValue);
		}
		return returnValue;
	}
}

ThreadManagerPostOfficeBox * DoubleVoidThreadManagerHandshake( struct ManagedDoubleVoid * me, struct ThreadManagerCache * threadManagerCache ){
	
	if(verbosity > 1){
		printf("doublevoid handshake being tied to a cache\n");
	}
	me->myPostbox = simpleKeyRequest( threadManagerCache, NULL );
	if(verbosity > 1){
		printf("doublevoid handshake request key request on memo %p\n", me->myPostbox);
	}
	pthread_mutex_lock( me->myPostbox->mailboxKey );
	if(verbosity > 1){
		printf("doublevoid handshake locked %p\n", me->myPostbox->mailboxKey);
	}
	

	
	
	me->myThreadControlPostbox = simpleKeyRequest( threadManagerCache, NULL);
	me->myThreadControlLock = me->myThreadControlPostbox->mailboxKey;
	

	if(verbosity > 1){
		printf("doublevoid handshake I've set my control lock to %p\n", me->myThreadControlPostbox->mailboxKey);
	}
	pthread_mutex_unlock( me->myPostbox->mailboxKey );
	if(verbosity > 1){
		printf("doublevoid handshake I've unlocked postbox %p using key %p\n", me->myPostbox, me->myPostbox->mailboxKey);
	}
}



#ifdef __cplusplus
}
#endif
