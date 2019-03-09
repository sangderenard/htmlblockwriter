#include <stdio.h>
#include <sys/time.h>
#include <limits.h>

#include "./htmldatatypes.c"


#define DIV "div"
#define ID "id="
#define STYLE "style="
#define CLASS "class="
#define MAXHTMLWORDLENGTH  50



char *divGrid(int width, int height, char style){
	return NULL;
}

int main(void) {
	
	RollingCharBuffer * screen;
	screen = initializeRollingCharBuffer( 5000, NULL );
	pthread_t * printThread = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(printThread, NULL, printScreen, (void *)screen);
	char * linebuffer;
	
	
	int testingDoubleVoid = 1;
	int testingListItem = 1;
	int testingLinkList = 1;
	
	int maxPageCount=20;
	int maxThreadCount=20;
	int memosPerPage=20;
	
	struct ThreadManagerCache * testThreadManagerCache;
	
	testThreadManagerCache =  InitializeTheThreadManager( maxPageCount, maxThreadCount, memosPerPage );
	
	/* double void initialization process */
	
	struct ManagedDoubleVoid * testDoubleVoid;
	

	/* end double void initialization process */
		
	struct ListItem * testListItem;
	
	
	
	struct LinkList	* testLinkList;
	struct ThreadManagerPostOfficeBox * testListListPostBox;
	



	/*Keyring * testKeyring;*/
	/*testKeyring = initializeKeyring( testThreadManagerCache, 10 );*/

	
	
	/*void * testObjects[] = { testDoubleVoid, testListItem, testLinkList };*/

for(int iterations = 0; iterations < 1; ++iterations){	
	if( testingDoubleVoid == 1 ){
		testDoubleVoid = (struct ManagedDoubleVoid	*)malloc(sizeof(struct ManagedDoubleVoid));
		defineDoubleVoidFunctions();

		initializeDoubleVoid( testDoubleVoid, NULL, testThreadManagerCache );
	}
	if( testingListItem == 1 ){
		testListItem = (struct ListItem *)malloc(sizeof(struct ListItem));
		defineListItemFunctions();
		
		testListItem = ListItemCreate( testListItem, testThreadManagerCache );
	}
	if( testingLinkList == 1){
		testLinkList = (struct LinkList *)malloc(sizeof(struct LinkList));

		defineLinkListFunctions();
		testLinkList = LinkListCreate( testLinkList, testThreadManagerCache );
	}
	
	int maxtestlength = 1001;
	for( int testLength = 1000; testLength < maxtestlength; testLength = testLength * 10 ){
	
		for( int l = 0; l < 2 && l < testLength; ++l ){
			
			for( int i = 0; i < 1; ++i ){

				for( int j = l; j < testLength; ++j ){
					
					int r = rand();
					int sleep = floor(((float)100*(float)r)/(float)INT_MAX) * floor(((float)maxtestlength/(float)10000) / (float)testLength); 
					
					if(sleep > 0){
						linebuffer = (char *)malloc(200);
						sprintf(linebuffer, "usleep(%i):",sleep);
						writeToCharBuffer( screen, linebuffer );
						usleep(sleep);
					}
					
					
					if( i == 0 ){
						int * testValue;
						int * testValueTwo;
						int * testValueThree;
						if( testingDoubleVoid ){
							testValue = (int *)(malloc(sizeof(int)));
							*testValue = j;
						}
						if( testingListItem ){
							testValueTwo = (int *)(malloc(sizeof(int)));
							*testValueTwo = j;
						}
						if( testingLinkList ){
							testValueThree = (int *)(malloc(sizeof(int)));
							*testValueThree = j;
						}
						
						
						if( testingDoubleVoid == 1 ){
							int * dvtv = testValue;
							
							DoubleVoidKnock( testDoubleVoid );
							testDoubleVoid->func->push( testDoubleVoid, dvtv );
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer,"dv push(%i):%i ",j, *testValue); 
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}	
							DoubleVoidRelease( testDoubleVoid );
							
						}
						if( !(testingLinkList) && !(testingListItem) ){
							printf("\r");
						}
						if( testingListItem == 1 ){
							int * litv = testValueTwo;
							testListItem->func->push( testListItem, litv );
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer,"lipush(%i):%i ",j, *testValueTwo); 
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}	

						}
						if( !testingLinkList ){
							printf("\r");
						}
						if( testingLinkList == 1 ){
							int * lltv = testValueThree;
							testLinkList->func->push( testLinkList, lltv );
							/*printf("%p",testLinkList->lastItem);*/
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer,"llpush(%i):%i //\r",j, *testValueThree);
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}
						}
						
						/*free( testValue );*/
					}else if( i == 1 ){
						int * dvReturn = NULL;
						int * liReturn = NULL;
						int * llReturn = NULL;
						/*struct ListItem * poppedItem = NULL;*/
						if( testingDoubleVoid == 1 ){
							DoubleVoidKnock( testDoubleVoid );
							dvReturn = (int *)(testDoubleVoid->func->pop( testDoubleVoid, 1 ));
							DoubleVoidRelease( testDoubleVoid );
						}
						if( testingListItem == 1 ){
							liReturn = (int *)(testListItem->func->pop( testListItem, 1 ));
						}
						if( testingDoubleVoid == 1 ){
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer, "dvpop(%i):%i ",j,*dvReturn );
							free( dvReturn );
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}	

						}
						if( !(testingLinkList) && !(testingListItem) ){
							printf("\r");
						}
						if( testingListItem == 1){
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer, "lipop(%i):%i ", j, *liReturn );
							free( liReturn );
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}	

						}if( !testingLinkList ){
							printf("\r");
						}
						if( testingLinkList == 1 ){
							int * testIndex = (int *)malloc(sizeof(int));
							*testIndex = floor(((float)(testLinkList->listLength - 1)*(float)r)/(float)INT_MAX);
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer,"ll(%i): set(%i):get(%i) //\r",testLinkList->listLength, *testIndex, *testIndex);
							writeToCharBuffer( screen, linebuffer );
							testLinkList->func->set( testLinkList, *testIndex, testIndex );
							llReturn = (int *)ListItemGet((struct ListItem *)(testLinkList->func->get( testLinkList, *testIndex )), 0);
							/*printf("%i   \r",*llReturn);*/
							if(verbosity > 0){
								printf("\n");
							}
						}
						
						/*free(returnedTestValue);*/
					}else if( i == 2){
						int * testIndex;
						if(testingDoubleVoid){
							testIndex = (int*)malloc(sizeof(int));
							*testIndex = (testLength*(float)r)/(float)INT_MAX;
						}
						int * testIndexTwo;
						if(testingListItem){
							testIndexTwo = (int*)malloc(sizeof(int));
							*testIndexTwo = (testLength*(float)r)/(float)INT_MAX;
						}
						
						
						
						int * dvReturn = NULL;
						int * liReturn = NULL;
						int * llReturn = NULL;
						
						
						/*remember to cast to avoid integer math*/
						/*int testIndex = j*20;*/
						if( testingDoubleVoid == 1 ){
							DoubleVoidKnock( testDoubleVoid );
							testDoubleVoid->func->set( testDoubleVoid, *testIndex, testIndex );
							dvReturn = (int *)(testDoubleVoid->func->get( testDoubleVoid, *testIndex ));
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer, "dv: set(%i):get(%i):%i ", *testIndex, *testIndex, *dvReturn);
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}	

							DoubleVoidRelease( testDoubleVoid );
						}
						if( !(testingLinkList) && !(testingListItem) ){
							printf("\r");
						}
						if( testingListItem == 1 ){
							testListItem->func->set( testListItem, *testIndexTwo, testIndexTwo );
							liReturn = (int *)(testListItem->func->get( testListItem, *testIndexTwo ));
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer, "li: set(%i):get(%i):%i ", *testIndexTwo, *testIndexTwo, *liReturn);
							writeToCharBuffer( screen, linebuffer );
							if(verbosity > 0){
								printf("\n");
							}	

						}if( !testingLinkList ){
							printf("\r");
						}
						if( testingLinkList == 1 ){
							struct ListItem * returnedListItem =(struct ListItem *)(testLinkList->func->pop( testLinkList, 1 ));
							llReturn = (int *)ListItemPop(returnedListItem, 1);
							linebuffer=(char *)malloc(200);
							sprintf(linebuffer, "llpop(%i):%i //\r",j, *llReturn);
							writeToCharBuffer( screen, linebuffer );
							ListItemDestructRecursive( returnedListItem );
							if(verbosity > 0){
								printf("\n");
							}
						}
						
					}
				}
				linebuffer=(char *)malloc(200);
				sprintf(linebuffer, "\ntest %i offset %i length %i concluded \n", i, l, testLength);
				writeToCharBuffer( screen, linebuffer );
			}
		}
	}	
	if( testingDoubleVoid ){
		DoubleVoidDestructRecursive( testDoubleVoid );
		free( testDoubleVoid );
	}
	if( testingListItem ){
		ListItemDestructRecursive( testListItem );
	}
	if( testingLinkList ){
		LinkListDestructRecursive( testLinkList );
	}
}
/*pthread_kill( *((pthread_t *)(testThreadManagerCache->threadList)[0]), 1 );*/
	/*free((void*)testThreadManagerCache->queuePage);*/
	
	
	
sleep(10);

	
	
	pthread_mutex_lock( testThreadManagerCache->queueLock );
	(testThreadManagerCache->queuePage)[0].type = MEMOSHUTDOWN;
	pthread_mutex_unlock( testThreadManagerCache->queueLock );
	RollingCharBufferClose( screen );
	pthread_join( *(testThreadManagerCache->threadList[0]), NULL );
	
	return 0;
}
