#ifdef __cplusplus
extern "C" {
#endif

struct FunctionSet LinkListFunctionSet;
struct FunctionSet ListItemFunctionSet;



ThreadManagerPostOfficeBox * ListItemThreadManagerHandshake( struct ListItem * me, struct ThreadManagerCache * threadManagerCache ){
	me->myPostbox = simpleKeyRequest( threadManagerCache, NULL );
	pthread_mutex_lock( me->myPostbox->mailboxKey );
	me->myThreadControlPostbox = simpleKeyRequest( threadManagerCache, NULL );
	me->myThreadControlLock = me->myThreadControlPostbox->mailboxKey;
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
	
	me->previousItem = NULL;
	me->nextItem = NULL;
	
	ListItemThreadManagerHandshake(  me, theCache );
	
	initializeDoubleVoid( &(me->contents), NULL, theCache );
	
	return me;
}

void ListItemKnock( struct ListItem * me ){
	int waiter = 0;
	/*printf("I'm %p", me);*/
	while( pthread_mutex_trylock( me->myThreadControlLock ) ){
	/*	if(waiter < 200){*/
			++waiter;
			if(waiter > 10){exit(1);}
		/*}*/
		int sleep = floor(((float)(float)waiter * (float)rand()) / (float)INT_MAX);
		if(verbosity > 3){ printf("usleep(%i) in LI Knock\n",sleep); }
		usleep(sleep);
	}
}

void ListItemRelease( struct ListItem * me ){
	pthread_mutex_unlock( me->myThreadControlLock );
}

char ListItemSet(void * self, const int index, void * input){
	struct ListItem * me = (struct ListItem *)self; 
	/*printf("looking for %i entry in %p", index, &(me->contents));*/
	/*sleep(1);*/
	ListItemKnock( me );
	DoubleVoidKnock( &(me->contents) );
	me->contents.func->set( &(me->contents), index, input );
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

char ListItemPush( void * self, void * contentsEntry ){
	struct ListItem * me = (struct ListItem *)self;
	ListItemKnock( me );
	DoubleVoidKnock( &(me->contents) );
	me->contents.func->push( &(me->contents), contentsEntry );
	DoubleVoidRelease( &(me->contents) );
	ListItemRelease( me );
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

ThreadManagerPostOfficeBox * LinkListThreadManagerHandshake( struct LinkList * me, struct ThreadManagerCache * threadManagerCache ){
	me->myPostbox = simpleKeyRequest( threadManagerCache, NULL );
	pthread_mutex_lock( me->myPostbox->mailboxKey );
	me->myThreadControlPostbox = simpleKeyRequest( threadManagerCache, NULL );
	me->myThreadControlLock = me->myThreadControlPostbox->mailboxKey;
	pthread_mutex_unlock( me->myPostbox->mailboxKey );
}


struct LinkList * LinkListCreate( struct LinkList * me, struct ThreadManagerCache * theCache){
	if( me == NULL ){
		me = (struct LinkList *)(malloc(sizeof(struct LinkList)));
	}
	me->func = &LinkListFunctionSet;
	me->theCache = theCache;
	
	LinkListThreadManagerHandshake( me, theCache );
	
	me->indexLock = 1;
	me->specialLock = 1;
	me->firstItem = NULL;
	me->lastItem = NULL;
	
	me->listLength = 0;
	
	return me;
}

void LinkListKnock( struct LinkList * me ){
	int waiter = 0;
	while( pthread_mutex_trylock( me->myThreadControlLock ) ){
		if(waiter < 200){
			++waiter;
		}
		usleep(waiter*rand()/INT_MAX);
	}
}

void LinkListRelease( struct LinkList * me ){
	pthread_mutex_unlock( me->myThreadControlLock );
}

char LinkListSet( void * self, const int index, void * value){
	struct LinkList * me = (struct LinkList *)self;
	LinkListKnock( me );
	struct ListItem * currentIndex = me->firstItem;
	int i= 0;
	for( i = 0; i < index; i++ ){
		currentIndex = currentIndex->nextItem;
		
	}/*printf("the list item is at %p, should be index %i",currentIndex, i);*/

	currentIndex->func->set( currentIndex, 0, value );
	LinkListRelease( me );
}

void * LinkListGet( void * self, const int index ){
	struct LinkList * me = (struct LinkList *)self;
	LinkListKnock( me );
	struct ListItem * currentIndex = me->firstItem;
	for( int i = 0; i < index; i++ ){
		currentIndex = currentIndex->nextItem;
	}
	LinkListRelease( me );
	return currentIndex;
}

char LinkListAppendLink( struct LinkList * me, struct ListItem * newItem ){
	if( me->lastItem != NULL ){
		newItem->previousItem = me->lastItem;
		me->lastItem->nextItem = newItem;
	
	}
	newItem->nextItem = NULL;
	me->lastItem = newItem;
	++me->listLength;
}

char LinkListDeleteLink( struct LinkList * me, struct ListItem * old){
	old->previousItem->nextItem = old->nextItem;
	old->nextItem->previousItem = old->previousItem;
	--(me->listLength);
}

char LinkListPush( void * self, void * value){
	struct LinkList * me = (struct LinkList *)self;
	LinkListKnock( me );
	struct ListItem * newLinkListEntry = ListItemCreate( NULL, me->theCache );
	ListItemPush( newLinkListEntry,  value );
	struct ListItem * theLastItem = me->lastItem;
	
	if( me->listLength == 0 ){
		me->firstItem = newLinkListEntry;
	}
	
	if( theLastItem != NULL ){
		ListItemKnock( theLastItem );
	}
	LinkListAppendLink( me, newLinkListEntry );
	if( theLastItem != NULL ){
		ListItemRelease( theLastItem );
	}
	
	LinkListRelease( me );
}


void * LinkListPop( void * self, const int count ){
	struct LinkList * me = (struct LinkList *)self;
	if( verbosity > 2 ){
		printf("LL is popping %i values.", count );
	}
	if( me->listLength == 0 ){
			return NULL;
	}
	if( verbosity > 4 ){
		printf("locking linked list\n");
	}
	LinkListKnock( me );
	if( verbosity > 4 ){
		printf("linked list locked, locking item %p\n", me->lastItem);
	}
	/*ListItemKnock( me->lastItem );*/
	
	struct ListItem * output = me->lastItem;
	if( verbosity > 4 ){
		printf("output has been set to %p\n", output);
	}
	me->lastItem = output->previousItem;
	if( verbosity > 4 ){
		printf("last item now equal to %p\n", me->lastItem );
	}
	ListItemRelease( output );

	if( me->lastItem != NULL ){
		if( verbosity > 4 ){
			printf("list not tempty, %p is last item\n",me->lastItem);
		}
		ListItemKnock( me->lastItem );
		me->lastItem->nextItem = NULL;
		ListItemRelease( me->lastItem );
	}

	--(me->listLength);
	if(me->listLength == 0){
		me->firstItem = NULL;
	}
	LinkListRelease( me );
	if( verbosity > 4 ){
		printf("returning %p\n", output);
	}

	return output;
}


void defineLinkListFunctions(){
	defineDoubleVoidFunctions();
	defineListItemFunctions();
	LinkListFunctionSet.get = &LinkListGet;
	LinkListFunctionSet.set = &LinkListSet;
	LinkListFunctionSet.push = &LinkListPush;
	LinkListFunctionSet.pop = &LinkListPop;


	/*ListItemFunctionSet.shift = &ListItemShift;
	*ListItemFunctionSet.unshift = &ListItemUnshift;
	*/

}

#ifdef __cplusplus
}
#endif
