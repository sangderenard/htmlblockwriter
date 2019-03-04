#ifdef __cplusplus
extern "C" {
#endif

struct FunctionSet DoubleVoidFunctionSet;

char scheduleUpdateDoubleVoid(struct ManagedDoubleVoid * const me){
	int verbosity = 0;
	
	float workerThresholdAdjustment = 1.4;
	
	me->needUpdate = (((float)(me->length) / (float)(me->maxLength))) + workerThresholdAdjustment;
	
	
	if( verbosity == 1 && me->length > 1 && me->needUpdate > 1.8 ){
		printf("urgency at %f, length %i and max length %i\n",me->needUpdate, me->length, me->maxLength);
	}
	
}

void DoubleVoidNegotiateAdditionalThread( struct ManagedDoubleVoid * me ){
	int verbose = 0;
	/* create a memo, send it, ask for permission to start a thread  */
	if(verbose > 0){
		printf("the negotiator is securing a mailbox\n");
	}
	
	
	/* this section pairs with other modified sections marked with comments
	 * as a shot in the dark being put together */
	
	/*struct ThreadManagerPostOfficeBox * threadRequestMailbox = getAPostBox( NULL );*/
	struct ThreadManagerPostOfficeBox * threadRequestMailbox = me->myPostbox;
	
	
	/* end of modification area */
	
	
	if(verbose > 0){
		printf("dv neg:using postbox %p with key %p.\n", me->myPostbox, threadRequestMailbox->mailboxKey);
	}
	pthread_mutex_lock( threadRequestMailbox->mailboxKey );
	if(verbose > 0){
		printf("dv neg: locked %p using key %p\n", threadRequestMailbox, threadRequestMailbox->mailboxKey);
	}
	threadRequestMailbox->contents->type = MEMOCREATETHREADREQUEST;
	threadRequestMailbox->contents->origin = getCallerOnTheLine();
	threadRequestMailbox->contents->destination = canITalkToYourManagerPlease( me->theCache );
	threadRequestMailbox->contents->sender = threadRequestMailbox;
	threadRequestMailbox->contents->recipient = (void *)(me->theCache->queuePage);
	threadRequestMailbox->contents->memoMutex = threadRequestMailbox->mailboxKey;
	if(verbose > 0){
		printf("dv neg: postmemo(%p) lock %p type %i\n", threadRequestMailbox->contents, threadRequestMailbox->mailboxKey, threadRequestMailbox->contents->type);
	}
	postMemo( threadRequestMailbox->contents, me->theCache );
	if(verbose > 0){
		printf("the negotiator has posted.\n");
	}
	pthread_mutex_unlock( threadRequestMailbox->mailboxKey );
	if(verbose > 0){
		printf("dv neg: unlocked key %p.\n", threadRequestMailbox->mailboxKey);
	}

	int keepWaiting = 1;
	while( keepWaiting ){
		++keepWaiting;
		if( pthread_mutex_trylock( threadRequestMailbox->mailboxKey ) ){
			usleep(100);
			if(verbose > 0){
				printf("dv neg: can't get into mailbox %p with lock %p %i\r", threadRequestMailbox, threadRequestMailbox->mailboxKey, keepWaiting);
			}
			continue;
		}
		if(verbose > 0){
			printf("dv neg: I've locked mutex %p\n", threadRequestMailbox->mailboxKey );
		}
		if( threadRequestMailbox->contents->type == MEMOCREATETHREADREQUEST ){
			if(verbose > 0){
				printf("dv neg: I've unlocked mutex %p\n", threadRequestMailbox->mailboxKey );
				printf("dv neg: there is no response at threadRequestMailbox %p\n", threadRequestMailbox->contents);
				printf("dv neg: I'm seeing type value %i at location %p\n", threadRequestMailbox->contents->type, &(threadRequestMailbox->contents->type));
			}
			pthread_mutex_unlock( threadRequestMailbox->mailboxKey );
			usleep(100);
		}else if( threadRequestMailbox->contents->type == MEMOCREATETHREADRESPONSE ){
			if(verbose > 0){
				printf("dv neg: recieved sreponse %i\n", threadRequestMailbox->contents->type);
			}
			
			const int response = *((int*)(threadRequestMailbox->contents->contents));
			
			if( response > 0 ){
							
				keepWaiting = 1;
				
				while( keepWaiting ){
					keepWaiting++;
					
					const int threadStartConfirmation =
						*((int*)(threadRequestMailbox->contents->contents));
					if( threadStartConfirmation == 0 ){
						if(verbose > 0){
							printf("recieved thread denial\n");
						}
						pthread_mutex_unlock( threadRequestMailbox->mailboxKey );
						keepWaiting = 0;
					}else{
						if(verbose > 0){
							printf("thread confirmation code: %i", threadStartConfirmation);
						}
						pthread_create(&(me->watcher), NULL, doubleVoidWorker, (void *)me);	
						pthread_mutex_unlock( threadRequestMailbox->mailboxKey );
						pthread_mutex_unlock( me->myThreadControlLock );
						int timetostop = 0;
						while( !timetostop ){
							while( pthread_mutex_trylock(me->myThreadControlLock)){
								usleep(100);
							}
							if(me->watched == 0){
								pthread_mutex_unlock(me->myThreadControlLock);
							}else{
								timetostop = 1;
								
							}
						}
						keepWaiting = 0;
					}
				}
			}else{
				keepWaiting = 0;
			}
		}
		
	}

}


char updateDoubleVoid(struct ManagedDoubleVoid * const me){
	int verbosity = 0;
	/*printf("inside the updator\n");*/
	int setWatcher;
	int firstTime = 0;
	if(me->previousLength == 0){
		firstTime = 1;
	}
	
	setWatcher = 0;
	
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
		if( me->watched == 0 ){
			setWatcher = 1;
		}
	}else if(me->parentalUrging > me->needUpdate){
		
		frequencyModifier = me->parentalUrging / (me->needUpdate+1);  
		
	}else{
		if( wait < 0 ){ 
			wait = 1001;
		}else if( wait > 5000 ){
			wait = 5001;
		}
		
		if( urgency > 10 ){
			urgency = 10;
			if( me->watched == 0){
				if(verbosity > 1){
					printf("urgency over 10, deploying worker.\n");
				}
				setWatcher = 1;
			}
		}
		
		if( (me->maxLength - me->length) < 10 && me->length > 20 ){
			if( me->watched == 0){
				if(verbosity > 1){
					printf("running out of space with more than 20 items, deploying worker.\n");
				}
				setWatcher = 1;
			}
			frequencyModifier = 10;
		}else if( wait < 1000 && firstTime == 0 ){
			if( me->watched == 0){
				if(verbosity == 2){
					printf("no wait time, deploying worker.\n");
				}
				setWatcher = 1;
			}
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
				printf("%i\n", requiredLength);
				printf("%i\n", frequencyModifier);
				printf("%i\n", me->length);
				
				printf("%i, %i, %i\n\n\n", requiredLength, frequencyModifier, me->length);
			}
			requiredSize = ( requiredLength * sizeof(void *) );
			
			if( (1+urgency) * requiredSize >= me->size ){
				
				volatile void ** newSelf = (volatile void **)malloc( requiredSize );
				
				if( 1 || verbosity > 1 ||  verbosity > 0 && me->length > 1 ){
					printf("resizing to %i, because length is %i and maxlength is %i\n", requiredLength, me->length, me->maxLength );
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
				printf("request rejected, %i no larger than %i to justify %i\n", ((1+(urgency)) * requiredSize), me->size, requiredSize ); 
			}
	}
	
	gettimeofday((timeval *)&(me->timeSinceUpdated), NULL);
	if( !firstTime && setWatcher == 1 && me->watched == 0 ){
		if(verbosity == 2){
			printf("deploying worker\n");
		}
		
		DoubleVoidNegotiateAdditionalThread( me );
		setWatcher = 0;
	}
	me->needUpdate = 0;
	
	return 0;
}


	

volatile void * initializeDoubleVoid(struct ManagedDoubleVoid * me, const int * const bufferLength){
		me->func = &DoubleVoidFunctionSet;
		int initialLength = 1;
		if(!(bufferLength == NULL)){
			initialLength = *bufferLength;
		}
		me->resizeCount = 0;
		gettimeofday((timeval *)&(me->timeSinceUpdated), NULL);
		me->watched = 0;
		me->needUpdate = .1;
		me->size = sizeof(void *)*initialLength;
		me->maxLength = initialLength;
		me->hitTheCliffCount = 0;
		me->length = 0;
		me->method = DOUBLEVOIDLINEAR;
		me->temperment = DOUBLEVOIDCONSERVATIVE;
		me->self = (volatile void**)malloc(sizeof(void*)*initialLength);
		int verbosity = 0;
		if(verbosity == 1){
			printf("created array data at %p\n", me->self);
		}
		return me->self;
}

int DoubleVoidRelease(struct ManagedDoubleVoid * const me){
	int verbose = 0;
	if(verbose > 0){
		printf("doublevoidKnock unlock %p\n", me->myThreadControlLock);
	}
	pthread_mutex_unlock(me->myThreadControlLock);
}

int DoubleVoidKnock(struct ManagedDoubleVoid * const me){
	int verbose = 0;
	int sleepTimer = 0;
	
	while( pthread_mutex_trylock(me->myThreadControlLock)  ){
		if(verbose > 1){
			printf("doublevoidknock is knocking\n");
		}
		if(sleepTimer > 100){
			usleep(100);
		}else{
			usleep(++sleepTimer);
		}
	} 
	if(verbose > 0){
		printf("doublevoidknock lock %p\n", me->myThreadControlLock);
	}
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


void defineDoubleVoidFunctions(){
	DoubleVoidFunctionSet.get = &DoubleVoidGet;
	DoubleVoidFunctionSet.set = &DoubleVoidSet;
		
	DoubleVoidFunctionSet.push = &DoubleVoidPush;
	DoubleVoidFunctionSet.pop = &DoubleVoidPop;
	DoubleVoidFunctionSet.shift = &DoubleVoidShift;
	DoubleVoidFunctionSet.unshift = &DoubleVoidUnshift;

}

void DoubleVoidDestruct(struct ManagedDoubleVoid * const me){
	for(int i = me->length; i < me->maxLength; ++i){
		free((void *)(me->self)[i]);
	}
	free(me->self);
}

void DoubleVoidDestructRecursive(struct ManagedDoubleVoid * const me){
	int verbosity = 0;
	for(int i = 0; i < me->length; ++i){
		if(verbosity == 1){
			printf("destroying allocation %p\n", me->self[i]);
		}
		free((void *)(me->self[i]));
	}
	if(verbosity == 1){
		printf("destroying the array allocation %p\n", me->self);
	}
	DoubleVoidDestruct( me );
}

volatile void * doubleVoid(struct ManagedDoubleVoid * const me, const int i){
	
	int verbosity = 0;
	if( me->watched != 0 ){
		
		int callsHome = 0;
		while( callsHome < 20 && pthread_mutex_trylock( me->myPostbox->mailboxKey ) ){
			++callsHome;
		}
		
		if( callsHome < 20 ){
			
			float parentalEncouragement = *(float *)me->myPostbox->contents->contents;
			
			if( parentalEncouragement > me->needUpdate ){
				if(verbosity > 0){
					printf("my parent wants to encourage me: %i\n", parentalEncouragement );
				}
			
				me->parentalUrging = parentalEncouragement;
				me->previousLength = me->length;
				updateDoubleVoid(me);
				scheduleUpdateDoubleVoid(me);
				me->myPostbox->contents->contents = &me->needUpdate;
			}
			
			pthread_mutex_unlock( me->myPostbox->mailboxKey );
		}
	}
	
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
		scheduleUpdateDoubleVoid(me);
		
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

void *doubleVoidWorker(void * requestedChild){
	int verbosity = 0;
	int myId = rand();
	float testParentalBoost = 0;
	float previousNeed = 0;
	while( pthread_mutex_trylock( ((struct ManagedDoubleVoid *)requestedChild)->myThreadControlLock ) ){
		if(verbosity > 2){
			printf("can't stop the clock");
		}
		usleep(100);
	}
	
	struct ManagedDoubleVoid * myChild;
	myChild = (struct ManagedDoubleVoid *)requestedChild;
	if( myChild->watched == 0 && myChild->needUpdate > 1 ){
		testParentalBoost = myChild->needUpdate;
		previousNeed = testParentalBoost;

		
		pthread_mutex_lock( myChild->myPostbox->mailboxKey );
		myChild->myPostbox->contents->contents = &testParentalBoost;
		pthread_mutex_unlock( myChild->myPostbox->mailboxKey );
		
		myChild->watched = 1;

		DoubleVoidRelease( myChild );


		if(verbosity > 1){
			printf("\nworker here\n\n");
		}
		int keepWatching = 1;
		float needUpdateDrift = 0;
		
		while(keepWatching < 100 ){
			usleep( (keepWatching)*(keepWatching) * 333 );
	
	
			DoubleVoidKnock( myChild );
			if( myChild->needUpdate > 1.5){
				
				pthread_mutex_lock( myChild->myPostbox->mailboxKey );
				/*updateDoubleVoid( myChild );*/
				needUpdateDrift = ( myChild->needUpdate - previousNeed );
				previousNeed = myChild->needUpdate;
				if(needUpdateDrift <= 0){
					pthread_mutex_unlock( myChild->myPostbox->mailboxKey );
					DoubleVoidRelease( myChild );
					++keepWatching;
					continue;
				}

				if(verbosity > 1){
					printf("looking into my child, see urgency:%f drift: %f\n", myChild->needUpdate, needUpdateDrift);
					printf("%i,%i\n", myId, keepWatching);
				}

				
				if(needUpdateDrift > .0002){
				
					testParentalBoost = myChild->needUpdate * testParentalBoost;
					
					myChild->myPostbox->contents->contents = &testParentalBoost;
					
				
					if(verbosity > 1){
						printf("setting a parental boost of %f based on drift %f\n", testParentalBoost, needUpdateDrift);
					}
				}
				
				pthread_mutex_unlock( myChild->myPostbox->mailboxKey );
				
				
				DoubleVoidRelease( myChild );
				
			}else if( myChild->needUpdate < 1 ){
				DoubleVoidRelease( myChild );
				keepWatching = 100;
			}else{
				DoubleVoidRelease( myChild );
				++keepWatching;
			}
		}
		if(verbosity == 2){
			printf("leaving my child\n");
		}
		DoubleVoidKnock( myChild );
		myChild->watched = 0;
		DoubleVoidRelease( myChild );
		
	}else{
		DoubleVoidRelease( myChild );
	}
	return NULL;
}


ThreadManagerPostOfficeBox * DoubleVoidThreadManagerHandshake( struct ManagedDoubleVoid * me, struct ThreadManagerCache * threadManagerCache ){
	int verbosity = 0;
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
	
	/* 
	 * on a hunch, this will be changed to a new, different key.
	 * 
	 * */
		
	/*me->myThreadControlLock = me->myPostbox->mailboxKey;*/
	
	
	me->myThreadControlPostbox = simpleKeyRequest( threadManagerCache, NULL);
	me->myThreadControlLock = me->myThreadControlPostbox->mailboxKey;
	
	/* end of modified section */
	
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
