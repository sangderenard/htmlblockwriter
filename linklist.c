#ifdef __cplusplus
extern "C" {
#endif

/* 
 * 
 * 
 * 
 * 
 * the next thing to fix is the struct that makes up each link
 * of my linked list. but, seeing as, as far as I can tell, 
 * the multithreaded dynamic array is working well enough 
 * to fill in the functional details later
 * 
 * and since I am not sure that's really true and I just don't
 * realize how buggy it still is...
 * 
 * 
 * I think this is a good time to stop for the night.
 * 
 * 
 * */



struct FunctionSet ListItemFunctionSet;











struct ListItem * LinkListGet( struct LinkList * const me, void * identifier, const char identifyStyle){
	struct ListItem * currentIndex = me->firstItem;
	switch(identifyStyle){
		case LINKLISTBASIC:
		
			for( int i = 0; i < *((int*)identifier); i++ ){
				currentIndex = currentIndex->nextItem;
			}
		
			return currentIndex;
			break;
			
	}
	
	return NULL;
}

struct ListItem * LinkListPop( struct LinkList * const me ){
	if( me->listLength == 1 ){
			return NULL;
	}
	LinkListLock( me, LINKLISTLOCKLIST );
	struct ListItem * output = me->lastItem;
	me->lastItem = output->previousItem;
	me->lastItem->nextItem = NULL;
	--(me->listLength);
	me->listLock = 0;
	return output;
}


ThreadManagerPostOfficeBox * LinkListThreadManagerHandshake( struct LinkList * me, struct ThreadManagerCache * threadManagerCache ){
	me->myPostbox = simpleKeyRequest( threadManagerCache, NULL );
	pthread_mutex_lock( me->myPostbox->mailboxKey );
	me->myThreadControlLock = me->myPostbox->mailboxKey;
	pthread_mutex_unlock( me->myPostbox->mailboxKey );
}

ThreadManagerPostOfficeBox * ListItemThreadManagerHandshake( struct ListItem * me, struct ThreadManagerCache * threadManagerCache ){
	me->myPostbox = simpleKeyRequest( threadManagerCache, NULL );
	pthread_mutex_lock( me->myPostbox->mailboxKey );
	me->myThreadControlLock = me->myPostbox->mailboxKey;
	pthread_mutex_unlock( me->myPostbox->mailboxKey );
}
struct ListItem * ListItemCreate( struct ListItem * me, struct ThreadManagerCache * theCache ){
	if(me == NULL){
		me = (struct ListItem *)malloc(sizeof(struct ListItem));
	}	

	me->theCache = theCache;
	me->contents.theCache = theCache;
	me->contents.length = 0;
	me->contents.self=NULL;
	me->func = &ListItemFunctionSet;
	
	
	struct ThreadManagerPostOfficeBox * contentsMailbox = DoubleVoidThreadManagerHandshake( &(me->contents), theCache );
	pthread_mutex_lock( me->contents.myThreadControlLock );
	initializeDoubleVoid( &(me->contents), NULL );
	me->contents.theCache = theCache;
	pthread_mutex_unlock( me->contents.myThreadControlLock );
	
	ListItemThreadManagerHandshake( me, theCache );
	
	return me;
}

void ListItemKnock( struct ListItem * me ){
	int waiter = 0;
	while( pthread_mutex_trylock( me->myThreadControlLock ) ){
		if(waiter < 200){
			++waiter;
		}
		usleep(waiter);
	}
}

void ListItemRelease( struct ListItem * me ){
	pthread_mutex_unlock( me->myThreadControlLock );
}

void * ListItemPop( void * self, int count){
	struct ListItem * me = (struct ListItem *)self;
	ListItemKnock( me );
	DoubleVoidKnock( &(me->contents) );
	void * returnValue;
	void ** returnValues;
	if( count > 1 ){
		returnValues = (void **)me->contents.func->pop( &(me->contents), count );
	}else{
		returnValue = me->contents.func->pop( &(me->contents), count );
	}
	DoubleVoidRelease( &(me->contents) );
	ListItemRelease( me );
	if( count > 1 ){
		return (void *)returnValues;
	}else{
		return returnValue;
	}
}

char ListItemPush( void * self, void * contentsEntry ){
	struct ListItem * me = (struct ListItem *)self;
	ListItemKnock( me );
	DoubleVoidKnock( &(me->contents) );
	me->contents.func->push( &(me->contents), contentsEntry );
	DoubleVoidRelease( &(me->contents) );
	ListItemRelease( me );
}

void* ListItemGet( void * self, int index ){
	struct ListItem * me = (struct ListItem *)self;
	ListItemKnock( me );
	DoubleVoidKnock( &(me->contents) );
	void * returnValue = DoubleVoidGet( &(me->contents), index );
	DoubleVoidRelease( &(me->contents) );
	ListItemRelease( me );
	return returnValue;
}

char ListItemSet(void * self, const int index, void * input){
	struct ListItem * me = (struct ListItem *)self; 
	ListItemKnock( me );
	DoubleVoidKnock( &(me->contents) );
	me->contents.func->set( &(me->contents), index, input );
	DoubleVoidRelease( &(me->contents) );
	ListItemRelease( me );
}

void defineListItemFunctions(){
	defineDoubleVoidFunctions();
	ListItemFunctionSet.get = &ListItemGet;
	ListItemFunctionSet.set = &ListItemSet;
		
	ListItemFunctionSet.push = &ListItemPush;
	ListItemFunctionSet.pop = &ListItemPop;
	/*ListItemFunctionSet.shift = &ListItemShift;
	*ListItemFunctionSet.unshift = &ListItemUnshift;
	*/

}

/* this needs to be changed over to reflect the use of multiple threads
 * and mutex's as soon as possible */

char LinkListLock( struct LinkList * me, const char lockType ){
	if( me->listLock == 0 ){
		switch(lockType){
			case LINKLISTLOCKLIST:
				me->listLock = 1;
			case LINKLISTLOCKINDEX:
				me->indexLock = 1;
			case LINKLISTLOCKSPECIAL:
				me->specialLock = 1;
		}
		
		return LINKLISTRESPONSESUCCESS;
	}else{
		return LINKLISTRESPONSEDENY;
	}
}

struct LinkList * LinkListCreate( struct ListItem * me, struct ThreadManagerCache * theCache){
	if(me == NULL){
		me = ListItemCreate(me, theCache);
	}
	struct LinkList * newList = (struct LinkList *)(malloc(sizeof(struct LinkList)));
	newList->listLock = 0;
	newList->indexLock = 1;
	newList->specialLock = 1;
	newList->firstItem = me;
	
	newList->theCache = theCache;
	
	newList->lastItem = me;
	newList->listLength = 1;
	newList->indexedItems = (struct ListItem **)(malloc(sizeof(struct ListItem *)));
	(newList->indexedItems)[0] = me;
	return newList;
}

struct ListItem * LinkListPush( struct LinkList * const me, const char behaviorType, volatile void * * newContents, size_t newEntrySize, int contentsLength ){
	if( behaviorType == LINKLISTBASIC ){
		LinkListLock( me , LINKLISTLOCKLIST );

		struct ListItem * newLinkListEntry = (struct ListItem *)malloc(sizeof(struct ListItem));
		newLinkListEntry = ListItemCreate(newLinkListEntry, me->theCache);

		for(int i = 0; i < contentsLength; i++){
			ListItemPush( newLinkListEntry,  (void *)newContents[i] );
		}
		
		newLinkListEntry->previousItem = me->lastItem;
	
		me->lastItem->nextItem = newLinkListEntry;
		me->lastItem = newLinkListEntry;
		++(me->listLength);
		me->listLock = 0;
		return newLinkListEntry;
	}
	return NULL;
}

#ifdef __cplusplus
}
#endif
