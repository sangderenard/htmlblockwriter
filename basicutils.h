#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

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

struct ManagedDoubleVoid{
	char lock;
	char method;
	char temperment;
	int length;
	int maxLength;
	size_t size;
	int resizeCount;
	void ** self;
};

char updateDoubleVoid(struct ManagedDoubleVoid * const me){
	printf("Updating the double void...\n");
	if( me->self == NULL ){
		/*exit(0);*/
		me->resizeCount = 0;
		me->size = 0;
		me->maxLength = 0;
		me->length = 0;
		me->method = DOUBLEVOIDLINEAR;
		me->temperment = DOUBLEVOIDCONSERVATIVE;
		me->self = (void**)malloc(sizeof(void*));
		/*(me->self)[0] = NULL;*/
		printf("Performed initialization, content at %p...\n", me->self);
	}
	
	/* i think initial length needs are different for new entry vs blank initialization */
	
	int requiredLength;
	size_t requiredSize;
	switch( me->temperment ){
		case DOUBLEVOIDCONSERVATIVE:
			requiredLength = me->length + DOUBLEVOIDMINIMUMBUFFER;
			requiredSize = ( requiredLength * sizeof(void *) );
			printf("requiredsize is %i (%i %i %i)\n", requiredSize, me->length, DOUBLEVOIDMINIMUMBUFFER, sizeof(void*));
		printf("required length is %i, used length is %i\n", requiredLength, me->length);

			if( requiredSize > me->size ){
				void ** newSelf = (void **)malloc( requiredSize );
				
				printf("beginning transfer of %i items...\n", me->length-1);
				
				for(int i = 0; i < me->length; i++){
					newSelf[i] = (me->self)[i];
					printf("placed item at index %i\n",i);
				}
				
				printf("destroying old list\n");
				free(me->self);
				
				printf("filling remaining space to index %i with NULL pointers\n", requiredLength);
				
				for(int j = me->length; j < requiredLength; j++){
					newSelf[j] = malloc(sizeof(void*));
				}
				me->maxLength = requiredLength;
				me->size = requiredSize;
				me->self = newSelf;
			}
	}
	return 0;
}

char scheduleUpdateDoubleVoid(struct ManagedDoubleVoid * const me){
	
	return updateDoubleVoid(me);
}

void * doubleVoid(struct ManagedDoubleVoid * const me, const int i){
	if( me->lock == 1){
		printf("the doublevoid lock is left on.\n");
		return NULL;
	}
	printf("I'm in the doublevoid...\n");
	if( i < me->length ){
		printf("i'm returning %p from within length\n", (me->self)[i]);
		return (me->self)[i];
	}else if( i < me->maxLength ){
		me->lock = 1;
		me->length  = i + 1;
	
		me->lock = scheduleUpdateDoubleVoid(me);

		if( me->lock == 1 ){
			return NULL;
		}else{
			printf("i'm returning %p from within maxLength\n", (me->self)[i]);
			return (me->self)[i];
		}
	}else{
		me->lock = 1;
		me->length = i + 1;
		me->lock = updateDoubleVoid(me);
		me->self[i] = malloc(sizeof(void *));
		printf("i'm returning %p from within resize\n", (me->self)[i]);
		printf("I was asked for index %i and had to generate space to fit it\n", i);
		return (me->self)[i];
	}
}

struct ListItem{
	struct ManagedDoubleVoid contents;
	size_t entrySize;
	int * myIndex;
	int * mySpecialIndex;
	char itemLock;
	struct ListItem * previousItem;
	struct ListItem * nextItem;
	struct ListItem * previousSpecialItem;
	struct ListItem * nextSpecialItem;
};

struct LinkList{
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

char resolveIndexes(struct LinkList *);

char resolveSpecialIndexes(struct LinkList *);

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



/*	LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 ); */

struct ListItem * ListItemPush( struct ListItem * , void * );

struct ListItem * LinkListPush( struct LinkList * const me, const char behaviorType, void * * newContents, size_t newEntrySize, int contentsLength ){
	printf("entering LinkListPush...\n");
	if( behaviorType == LINKLISTBASIC ){
		LinkListLock( me , LINKLISTLOCKLIST );
		printf("creating the new item with %i entries of size %i...\n", contentsLength, newEntrySize);
		
		struct ListItem * newLinkListEntry = (struct ListItem *)malloc(sizeof(struct ListItem));
		printf("gotta track down the corrupted memory\n");
		/*this memory addressing will fail and is currently only set to first item*/


		for(int i = 0; i < contentsLength; i++){
			printf("adding a contents entry %i\n",i);
			ListItemPush( newLinkListEntry,  newContents[i] );
		}
		
		printf("the new listed item's contents is now %i entries, wanted %i\n",newLinkListEntry->contents.length , contentsLength);
		
		printf("\n\n checking the expected values \n\n");
		printf("we would like to set the link list pointers now.\n");
		printf("we think the current end of the list is here: %p\n", me->lastItem);
		
		
		printf("updating item's \"previous\" adresses which is now %p with %p...\n", newLinkListEntry->previousItem, me->lastItem);
		
		
		
		newLinkListEntry->previousItem = me->lastItem;
		printf("updating list's last item(%p)'s \"next\" adresses, currently %p, changing to %p...\n", me->lastItem, me->lastItem->nextItem, newLinkListEntry);
		me->lastItem->nextItem = newLinkListEntry;
		printf("updating list's \"last\" adresses...\n");
		me->lastItem = newLinkListEntry;
		++(me->listLength);
		me->listLock = 0;
	}
	
	printf("done with LinkListPush()\n");
		
}

void* ListItemGet( struct ListItem * me, const int index ){
	return *(void**)doubleVoid( &(me->contents), index );
}

struct ListItem * ListItemPush( struct ListItem * me, void * contentsEntry ){
	me->itemLock = 1;
	printf("I was asked to add pointer: %p to the item\n", contentsEntry);
	printf("If this is a pointer list the virst adress is: %p\n", ((float*)contentsEntry));
	printf("If this is a float pointer pointer list, the first float is %f\n", ((*(float**)contentsEntry))[0]);
	printf("calling doublevoid at index at %i\n", me->contents.length);
	void ** contentsTarget = (void**)doubleVoid( &(me->contents), me->contents.length );
	printf("doublevoid requested index void* is located at %p, it points to %p\n", contentsTarget, *contentsTarget);
	*contentsTarget = contentsEntry;
	printf("the doublevoid void* entry has been assigned value %p, is now %p at %p\n", contentsEntry, *contentsTarget, contentsTarget);
	printf("the doublevoid reports a length of %i and lock state %i\n", me->contents.length, me->contents.lock );
	printf("setting the length of the doublevoid to reflect our manual new entry\n");
	
	++(me->contents.length);
	me->itemLock = 0;
	
	return me;
}

struct LinkList * LinkListCreate( struct ListItem * me){
	if(me == NULL){
		me = (struct ListItem *)malloc(sizeof(struct ListItem));
		me->contents.length = 0;
		updateDoubleVoid(&(me->contents));
	}
	struct LinkList * newList = (struct LinkList *)(malloc(sizeof(struct LinkList)));
	newList->indexLock = 1;
	newList->specialLock = 1;
	newList->firstItem = me;
	newList->lastItem = me;
	newList->listLength = 1;
	newList->indexedItems = (struct ListItem **)(malloc(sizeof(struct ListItem *)));
	(newList->indexedItems)[0] = me;
	return newList;
}


struct StringTree{
	
};

#ifdef __cplusplus
}
#endif
