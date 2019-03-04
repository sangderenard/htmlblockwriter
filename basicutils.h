#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

#define LINKLISTRESPONSEDELAY 1
#define LINKLISTRESPONSEDENY 2
#define LINKLISTRESPONSESUCCESS 3

#define LINKLISTLOCKLIST 1
#define LINKLISTLOCKINDEX 2
#define LINKLISTLOCKSPECIAL 3

#define LINKLISTBASIC 1

#define DOUBLEVOIDCONSERVATIVE 1
#define DOUBLEVOIDWARY 2
#define DOUBLEVOIDGREEDY 3
#define DOUBLEVOIDAGGRESSIVE 4

#define DOUBLEVOIDLINEAR 1
#define DOUBLEVOIDBLOCK 2
#define DOUBLEVOIDLINEARBLOCK 3
#define DOUBLEVOIDCUBICBLOCK 4

#define DOUBLEVOIDMINIMUMBUFFER 1



 #define MEMOSERVICEON 11
 #define MEMOKEYREQUEST 1
 #define MEMOKEYRESPONSE 2
 #define MEMOVALIDATIONREQUEST 3
 #define MEMOVALIDATIONRESPONSE 4
 #define MEMOKEYRETURN 5
 #define MEMOKEYRETURNRESPOSNE 6
 #define MEMONEXTQUEUEPAGE 7
 #define MEMOCREATETHREADREQUEST 8
 #define MEMOCREATETHREADRESPONSE 9
 #define MEMOSHUTDOWN 10
 
 struct FunctionSet{
	void * (*get)(void *, const int);
	char (*set)(void *, const int, void *);
	
	char (*push)(void *, void *);
	void * (*pop)(void *, const int);
	char (*shift)(void *, void *);
	void * (*unshift)(void *, const int);
	
	char (*add)(void *, void *);
	void * (*difference)(void *, void *);
	
	char (*dimensionalize)(void *, void *);
	char (*serialize)(void *, void *);
			
	void * (*slice)(void *, const int, const int);
	char (*splice)(void *, const int, const int, void *, const int, const int);
		
	char (*sort)(void *, const char);
	char (*shuffle)(void *, const char);
	
	void * (*find)(void *, void *);
	
	void * (*walk)(void *, void *(*));
	void * (*filter)(void *, char(*), void *(*));
};
 
struct ManagedDoubleVoid{
	/*
		*the variables should stay non volatile 
		* because pthread locking should never allow
		* volatility to be an issue. in fact, the volatility
		* of the array should be removed.
	 */
	
	
	
	char watched;
	pthread_t watcher;
	
	pthread_mutex_t * myThreadControlLock; /* for tokens granted by manager */
	
	/*added to try and diagnose a race condition */
	struct ThreadManagerPostOfficeBox * myThreadControlPostbox;
	/* end of modified section */
	
	
	struct ThreadManagerPostOfficeBox * myPostbox; /* contains lock for mailbox */
	struct ThreadManagerCache * theCache;
	
	float needUpdate;
	float parentalUrging;
	
	struct timeval timeSinceUpdated;
	
	size_t size;
	int resizeCount;
	
	char method;
	char temperment;

	int hitTheCliffCount;
	int previousLength;
	int length;
	int maxLength;
	
	volatile void ** self;

	struct FunctionSet * func;
};

struct ListItem{
	struct ThreadManagerPostOfficeBox * myPostbox; 
	pthread_mutex_t * myThreadControlLock;
	struct ThreadManagerCache * theCache;
	
	char watched;
	struct ManagedDoubleVoid contents;
	size_t entrySize;
	int * myIndex;
	int * mySpecialIndex;
		
	struct ListItem * previousItem;
	struct ListItem * nextItem;
	struct ListItem * previousSpecialItem;
	struct ListItem * nextSpecialItem;
	
	struct FunctionSet * func;
	
	int contentsIndexOffeset;
	int contentsIndexEnd;
	
