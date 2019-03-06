#ifdef __cplusplus
extern "C" {
#endif

void simpleMemoCopy( struct memo * memoToCopy, volatile struct memo * memoToOverwrite ){
	
	
	if( verbosity > 3 ){
		printf("memocopy target %p intended value %i from %p\n", &(memoToOverwrite->type), memoToCopy->type, &(memoToCopy->type));
	}

	memoToOverwrite->origin = memoToCopy->origin;
	memoToOverwrite->destination = memoToCopy->destination;
	memoToOverwrite->sender = memoToCopy->sender;
	memoToOverwrite->recipient = memoToCopy->recipient;
	memoToOverwrite->type = memoToCopy->type;
	memoToOverwrite->contents = memoToCopy->contents;
	memoToOverwrite->memoMutex = memoToCopy->memoMutex;
	
	if( verbosity > 4 ){
		printf("memocopy has set %p to equal values at %p\n", memoToOverwrite, memoToCopy);
		printf("memocopy the type value location was %p now %p value %i\n", &(memoToCopy->type), &(memoToOverwrite->type), memoToOverwrite->type );
	}
}

void blankMemo( volatile struct memo * memoToBlank, const int memosToBlank ){
	 
	 struct memo blankMemo;
	 if( verbosity > 3 ){
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
		 if( verbosity > 4 ){
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


void destroyVolatileMemo( volatile struct memo * memoToDestroy ){
	/* I don't remember my intentions for this, but I do need garbage collection */
}

struct memo * joinMemo(struct memo * memoToWatch){
	/* I have no idea what I was going to do with this */
}


struct memo * newMemo(){
	struct memo * returnValue = (struct memo *)malloc(sizeof(struct memo *));
	blankMemo( returnValue, 1 );
}

pthread_t * canITalkToYourManagerPlease(struct ThreadManagerCache * thisStarbux ){
	return (pthread_t *)(thisStarbux->threadList[0]);
}



pthread_t * getCallerOnTheLine(){
	pthread_t * callerOnTheLine = (pthread_t *)malloc(sizeof(pthread_t *));
	*callerOnTheLine = pthread_self();
	return callerOnTheLine;
}

#ifdef __cplusplus
}
#endif
