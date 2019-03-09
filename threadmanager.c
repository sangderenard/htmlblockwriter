#ifdef __cplusplus
extern "C" {
#endif

int ThreadManagerCopyWithVerify(struct memo * memoToCopy, volatile struct memo * locationToAssure){
	simpleMemoCopy( memoToCopy, locationToAssure );
	return checkMemoCopy( *(struct memo *)memoToCopy, *(struct memo *)locationToAssure );
	
}

struct memo * ThreadManagerScan( volatile struct memo * page, int pageSize, char * scanType ){
	
	/* first and last entry for linked list entries */
	if(verbosity > 5){
		printf("ThreadManagerScan starting\n");
	}
	if(page[0].type == MEMOSHUTDOWN){
		return (struct memo *)(&page[0]);
	}
	volatile struct memo * currentPage = page;
	while( currentPage != NULL ){
		for( int i = 1; i < pageSize - 1; ++i ){
			if( currentPage[i].type != 0 ){
				if( verbosity > 1){
					printf("scan: tyepe %i at %p lock %p\n", (int)currentPage[i].type, &(currentPage[i]), currentPage[i].memoMutex);
				}
				
				/* stop putting in code ruining diagnostic
				 * printf calls looking at uninitialized crap
				 * without a check for null
				 **/
				
				
				if( 0 && currentPage[i].memoMutex != NULL ){
					/*printf("%i\n", pthread_mutex_trylock( page[i].memoMutex ));*/
				}
				if( ( currentPage[i].memoMutex == NULL ) || !(pthread_mutex_trylock( currentPage[i].memoMutex )) ){
					if( currentPage[i].memoMutex == NULL ){
						if(verbosity > 0){
							printf("the memo mutex is null\n");
						}
					}
					
					struct memo * returnMemo = (struct memo *)malloc(sizeof(struct memo));
					if(verbosity > 0){
						printf("threadscan is making a blank memo %p to send to the thread manager\n", returnMemo);
					}
					blankMemo( returnMemo, 1 );
					if(verbosity > 1){
						printf("thread scan is making a xerox..\n");
					}
					ThreadManagerCopyWithVerify( (struct memo *)(&(currentPage[i])), returnMemo );
					if(verbosity > 0){
						printf("thread scan: memo %p type %i lock %p generated for manager\n", 
							returnMemo, returnMemo->type, returnMemo->memoMutex); 
					}
					blankMemo( (struct memo *)(&(currentPage[i])), 1);
					if(verbosity > 0){
						printf("thread scan blanked memo %p\n", (struct memo *)(&(currentPage[i])));
					}
					return returnMemo;
				}else{
					if(verbosity > 0){
						printf("the discovered memo %p is still locked with key %p\n", &(currentPage[i]), currentPage[i].memoMutex);
					}
				}
			}
		}
		currentPage = (volatile struct memo *)currentPage[0].recipient;
	}
	
	return NULL;
}
void ThreadManagerBlankPage(volatile struct memo * );
volatile struct memo * ThreadManagerAddPage( volatile struct memo * firstPage ){
	const struct ThreadManagerCache * const theCache = (struct ThreadManagerCache *)(firstPage->contents);
	volatile struct memo * currentPage = (volatile struct memo *)firstPage->sender;

	if( currentPage == NULL ){
		currentPage = (volatile struct memo *)calloc(theCache->memosPerPage, sizeof(struct memo));
		currentPage[0].sender = (void *)firstPage;
		currentPage[0].type = firstPage[0].type;
		currentPage[0].origin = firstPage[0].origin;
		currentPage[0].destination = firstPage[0].destination;
		currentPage[0].recipient = NULL;
		currentPage[0].memoMutex = firstPage[0].memoMutex;
		currentPage[0].contents = firstPage[0].contents;
		firstPage->sender = (void *)currentPage;
		firstPage->recipient = (void *)currentPage;
		ThreadManagerBlankPage( currentPage );
		return currentPage;
		
	}else{
		volatile struct memo * newPage = (volatile struct memo *)calloc(theCache->memosPerPage, sizeof(struct memo));
		newPage[0].type = firstPage[0].type;
		newPage[0].origin = firstPage[0].origin;
		newPage[0].destination = firstPage[0].destination;
		newPage[0].recipient = NULL;
		newPage[0].sender = (void *)firstPage;
		newPage[0].memoMutex = firstPage[0].memoMutex;
		newPage[0].contents = firstPage[0].contents;
		currentPage[theCache->memosPerPage-1].recipient = (void *)newPage;
		currentPage[0].recipient = (void*)newPage;
		ThreadManagerBlankPage( newPage );
		firstPage->sender = (void *)newPage;
		return newPage;
	}
}

volatile struct memo * ThreadManagerEndOfLastPage( volatile struct memo * firstPage ){
printf("setting lock %p\n", firstPage->memoMutex );
	pthread_mutex_lock( firstPage->memoMutex );
	 	
	 const struct ThreadManagerCache * const cacheInfo = (struct ThreadManagerCache *)(firstPage->contents);
	 
	 volatile struct memo * currentPage = firstPage;
	 if(firstPage->sender != NULL){
		 currentPage = (volatile struct memo *)(firstPage->sender);
	 }
	 
	 const int memosPerPage = cacheInfo->memosPerPage;
	 
	 
	 volatile struct memo * memoAddressIWant = NULL;
	int i = memosPerPage - 1;
	 for(; i >= 0; --i ){
		 if( currentPage[i].type != 0 ){

			 memoAddressIWant = &(currentPage[i+1]);
			 break;
		 }
	 }
	 
	 if( i == memosPerPage - 1 ){
		 printf("adding a page");
		 currentPage = ThreadManagerAddPage( firstPage );
		 memoAddressIWant = &(currentPage[1]);
	 }
	 
	 printf("first available memo is %p at index %i\n", memoAddressIWant, i);
	 return memoAddressIWant;
}

void ThreadManagerBlankPage( volatile struct memo * pageToBlank ){
	 const struct ThreadManagerCache * const cacheInfo = (struct ThreadManagerCache *)(pageToBlank[0].contents);
	 int memosToBlank = cacheInfo->memosPerPage;
	 --memosToBlank;
	 
	 blankMemo( &(pageToBlank[1]), memosToBlank );
}



struct memo * postMemo(struct memo * memoToPost, struct ThreadManagerCache const * theCache ){
	
		
	volatile struct memo * page;
	pthread_mutex_t * lock;
	
	switch( memoToPost->type ){
		case MEMOTHREADCLOSING:
		case MEMOKEYRETURN:
			page = theCache->returnPage;
			lock = theCache->returnLock;
			break;
		case MEMOVALIDATIONREQUEST:
			page = theCache->validationPage;
			lock = theCache->validationLock;
			break;
		case MEMOCREATETHREADREQUEST:
		case MEMOKEYREQUEST:
			page = theCache->queuePage;
			lock = theCache->queueLock;
			break;
	}	
		
	int success = 0;
	while( success == 0 ){
		volatile struct memo * endOfLastPage = ThreadManagerEndOfLastPage( page );
		if( verbosity > 1){
			printf("postMemo is posting memo with type %i lock %p\n", memoToPost->type, memoToPost->memoMutex );
		}
		success = ThreadManagerCopyWithVerify(memoToPost, endOfLastPage);
		printf("unlocking %p\n", lock);
		pthread_mutex_unlock(lock);
	}
}

void * ThreadManagerInitializePages(volatile struct memo ** pages, pthread_mutex_t ** pagelocks, struct ThreadManagerCache * theCache){
	for( int i = 0; i < 3; ++i){
		
	
		pages[i][0].memoMutex = pagelocks[i];
		pages[i][0].type = MEMOSERVICEON;
		pages[i][0].origin = NULL;
		pages[i][0].destination = NULL;
		pages[i][0].sender = NULL;
		pages[i][0].recipient = NULL;
		pages[i][0].contents = theCache;
		
		ThreadManagerBlankPage(pages[i]);	
	}
}

int InitializeTheThreadManagerCache( int maxPageCount, int maxThreadCount, int memosPerPage, struct ThreadManagerCache * theCache ){
	size_t memoSize = sizeof(struct memo);					
	
	/* consider making a recursive lock on the cache to allow the manager to control 
	 * prioritizing and behavior
	 */
	 
	blankMemo( &(theCache->masterPost), 1 );
	
	theCache->ledger = (ThreadManagerKeyLedger *)malloc(sizeof(struct ThreadManagerKeyLedger));


	theCache->ledger->ledgerBlockSize = 300;
	int initialLedgerLength = theCache->ledger->ledgerBlockSize;
	theCache->ledger->length = 0;


	theCache->ledger->keyHolderInboxKeys =
					(pthread_mutex_t **)calloc(initialLedgerLength, sizeof(pthread_mutex_t *));
	theCache->ledger->keyHolderInboxes =
					(struct memo **)calloc(initialLedgerLength, sizeof(struct memo *));
	theCache->ledger->keyHolders = 
					(pthread_t **)calloc(initialLedgerLength, sizeof(pthread_t *));
	theCache->ledger->mutexKeys = 
					(pthread_mutex_t **)calloc(initialLedgerLength, sizeof(pthread_mutex_t *));
	theCache->ledger->blockCount = 1;
	


	 
	 
	theCache->cacheLock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	theCache->threadListLock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	theCache->queueLock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	theCache->validationLock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	theCache->returnLock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	 
	theCache->ledgerLock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	 
	pthread_mutex_init(theCache->cacheLock, NULL);
	pthread_mutex_lock(theCache->cacheLock);
	
	pthread_mutex_init(theCache->ledgerLock, NULL);
	pthread_mutex_lock(theCache->ledgerLock);
	
	/*theCache->ledger.length = 0;*/
	
	pthread_mutex_init(theCache->threadListLock, NULL);
	pthread_mutex_lock(theCache->threadListLock);
	pthread_mutex_init(theCache->queueLock, NULL);
	pthread_mutex_lock(theCache->queueLock);
	pthread_mutex_init(theCache->validationLock, NULL);
	pthread_mutex_lock(theCache->validationLock);
	pthread_mutex_init(theCache->returnLock, NULL);
	pthread_mutex_lock(theCache->returnLock);
	
	
	theCache->queuePage = (volatile struct memo *)calloc(theCache->memosPerPage, memoSize);
	theCache->validationPage = (volatile struct memo *)calloc(theCache->memosPerPage, memoSize);
	theCache->returnPage = (volatile struct memo *)calloc(theCache->memosPerPage, memoSize);
	theCache->threadList = (volatile pthread_t **)calloc(theCache->maxThreadCount,sizeof(pthread_t *));
	
	theCache->currentThreadCount = 1;
	
	pthread_mutex_unlock(theCache->threadListLock);
	pthread_mutex_unlock(theCache->queueLock);
	pthread_mutex_unlock(theCache->validationLock);
	pthread_mutex_unlock(theCache->returnLock);
	
	pthread_mutex_unlock(theCache->ledgerLock);
	
	pthread_mutex_unlock(theCache->cacheLock);
}
int boxesCreated = 0;
struct ThreadManagerPostOfficeBox * getAPostBox( void * contents ){
	
	struct ThreadManagerPostOfficeBox * returnValue = 
				(struct ThreadManagerPostOfficeBox *)malloc(sizeof(ThreadManagerPostOfficeBox));
				
	returnValue->mailboxKey = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(returnValue->mailboxKey, NULL);
	printf("\n\n%i created box %p key %p\n\n", ++boxesCreated, returnValue, returnValue->mailboxKey);
	if( verbosity > 0 ){
		printf("get a post box issued key %p in memo %p\n", returnValue->mailboxKey, returnValue);
	}
	returnValue->contents = (struct memo *)malloc(sizeof(struct memo));
	blankMemo( returnValue->contents, 1 );
	returnValue->contents->contents = contents;
	return returnValue;
}

void simpleKeyReturn( struct ThreadManagerCache * theCache, struct ThreadManagerPostOfficeBox * postbox ){
	pthread_mutex_lock( postbox->mailboxKey	);
	struct memo * memoToPost = postbox->contents;
	pthread_mutex_t * keyBeingReturned = (pthread_mutex_t *)(memoToPost->contents);
	
	memoToPost->type = MEMOKEYRETURN;
	memoToPost->origin = getCallerOnTheLine();
	memoToPost->destination = canITalkToYourManagerPlease( theCache );
	memoToPost->sender = postbox;
	memoToPost->recipient = (void *)(theCache->returnPage);
	
/*	printf("simpleKeyReturn is dropping the key off at the front desk. %p\n", memoToPost );*/

	/* am I implementing the memo post as an assumed locked function? I think so 
	 * I don't want a race condition between preparing to post and posting
	 * as eventually there will be intervening memo editing from the manager
	 * */
	 
	postMemo( memoToPost, theCache );
	pthread_mutex_unlock( postbox->mailboxKey );
	return;
}

struct ThreadManagerPostOfficeBox * simpleKeyRequest( struct ThreadManagerCache * theCache, void * contents ){
	
	struct ThreadManagerPostOfficeBox * returnValue = getAPostBox( contents );
	pthread_mutex_lock(returnValue->mailboxKey);
	struct memo * memoToPost = (struct memo *)malloc(sizeof(struct memo));
	memoToPost->type = MEMOKEYREQUEST;
	pthread_t * callerOnTheLine = (pthread_t *)malloc(sizeof(pthread_t));
	*callerOnTheLine = pthread_self();
	memoToPost->origin = callerOnTheLine;
	memoToPost->destination = canITalkToYourManagerPlease( theCache );
	memoToPost->contents = contents;
	memoToPost->sender = returnValue;
	memoToPost->recipient = (void *)(theCache->queuePage);
	memoToPost->memoMutex = returnValue->mailboxKey;
	if( verbosity > 0){
		printf("simpleKeyRequest is posting a key request memo %p with key %p\n", memoToPost, memoToPost->memoMutex);
	}
	postMemo( memoToPost, theCache );
	free( memoToPost );
	pthread_mutex_unlock(returnValue->mailboxKey);
	return returnValue;
}





void ThreadManagerIncrementTheLedger( struct ThreadManagerKeyLedger * theLedger, pthread_mutex_t * ledgerLock ){
	pthread_mutex_lock( ledgerLock );
	++(theLedger->length);
	if( theLedger->length > floorf( theLedger->ledgerBlockSize * 3.0/4.0 ) ){
		pthread_mutex_unlock( ledgerLock );
		
		++(theLedger->blockCount);
		size_t newLength = (theLedger->blockCount) * (theLedger->ledgerBlockSize);

		pthread_mutex_t ** newKeyHolderInboxKeys = (pthread_mutex_t **)calloc(newLength, sizeof(pthread_mutex_t *));
		struct memo ** newKeyHolderInboxes = (struct memo **)calloc(newLength, sizeof(struct memo *));
		pthread_mutex_t ** newMutexKeys = (pthread_mutex_t **)calloc(newLength, sizeof(pthread_mutex_t *));
		pthread_t ** newKeyHolders = (pthread_t **)calloc(newLength, sizeof(pthread_t *));
		
		pthread_mutex_lock( ledgerLock );
			/* what was I doing........ 
			 * we're updating the ledger to an increased block count
			 * I don't think it should be linear
			 * but I also don't want to scale blocks in 
			 * a fashion that could run out of control
			 * so for now I'll just bump it up one block of memory at a time*/
		
		for(int i=0; i < theLedger->length; ++i){
			newKeyHolderInboxKeys[i] = theLedger->keyHolderInboxKeys[i];
			newKeyHolderInboxes[i] = theLedger->keyHolderInboxes[i];
			newMutexKeys[i] = theLedger->mutexKeys[i];
			newKeyHolders[i] = theLedger->keyHolders[i];
		}
		
		free(theLedger->keyHolderInboxKeys);
		free(theLedger->keyHolderInboxes);
		free(theLedger->mutexKeys);
		free(theLedger->keyHolders);
		
		theLedger->keyHolderInboxKeys = newKeyHolderInboxKeys;
		theLedger->keyHolderInboxes = newKeyHolderInboxes;
		theLedger->mutexKeys = newMutexKeys;
		theLedger->keyHolders = newKeyHolders;
			
		pthread_mutex_unlock( ledgerLock );
	}
	
	
	pthread_mutex_unlock( ledgerLock );
}


void ThreadManagerIssueKeyToPostBox( struct memo * requestMemo, struct ThreadManagerCache * theCache ){
	
	if(verbosity > 0 ){
		printf("key issuer: locking memo %p with key %p\n", requestMemo, requestMemo->memoMutex );
	}
	/*pthread_mutex_lock( requestMemo->memoMutex );*/
	/*printf("the mailbox is locked.\n");*/
	 struct ThreadManagerPostOfficeBox * theLuckyWinner = 
			(ThreadManagerPostOfficeBox *)(requestMemo->sender);


	struct ThreadManagerKeyLedger * theLedger = 
		theCache->ledger;
		
	theLedger->keyHolderInboxKeys[theLedger->length] = 
		theLuckyWinner->mailboxKey;
	theLedger->keyHolderInboxes[theLedger->length] = 
		theLuckyWinner->contents;
	theLedger->keyHolders[theLedger->length] = 
		requestMemo->origin;
	theLedger->mutexKeys[theLedger->length] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));

	pthread_mutex_init( theLedger->mutexKeys[theLedger->length], NULL );
	pthread_mutex_lock( theLedger->mutexKeys[theLedger->length] );
	
	struct memo * issuedKeyMemo  = theLuckyWinner->contents;
	
	issuedKeyMemo->destination = (pthread_t *)(requestMemo->origin);
	issuedKeyMemo->origin = (pthread_t *)theCache->threadList[0];
	issuedKeyMemo->sender = (void *)(theCache->ledger);
	issuedKeyMemo->recipient = (void *)theLuckyWinner;

	issuedKeyMemo->type = MEMOKEYRESPONSE;
	
	/*right now we're just tacking the key requested onto the
	 * response memo. in the future we may want memo urgency
	 * or more in depth messages. it's possible that all key responses
	 * should have an argument void double pointer*/
	
	issuedKeyMemo->contents = (void *)(theLedger->mutexKeys[theLedger->length] );

	ThreadManagerIncrementTheLedger( theLedger, theCache->ledgerLock );

	/* the mailbox key should always also be the memo key 
	 * in any case where the memo has been sent to a queue
	 * and so it should be relied upon to already be assigned
	 * if making decisions about a memo on hand from elsewhere
	 * this is why the memomutex isn't being assigned. it should
	 * already be there if things are being done correctly*/
	if( requestMemo->memoMutex != NULL ){
		pthread_mutex_unlock( requestMemo->memoMutex );
	}
}