	/*
	 * instead of expanding functionality of the double void immediately
	 * perhaps whatever abstractions and functions I want should be
	 * part of the list item, then the double void would be a general
	 * dynamic array and the listitem would be the featured version
	 * 
	 * ideas:
	 * 
	 * redirect to buffer input{
	 * 
	 * if there's extra space in a list item neighbor and
	 * the list item's array is even momentarily busy, 
	 * redirect the data to the neighbor and fill it back
	 * into the self when it's convenient.
	 * 
	 * this could be negotiated by either a list item thread
	 * or a double void thread
	 * 
	 * shifting by index offset{
	 * 
	 * if it would be inconvenient to rewrite an entire array to accomodate shifting
	 * consider the beginning to be a wrapping of the ending and move indexes
	 * 
	 * contiguous virtualization{
	 * 
	 * use neighbors to pretend to be only part of a larger array
	 *
	 * 
	 * 
	 *  */
	
	
};

struct LinkList{
	struct ThreadManagerPostOfficeBox * myPostbox; 
	pthread_mutex_t * myThreadControlLock;
	struct ThreadManagerCache * theCache;
	
	char watched;
	char listLock;
	char indexLock;
	char specialLock;
	struct ListItem * firstItem;
	struct ListItem * lastItem;
	int listLength;
	struct ListItem ** indexedItems;
	struct ListItem ** specialIndexedItems;
	int * specialItemIndexes;
	int specialItemListLength;
};
 
 struct memo{
	pthread_mutex_t * memoMutex;
	pthread_t * origin;
	pthread_t * destination;
	void * sender;
	void * recipient;
	int type;
	void * contents;
 };

struct ThreadManagerKeyLedger{
	int blockCount;
	int ledgerBlockSize;
	int length;
	pthread_mutex_t ** mutexKeys;
	pthread_t ** keyHolders;
	struct memo ** keyHolderInboxes;
	pthread_mutex_t ** keyHolderInboxKeys;
};

struct ThreadManagerCache{
	struct memo masterPost;
	pthread_mutex_t * cacheLock;
	int memosPerPage;
	int maxPageCount;
	int currentThreadCount;
	int maxThreadCount;
	pthread_mutex_t * threadListLock;
	volatile pthread_t ** threadList;
	pthread_mutex_t * queueLock;
	volatile struct memo * queuePage;
	pthread_mutex_t * validationLock;
	volatile struct memo * validationPage;
	pthread_mutex_t * returnLock;
	volatile struct memo * returnPage;
	struct ThreadManagerKeyLedger * ledger;
	pthread_mutex_t * ledgerLock;
};

/* I compltely forgot I was going to name this structure "multipass" */
struct ThreadManagerPostOfficeBox{
	pthread_mutex_t * mailboxKey;
	struct memo * contents;
};

char scheduleUpdateDoubleVoid(struct ManagedDoubleVoid * const);
char updateDoubleVoid(struct ManagedDoubleVoid * const);
volatile void * doubleVoid(struct ManagedDoubleVoid * const, const int);
void *doubleVoidWorker(void * );
int DoubleVoidRelease(struct ManagedDoubleVoid * const );
int DoubleVoidKnock(struct ManagedDoubleVoid * const );
ThreadManagerPostOfficeBox * DoubleVoidThreadManagerHandshake( struct ManagedDoubleVoid * me, struct ThreadManagerCache * );

char LinkListLock( struct LinkList * me, const char );

char resolveIndexes(struct LinkList *);
char resolveSpecialIndexes(struct LinkList *);

struct ListItem * ListItemCreate( struct ListItem *, ThreadManagerCache	* );
char ListItemPush( void *, void * );
void* ListItemGet( void *, int );

struct LinkList * LinkListCreate( struct ListItem *, struct ThreadManagerCache * );
struct ListItem * LinkListPush( struct LinkList * const, const char, volatile void * * , size_t, int );









struct StringTree{
	
};



 


struct memo * newMemo();

