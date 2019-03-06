#ifdef __cplusplus
extern "C" {
#endif

/*void * reallocateArray( void * array, long length, size_t size ){*/
	/* I'm not sure how possible this is given I won't know the size
	 * of any array that isn't one specific data type. i'm not sure this
	 * should be generalized */
	/*void * newArray = malloc( size );
	*
	*for( long i = 0; i < length; ++i ){
	*	
	*}
	*}
	*/




 
 /* desired functions:
  * 
  * initializeKeyring check
  * 
  * KeyringNewKey  check
  * KeyringDeleteKey check 
  * 
  * KeyringIndexByKey check
  * KeyringKeyByIndex check 
  * 
  * KeyringIndexByName check
  * KeyringNameByIndex check
  * 
  * KeyringKeyByName check
  * KeyringNameByKey check
  * 
  * destroyKeyring
  * 
  * */
 
 
 /* */
 

 
void KeyringKnock( struct Keyring * me ){
	generalKnock( me->myPostbox->mailboxKey );
}

void KeyringRelase( struct Keyring * me ){
	pthread_mutex_unlock( me->myPostbox->mailboxKey );
} 
 
size_t KeyringExpand( struct Keyring * me, int newSize ){
	pthread_mutex_lock( me->myPostbox->mailboxKey );
	char autoSize = 0;
	if( newSize == 0 ){ autoSize = 1; };
	 
	size_t newSizeOne = sizeof(struct ThreadManagerPostOfficeBox *) * newSize;
	size_t newSizeTwo = sizeof(pthread_mutex_t *) * newSize;
	size_t newSizeThree = sizeof(char *) * newSize;
	size_t newSizeFour = sizeof(pthread_t *) * newSize;
	struct ThreadManagerPostOfficeBox ** newThreadManagerBoxes = (struct ThreadManagerPostOfficeBox **)malloc(newSizeOne);
	pthread_mutex_t ** newKeys = (pthread_mutex_t **)malloc(newSizeTwo);
	char ** newKeyNames = (char **)malloc(newSizeThree);
	pthread_t ** newKeyHolders = (pthread_t **)malloc(newSizeFour);
	 
	for(int i = 0; i < me->length; ++i){
		newThreadManagerBoxes[i] = me->threadManagerBoxes[i];
		newKeys[i] = me->keys[i];
		newKeyNames[i] = me->keyNames[i];
		newKeyHolders[i] = me->keyHolders[i];
	}
	
	for(int i = me->length; i < newSize; ++i){
		newThreadManagerBoxes[i] = NULL;
		newKeys[i] = NULL;
		newKeyNames[i] = NULL;
		newKeyHolders[i] = NULL;
	}
	
	free(me->threadManagerBoxes);
	me->threadManagerBoxes = newThreadManagerBoxes;
	free(me->keys);
	me->keys = newKeys;
	free(me->keyNames);
	me->keyNames = newKeyNames;
	free(me->keyHolders);
	me->keyHolders = newKeyHolders;
	me->allocatedLength = newSize;
	return newSizeOne + newSizeTwo + newSizeThree;
}
 
long KeyringNewKey( struct Keyring * me, char * name ){
	KeyringKnock( me );
	int newIndex;
	
	ThreadManagerCache * theCache = (struct ThreadManagerCache *)(me->myPostbox->contents->contents);
	
	if( me->length == me->allocatedLength ){
		KeyringExpand( me, me->allocatedLength * 2 );
	}
	
	(me->keyNames)[me->length] = name;
	me->keyHolders[me->length] = NULL;
	
	if( theCache != NULL ){
		(me->threadManagerBoxes)[me->length] = getAPostBox( theCache );
		(me->keys)[me->length] = ((me->threadManagerBoxes)[me->length])->mailboxKey;
	}else{
		
		/* consider either a blank memo or a null memo option */
		
		(me->threadManagerBoxes)[me->length] = NULL;
		(me->keys)[me->length] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init((me->keys)[me->length], NULL );
	}
	
	newIndex = me->length;
	++(me->length);
	KeyringRelase( me );
	return newIndex;
}
 
char KeyringDeleteKey( struct Keyring * me, int index ){
	if((me->threadManagerBoxes)[index] != NULL){
		free((me->threadManagerBoxes)[index]);
	}
	if((me->keys)[index] != NULL){
		free((me->keys)[index]);
	}
	if((me->keyNames)[index] != NULL){
		free((me->keyNames)[index]);
	}
	
	me->keyHolders[index] = NULL;
}
 
pthread_mutex_t * KeyringKeyByName( struct Keyring * me, char * name ){
	int index = findStringAmongStrings( (const char **)me->keyNames, me->length, name );
	if( index == -1 ){
		return NULL;
	}else{
		return me->keys[index];
	}
}
 
 
long KeyringIndexByName( struct Keyring * me, char * name ){
	return findStringAmongStrings( (const char **)me->keyNames, me->length, name );
}
 
char * KeyringNameByIndex( struct Keyring * me, const long index ){
	return me->keyNames[index];
}

pthread_mutex_t * KeyringKeyByIndex( struct Keyring * me, const long index ){
	return me->keys[index];
}

char * KeyringNameByKey( struct Keyring * me, pthread_mutex_t * key){
	for(int i = 0; i < me->length; ++i){
		if( me->keys[i] == key ){
			return me->keyNames[i];
		}
	}
	
	return NULL;
}

long KeyringIndexByKey( struct Keyring * me, pthread_mutex_t * key ){
	for(int i = 0; i < me->length; ++i){
		if( me->keys[i] == key ){
			return i;
		}
	}
	
	return -1;
}

struct Keyring * initializeKeyring( struct ThreadManagerCache * theCache, const long initialLength ){
	struct Keyring * newKeyring = (struct Keyring *)malloc(sizeof(struct Keyring));
	newKeyring->myPostbox = getAPostBox( theCache );
	newKeyring->length = 0;
	newKeyring->allocatedLength = 0;
	KeyringExpand( newKeyring, initialLength );
	return newKeyring;
}


#ifdef __cplusplus
}
#endif
