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
 #define MEMOTHREADCLOSING 13
 #define MEMOGENERALINUSE 12
 
 int verbosity = 0;
 
 
 
 
 
 
 void generalKnock( pthread_mutex_t * const );
 int randomSleep( int );
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
 
 /* if I use postboxes, every key will have a memo, but I'll be
  * tied to the threadmanager.
  * 
  * I can't make this struct too bulky because it would then greatly
  * amplify the memory overhead of data structures utilizing it.
  * It's possible that it could make use of postboxes but
  * discard the associated memos, though that increases the overhead
  * in terms of wasted operations.
  * 
  *  */
  
  
  /* 
   *  internal wondering notes:
   * 
   * although this is planned to be mostly used as key/value pairs
   * (which will be confusing because the values are "keys" )
   * and while I don't want to make it use indexes or keys implicitly
   * perhaps it could return indexes for keys and threads or functions
   * or structs using a keyring could set a key string for a mutex,
   * get the resultant index, then never use keys for lookups
   * 
   * in such a case I think that indexes should be returned by add
   * functions. it would be just as fast to immediately look up by
   * index after adding if a return type of the mutex is desired
   * 
   * such as mykey = getbyindex( newkey () );
   * 
   * 
   * */
 
 
 
/* As of right now, myThreadControlPostbox is used for accessing and
 * modifying the array, where mypostbox is used to communicate between
 * thread and array controlling threads. That may not be how I've 
 * dealt with it thus far - that might not be accurate to the code
 * as currently written - but that's the current intention
 * */

struct TreeNode{
	struct TreeNode * parent;
	struct TreeNode * previousSibling;
	struct TreeNode * nextSibling;
	struct TreeNode * firstChild;
	void * contents;
};

struct ManagedDoubleVoid{
	pthread_mutex_t * myThreadControlLock;
	struct ThreadManagerPostOfficeBox * myThreadControlPostbox;
	
	struct ThreadManagerPostOfficeBox * myPostbox; /* contains lock for mailbox */
	struct ThreadManagerCache * theCache;
	
	float needUpdate;
	
	struct timeval timeSinceUpdated;
	
	size_t size;
	int resizeCount;
	
	char method;
	char temperment;
	char deleteBehavior;

	int hitTheCliffCount;
	int previousLength;
	int length;
	int initializedLength;
	int maxLength;
	
	volatile void ** self;

	struct FunctionSet * func;
};

struct ListItem{
	struct ThreadManagerPostOfficeBox * myPostbox; 
	pthread_mutex_t * myThreadControlLock;
	struct ThreadManagerPostOfficeBox * myThreadControlPostbox;
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

};

struct LinkList{
	struct ThreadManagerPostOfficeBox * myPostbox; 
	pthread_mutex_t * myThreadControlLock;
	struct ThreadManagerPostOfficeBox * myThreadControlPostbox;
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
	
	struct FunctionSet * func;
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
struct Keyring{
	long length;
	long allocatedLength;
	
	struct ThreadManagerPostOfficeBox ** threadManagerBoxes;
	pthread_t ** keyHolders;
	pthread_mutex_t ** keys;
	char ** keyNames;
	
	struct ThreadManagerPostOfficeBox * myPostbox;
};
struct RollingCharBuffer{
	pthread_mutex_t bufferKey;
	char close;
	long currentWriteIndex;
	long currentReadIndex;
	long size;
	int framerate;
	char ** buffer;
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

struct ListItem * ListItemCreate( struct ListItem *, struct ThreadManagerCache	* );
char ListItemSet( void *, const int, void *);
void* ListItemGet( void *, const int );
char ListItemPush( void *, void * );
void * ListItemPop( void *, const int );


struct LinkList * LinkListCreate( struct LinkList *, struct ThreadManagerCache * );
char LinkListSet( void *, const int, void * );
void * LinkListGet( void *, const int);
char LinkListPush( void *, void * );
void* LinkListPop( void *, const int );

struct StringTree{
	
};

struct memo * newMemo();


/* proposed future inclusions
 * 
 * Keychain
 * 
 * a keychain struct and set of functions, which will handle a generic
 * parallel array of keys and memos for communcation with the thread
 * manager without each individual data structure needing a custom
 * means of deciding how many keys it needs or when to use them.
 * The proposal is that two simple arrays keep keys and "keys" - mutexes
 * and strings or otherwise values that identify the use of the key.
 * The keychain would communicate with the thread manager to be issued
 * mutex keys and then would allow anything which is accessing the 
 * keychain the correct mutex depending on the purpose at hand
 * 
 * String Cache
 * 
 * a cache of string variables, so that identical copies are never 
 * instantiated, and all string variables are freed in one consolidated
 * place. The inclusion of a string cache like this also implies
 * a general set of string functions similar to what exist now but
 * expanded and formed to work with a cache of string variabls.
 * 
 * Tree
 * 
 * the linked list struct should either be the basis of a tree data structure
 * or else it should be adapted to accomodate that kind of arangement
 * 
 * 
 * htmldatatypes.c
 * 
 * the HTML tag struct and fnuctions need to be... something... anything...
 * the css style struct and functions kind of sort of work but the 
 * html tag code is mostly unwritten.
 * 
 * printer thread
 * 
 * This should be done very soon, so that testing does not imply slower
 * operation than is actually being carried out. All diagnostic messages
 * or output in general should be dumped immediately to memory and then
 * printed by a separate thread dedicated to the task.
 * 
 * this will undoubtably coordinate heavily with or use quite a bit the
 * proposed string handler, so its design should keep that potential future
 * in mind.
 * 
 * 
 * */





#ifdef __cplusplus
}
#endif