void simpleMemoCopy( struct memo * memoToCopy, volatile struct memo * memoToOverwrite ){
	int verbosity = 0;
	
	if( verbosity > 0 ){
		printf("memocopy target %p intended value %i from %p\n", &(memoToOverwrite->type), memoToCopy->type, &(memoToCopy->type));
	}

	memoToOverwrite->origin = memoToCopy->origin;
	memoToOverwrite->destination = memoToCopy->destination;
	memoToOverwrite->sender = memoToCopy->sender;
	memoToOverwrite->recipient = memoToCopy->recipient;
	memoToOverwrite->type = memoToCopy->type;
	memoToOverwrite->contents = memoToCopy->contents;
	memoToOverwrite->memoMutex = memoToCopy->memoMutex;
	
	if( verbosity > 0 ){
		printf("memocopy has set %p to equal values at %p\n", memoToOverwrite, memoToCopy);
		printf("memocopy the type value location was %p now %p value %i\n", &(memoToCopy->type), &(memoToOverwrite->type), memoToOverwrite->type );
	}
}

void blankMemo( volatile struct memo * memoToBlank, const int memosToBlank ){
	 int verbosity = 0;
	 struct memo blankMemo;
	 if( verbosity > 0 ){
		printf("blankmemo: new blank memo %p\n", &blankMemo );
	}
	 blankMemo.type = 0;
	 blankMemo.origin = NULL;
	 blankMemo.destination = NULL;
	 blankMemo.sender = NULL;
	 blankMemo.recipient = NULL;
	 blankMemo.contents = NULL;
	 blankMemo.memoMutex = NULL;
	 for(int i = 0; i < memosToBlank; ++i ){
		 if( verbosity > 0 ){
			printf("setting %p values to blank values at %p\n", &(memoToBlank[i]), &blankMemo);
		}
		 simpleMemoCopy( &blankMemo, &(memoToBlank[i]) );
	 }
}

int checkMemoCopy( const struct memo memoOne, const struct memo memoTwo ){
	if( memoOne.origin == memoTwo.origin && memoOne.destination == memoTwo.destination 
	&& memoOne.sender == memoTwo.sender && memoOne.recipient == memoTwo.recipient
	&& memoOne.type == memoTwo.type && memoOne.contents == memoTwo.contents ){
		return 1;
	}
	
	return 0;
}

/* this is absolutely redundant, I just forgot that mutexes existed */

int ThreadManagerCopyWithVerify(struct memo * memoToCopy, volatile struct memo * locationToAssure){
	simpleMemoCopy( memoToCopy, locationToAssure );
	return checkMemoCopy( *(struct memo *)memoToCopy, *(struct memo *)locationToAssure );
	
}

struct memo * ThreadManagerScan( volatile struct memo * page, int pageSize, char * scanType ){
	int verbose = 0, verbosity = 0;
	/* first and last entry for linked list entries */
	if(verbosity > 2){
		printf("ThreadManagerScan starting\n");
	}
	for( int i = 1; i < pageSize - 1; ++i ){
		if( page[i].type != 0 ){
			if(verbosity > 1){
				printf("scan: tyepe %i at %p lock %p\n", (int)page[i].type, &(page[i]), page[i].memoMutex);
			}
			
			/* stop putting in code ruining diagnostic
			 * printf calls looking at uninitialized crap
			 * without a check for null
			 **/
			
			
			if( 0 && page[i].memoMutex != NULL ){
				/*printf("%i\n", pthread_mutex_trylock( page[i].memoMutex ));*/
			}
			if( ( page[i].memoMutex == NULL ) || !(pthread_mutex_trylock( page[i].memoMutex )) ){
				if( page[i].memoMutex == NULL ){
					if(verbose > 0){
						printf("the memo mutex is null\n");
					}
				}
				
				struct memo * returnMemo = (struct memo *)malloc(sizeof(struct memo));
				if(verbose > 0){
					printf("threadscan is making a blank memo %p to send to the thread manager\n", returnMemo);
				}
				blankMemo( returnMemo, 1 );
				if(verbosity > 1){
					printf("thread scan is making a xerox..\n");
				}
				ThreadManagerCopyWithVerify( (struct memo *)(&(page[i])), returnMemo );
				if(verbose > 0){
					printf("thread scan: memo %p type %i lock %p generated for manager\n", 
						returnMemo, returnMemo->type, returnMemo->memoMutex); 
				}
				blankMemo( (struct memo *)(&(page[i])), 1);
				if(verbose > 0){
					printf("thread scan blanked memo %p\n", (struct memo *)(&(page[i])));
				}
				return returnMemo;
			}else{
				if(verbose > 0){
					printf("the discovered memo %p is still locked\n", &(page[i]), page[i].memoMutex);
				}
			}
		}
	}
	