int boxesDestroyed = 0;

void * threadManager(void * Johnny){
	
	struct ThreadManagerCache * const theCache = (struct ThreadManagerCache *)((void**)Johnny)[0];
	
	int memosPerPage = theCache->memosPerPage;
	int maxPageCount = theCache->maxPageCount;
	int maxThreadCount = theCache->maxThreadCount;
	
	InitializeTheThreadManagerCache( maxPageCount, maxThreadCount, memosPerPage, theCache );
	
	
	pthread_mutex_lock(theCache->cacheLock);

	volatile struct memo * myPages[] = { theCache->queuePage, theCache->validationPage, theCache->returnPage };
	volatile struct memo * queuePage = myPages[0];
	volatile struct memo * validationPage = myPages[1];
	volatile struct memo * returnPage = myPages[2];
	
	volatile pthread_t ** myThreads = theCache->threadList;
	
	pthread_mutex_unlock(theCache->cacheLock);
	
	pthread_mutex_t * myLocks[] = { theCache->queueLock, theCache->validationLock, theCache->returnLock };

	int myPageCountsOpen[] = { 1, 1, 1 };

	char calm = 1;
	int calmdelay = 100;
	
	ThreadManagerInitializePages( myPages, myLocks, theCache );

	int myPageCountsPrepared[] = { 1, 1, 1 };
/* so, what's happened here is I passed a mutex lock
 * through the thread creation portal hoping to
 * use it to signal that initlalization was done.
 * I'm afraid this might cause some unwanted behavior
 * that would be worse than using a char pointer
 * so I ahve to undo the passage of the pthread mutex
 * here ...*/
	pthread_mutex_lock((pthread_mutex_t *)((void**)Johnny)[1]);
	
	*(char *)(((void**)Johnny)[2]) = 1;
	
	pthread_mutex_unlock((pthread_mutex_t *)((void**)Johnny)[1]);

	while( queuePage[0].type != MEMOSHUTDOWN ){
		if(calm == 1){
			usleep(calmdelay);
		}
		struct memo * returnMemo = NULL;
		while(returnMemo != NULL){
			
		pthread_mutex_lock( myLocks[2] );
		returnMemo = ThreadManagerScan( returnPage, memosPerPage, NULL );
		pthread_mutex_unlock( myLocks[2] );
		
		if( returnMemo != NULL ){
			printf("returnscan: type: %i key: %p\n", returnMemo->type, returnMemo->memoMutex );
			if(verbosity > 0){
				printf("Memo scanning revealed return memo: %p\n", returnMemo);
			}
			if( returnMemo->memoMutex == NULL){
				printf("this is impossible ");
			}
			if( returnMemo->type == MEMOKEYRETURN ){ /* && returnMemo->memoMutex != NULL && returnMemo->contents != NULL ){*/
				printf(" deleting the key %p \n", returnMemo->memoMutex	);
				
				/*printf("deleting the mailbox memo\n");*/
				if( returnMemo->contents != NULL ){
					pthread_t * memoOrigin = 
						((struct memo *)(struct ThreadManagerPostOfficeBox *)returnMemo->contents)->origin;
					
					
					
					if( memoOrigin != NULL && *memoOrigin != *(theCache->threadList[0]) ){
						free( memoOrigin );
					}
					/*free( ((struct ThreadManagerPostOfficeBox *)returnMemo->contents)->contents );*/
					printf("\n\n%i destroying box %p\n\n",++boxesDestroyed,((struct ThreadManagerPostOfficeBox *)returnMemo->contents) );
					free( ((struct ThreadManagerPostOfficeBox *)returnMemo->contents) );
				}
				
				
				free( returnMemo );
			}else if( returnMemo->type == MEMOTHREADCLOSING ){
				pthread_mutex_lock( theCache->threadListLock );
				for( int i = 0; i < theCache->currentThreadCount; ++i){
					if( *theCache->threadList[i] == *returnMemo->origin ){
						for( int j = i+1; j < theCache->currentThreadCount; ++j){
							theCache->threadList[j-1] = theCache->threadList[j];
						}
						--theCache->currentThreadCount;
						break;
					}
				}
				pthread_mutex_unlock( theCache->threadListLock );
			}
		}
	}
		pthread_mutex_lock( myLocks[1] );
		returnMemo = ThreadManagerScan( validationPage, memosPerPage, NULL) ;
		pthread_mutex_unlock( myLocks[1] );
		
		pthread_mutex_lock( myLocks[0] );
		if(verbosity > 5){
			printf("preparing to scan the queue...\n");
		}
		returnMemo = ThreadManagerScan( queuePage, memosPerPage, NULL );
		/* 
		 * I think that to read from returnMemo the page it lives on
		 * must remain locked. I don't know if I've set that kind of
		 * respect for the page lock up elsewhere in the code though
		 * */
		
		/* pthread_mutex_unlock( myLocks[0] ); */
		if( returnMemo != NULL && returnMemo->type == MEMOSHUTDOWN ){
		printf("shutting down the thread manager\n");
			volatile struct memo * currentPage = theCache->queuePage;
			while( currentPage != NULL ){
				for(int i = 1; i < memosPerPage; ++i){
					if( 0 ){
					;
					}
				}
				currentPage = (volatile struct memo *)currentPage->recipient;
				if(currentPage != NULL){
					free(currentPage->sender);
				}
			}
			free( (void*)theCache->queuePage );
			
			currentPage = theCache->validationPage;
			while( currentPage != NULL ){
				for(int i = 1; i < memosPerPage; ++i){
					if( 0 ){
					;
					}
				}
				currentPage = (volatile struct memo *)currentPage->recipient;
				if(currentPage != NULL){
					free(currentPage->sender);
				}
			}
			free( (void *)theCache->validationPage );
		
			currentPage = theCache->returnPage;
			while( 0 && currentPage != NULL ){
				for(int i = 1; i < memosPerPage-1; ++i){
					if( currentPage[i].type == MEMOKEYRETURN && currentPage[i].memoMutex != NULL ){
						pthread_mutex_lock( currentPage[i].memoMutex );
						printf("clearing out the last requests\n");
						free( currentPage[i].memoMutex );
						free( ((struct ThreadManagerPostOfficeBox *)currentPage[i].contents)->contents );
						printf("\n\ndestroying box %p\n\n",((struct ThreadManagerPostOfficeBox *)currentPage[i].contents) );
						free( ((struct ThreadManagerPostOfficeBox *)currentPage[i].contents) );
					}
				}
				currentPage = (volatile struct memo *)currentPage->recipient;
				
				if(currentPage != NULL){
					free(currentPage->sender);
				}
			}
							
			free( (void *)theCache->returnPage );

			free( theCache->validationLock );
			free( theCache->queueLock );
			free( theCache->returnLock );
			
			free( theCache->ledger->keyHolderInboxKeys );
			free( theCache->ledger->keyHolderInboxes );
			free( theCache->ledger->keyHolders );
			free( theCache->ledger->mutexKeys );

			return NULL;
		}
		
		
		if( returnMemo != NULL ){
			if(verbosity > 0){
				printf("thread manager: memo: %p type %i\n", returnMemo, returnMemo->type);
			}
			if( returnMemo->type == MEMOKEYREQUEST ){
				if(verbosity >0){
					printf("thread manager: this is a key request. \n");
				}
				ThreadManagerIssueKeyToPostBox( returnMemo, theCache );
			}else if( returnMemo->type == MEMOCREATETHREADREQUEST ){
				if(1 || verbosity >0){
					printf("thread manager: setting lock %p\n", theCache->threadListLock );
				}
				
				
/*				pthread_mutex_lock( returnMemo->memoMutex );
 * 
 * the memo mutex should always return from the scanner as already locked.
 * 
 * */
			
				
				if(verbosity >0){
					printf("thread manager: editing memo %p\n", returnMemo );
				}
				returnMemo->type = MEMOCREATETHREADRESPONSE;
				if(verbosity >0){
					printf("type value located at %p set to %i, we want %i\n", &(returnMemo->type), returnMemo->type, MEMOCREATETHREADRESPONSE);
				}
				int * threadResponse = (int *)malloc(sizeof(int));
				*threadResponse = theCache->maxThreadCount - theCache->currentThreadCount;
				returnMemo->contents = threadResponse;
				returnMemo->destination = returnMemo->origin;
				returnMemo->origin = canITalkToYourManagerPlease( theCache );
				returnMemo->recipient = returnMemo->sender;
				returnMemo->sender = (void *)(theCache->threadList);
				/*pthread_mutex_lock( ((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->mailboxKey );*/
				ThreadManagerCopyWithVerify( returnMemo, ((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->contents );
				
				if(verbosity >0){
					printf("thread manager: attempting to unlock %p\n", ((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->mailboxKey );
				}
				
				if(*threadResponse > 0){
					pthread_mutex_lock( theCache->threadListLock );
					theCache->threadList[theCache->currentThreadCount] = returnMemo->destination;
					++theCache->currentThreadCount;
					pthread_mutex_unlock( theCache->threadListLock );
				}
				
				/*add the thread to the list */

				
				pthread_mutex_unlock( ((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->mailboxKey );	
				
				
				
				if(verbosity >0){
					printf("thread manager: mutex %p unlocked\n",((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->mailboxKey);
				}
			}

			if(verbosity > 1){
				printf("thread manager: Memo scanning revealed request queue memo: %p\n", returnMemo);
				printf("%i\n", returnMemo->type );
				printf("thread manager: The request queue package is %p, containing \"%s\"\n", returnMemo->contents, returnMemo->contents);
			}
			
			free( returnMemo );
		}
		/* this is an attempt to find a race condition, may not need to lock page 
		 * for the duration of this process*/
		pthread_mutex_unlock( myLocks[0] );
	}
}


struct ThreadManagerCache * InitializeTheThreadManager( int maxPageCount, int maxThreadCount, int memosPerPage ){

	struct ThreadManagerCache * theCache = (struct ThreadManagerCache *)malloc(sizeof(struct ThreadManagerCache));
	
	if( maxPageCount > 0 ){
		theCache->maxPageCount = maxPageCount;
	}
	
	if( maxThreadCount > 0 ){
		theCache->maxThreadCount = maxThreadCount;
	}
	
	if( memosPerPage > 0 ){
		theCache->memosPerPage = memosPerPage;
	}
	
	pthread_mutex_t initlock;
	pthread_mutex_init( &initlock, NULL );
	char initDoneFlag = 0;
	
	pthread_t * theThreadManager = (pthread_t *)malloc(sizeof(pthread_t));  /* is this redundant? */

	void * args[] = { theCache, &initlock, &initDoneFlag };

	pthread_create( theThreadManager, NULL, &threadManager, (void *)args );
	
	int isInitLocked = pthread_mutex_trylock( &initlock );
		
	/* brb need more coffe to remember what I"m doing */
	/* quick plan recap...
	 * we gotta lock and unlock in same thread
	 * so there's gotta be a lock unlock flag shuffle here*/
	int tries = 0;
	while( isInitLocked || initDoneFlag == 0 ){
		
		
		/*printf("did I forget to set the initdone flag in initialization?\n");*/
		
		++tries;
		if( ! isInitLocked ){
			if( initDoneFlag == 1 ){
				break;
			}else{
				pthread_mutex_unlock( &initlock );
			}
		}
		usleep(200+tries);
		isInitLocked = pthread_mutex_trylock( &initlock );
	}

	pthread_mutex_unlock( &initlock );
	
	pthread_mutex_lock(theCache->threadListLock);
	
	theCache->threadList[0] = theThreadManager;
	
	pthread_mutex_unlock(theCache->threadListLock);
	
	return theCache;
}




#ifdef __cplusplus
}
#endif