	return NULL;
}

/*
 * 
 * I think that I'll need to supply the first page
 * 
 */

volatile struct memo * ThreadManagerEndOfLastPage( volatile struct memo * firstPage ){
	/*
	 * 
	 * intentions:
	 * the first entry of each page should contain all information any function could want
	 * and is also the place to discover emergency flags
	 * so when we're searching for the last place in line, we should check the first entry
	 * of the first page. here, we can use the void pointer in sender and recipient
	 * in order to function as link list addresses. the thread manager can maintain
	 * the last page in the first entry of the first page as sender
	 * 
	 * (sender/previous and recipient/next, with previous at beginning being the end)
	 * 
	 * the thread manager will also be responsible for tidying the number of pages
	 * it could, I guess... also maintain a guess for the last index... but that seems
	 * like unnecessary complexity
	 * 
	 * I think the first entry tells if you need to jump to a new page, then the first entry
	 * also always has the page size, so jump to the last index and count back. this will
	 * be opposite a companion function, TheadManagerFirstPossiblePlace
	 */
	pthread_mutex_lock( firstPage->memoMutex );
	 	
	 const struct ThreadManagerCache * const cacheInfo = (struct ThreadManagerCache *)(firstPage->contents);
	 
	 volatile struct memo * currentPage = firstPage;
	 if(firstPage->sender != NULL){
		 currentPage = (volatile struct memo *)(firstPage->sender);
	 }
	 
	 const int memosPerPage = cacheInfo->memosPerPage;
	 
	 
	 volatile struct memo * memoAddressIWant = NULL;

	 for( int i = memosPerPage-1; i >= 0; --i ){
		 if( currentPage[i].type != 0 ){

			 memoAddressIWant = &(currentPage[i+1]);
		 }
	 }
	 
	 
	 
	 return memoAddressIWant;
}



void destroyVolatileMemo( volatile struct memo * memoToDestroy ){
	/*this isn't right now an array of struct pointers it's an array of structs*/
	
	
	/*free(memoToDestroy);*/
	/*memoToDestroy = (volatile struct memo *)calloc(1, sizeof(struct memo));*/
}



void ThreadManagerBlankPage( volatile struct memo * pageToBlank ){
	 const struct ThreadManagerCache * const cacheInfo = (struct ThreadManagerCache *)(pageToBlank[0].contents);
	 int memosToBlank = cacheInfo->memosPerPage;
	 --memosToBlank;
	 
	 blankMemo( &(pageToBlank[1]), memosToBlank );
}



struct memo * postMemo(struct memo * memoToPost, struct ThreadManagerCache const * theCache ){
	int verbosity = 0;
		
	volatile struct memo * page;
	pthread_mutex_t * lock;
	
	switch( memoToPost->type ){
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
		if(verbosity > 1){
			printf("postMemo is posting memo with type %i\n", memoToPost->type );
		}
		success = ThreadManagerCopyWithVerify(memoToPost, endOfLastPage);
		pthread_mutex_unlock(lock);
	}
}

struct memo * joinMemo(struct memo * memoToWatch){
	
}

/* consider a generic void pack unpack */


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



struct memo * newMemo(){
	struct memo * returnValue = (struct memo *)malloc(sizeof(struct memo *));
	blankMemo( returnValue, 1 );
}

pthread_t * canITalkToYourManagerPlease(struct ThreadManagerCache * thisStarbux ){
	return (pthread_t *)(thisStarbux->threadList[0]);
}

struct ThreadManagerPostOfficeBox * getAPostBox( void * contents ){
	int verbosity = 0;
	struct ThreadManagerPostOfficeBox * returnValue = 
				(struct ThreadManagerPostOfficeBox *)malloc(sizeof(ThreadManagerPostOfficeBox));
	returnValue->mailboxKey = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(returnValue->mailboxKey, NULL);
	if( verbosity > 0 ){
		printf("get a post box issued key %p in memo %p\n", returnValue->mailboxKey, returnValue);
	}
	returnValue->contents = (struct memo *)malloc(sizeof(struct memo));
	blankMemo( returnValue->contents, 1 );
	returnValue->contents->contents = contents;
	return returnValue;
}

pthread_t * getCallerOnTheLine(){
	pthread_t * callerOnTheLine = (pthread_t *)malloc(sizeof(pthread_t *));
	*callerOnTheLine = pthread_self();
	return callerOnTheLine;
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
	int verbosity = 0;
	struct ThreadManagerPostOfficeBox * returnValue = getAPostBox( contents );
	pthread_mutex_lock(returnValue->mailboxKey);
	struct memo * memoToPost = (struct memo *)malloc(sizeof(struct memo));
	memoToPost->type = MEMOKEYREQUEST;
	pthread_t * callerOnTheLine = (pthread_t *)malloc(sizeof(pthread_t *));
	*callerOnTheLine = pthread_self();
	memoToPost->origin = callerOnTheLine;
	memoToPost->destination = canITalkToYourManagerPlease( theCache );
	memoToPost->contents = contents;
	memoToPost->sender = returnValue;
	memoToPost->recipient = (void *)(theCache->queuePage);
	memoToPost->memoMutex = returnValue->mailboxKey;
	if(verbosity > 0){
		printf("simpleKeyRequest is posting a key request memo %p\n", memoToPost);
	}
	postMemo( memoToPost, theCache );
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
	int verbosity = 0;
	if( verbosity > 0 ){
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
			 
	pthread_mutex_unlock( requestMemo->memoMutex );
}

void * threadManager(void * Johnny){
	int verbosity = 0;
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
		
		pthread_mutex_lock( myLocks[2] );
		struct memo * returnMemo = ThreadManagerScan( returnPage, memosPerPage, NULL );
		pthread_mutex_unlock( myLocks[2] );
		
		if( returnMemo != NULL ){
			if(verbosity > 0){
				printf("Memo scanning revealed return memo: %p\n", returnMemo);
			}
		}
		
		pthread_mutex_lock( myLocks[1] );
		returnMemo = ThreadManagerScan( validationPage, memosPerPage, NULL) ;
		pthread_mutex_unlock( myLocks[1] );
		
		pthread_mutex_lock( myLocks[0] );
		if(verbosity > 2){
			printf("preparing to scan the queue...\n");
		}
		returnMemo = ThreadManagerScan( queuePage, memosPerPage, NULL );
		/* 
		 * I think that to read from returnMemo the page it lives on
		 * must remain locked. I don't know if I've set that kind of
		 * respect for the page lock up elsewhere in the code though
		 * */
		
		/* pthread_mutex_unlock( myLocks[0] ); */
		
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
				if(verbosity >0){
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
				
				pthread_mutex_lock( theCache->threadListLock );
				/*add the thread to the list */
				pthread_mutex_unlock( theCache->threadListLock );
				
				pthread_mutex_unlock( ((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->mailboxKey );	
				
				
				
				if(verbosity >0){
					printf("thread manager: mutex %p unlocked\n",((struct ThreadManagerPostOfficeBox *)(returnMemo->recipient))->mailboxKey);
				}
			}

			if(verbosity > 1){
				printf("thread manager: Memo scanning revealed request queue memo: %p\n", returnMemo);
				printf("thread manager: The request queue package is %p, containing \"%s\"\n", returnMemo->contents, returnMemo->contents);
			}
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
