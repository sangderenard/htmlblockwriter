#include <stdio.h>
#include <sys/time.h>
#include <limits.h>

#include "./htmldatatypes.c"


#define DIV "div"
#define ID "id="
#define STYLE "style="
#define CLASS "class="
#define MAXHTMLWORDLENGTH  50









/*
 * 
 * alright, I'm sleepy and I don't want to figure out tonight how to
 * get the features of printf's variable substitution to work with
 * my char buffer idea. I have some thoughts on how to do it, but
 * I don't want to start in on it now.
 * that's enough for tonight.
 * 
 */










char *divGrid(int width, int height, char style){
	return NULL;
}

int main(void) {
	
	RollingCharBuffer * screen;
	screen = initializeRollingCharBuffer( 500, NULL );
	pthread_t * printThread = (pthread_t *)malloc(sizeof(pthread_t));
	pthread_create(printThread, NULL, printScreen, (void *)screen);
	
	
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
	
	if( testingDoubleVoid == 1 ){
		testDoubleVoid = (struct ManagedDoubleVoid	*)malloc(sizeof(struct ManagedDoubleVoid));
		defineDoubleVoidFunctions();

		initializeDoubleVoid( testDoubleVoid, NULL, testThreadManagerCache );
	}
	/* end double void initialization process */
		
	struct ListItem * testListItem;
	
	if( testingListItem == 1 ){
		testListItem = (struct ListItem *)malloc(sizeof(struct ListItem));
		defineListItemFunctions();
		
		testListItem = ListItemCreate( testListItem, testThreadManagerCache );
	}
	
	
	struct LinkList	* testLinkList;
	struct ThreadManagerPostOfficeBox * testListListPostBox;
	
	if( testingLinkList == 1){
		testLinkList = (struct LinkList *)malloc(sizeof(struct LinkList));

		defineLinkListFunctions();
		testLinkList = LinkListCreate( testLinkList, testThreadManagerCache );
	}
	
	
	/*void * testObjects[] = { testDoubleVoid, testListItem, testLinkList };*/

for(int iterations = 0; iterations < 10; ++iterations){	
	int maxtestlength = 10000;
	for( int testLength = 1; testLength < maxtestlength; testLength = testLength * 10 ){
	
		for( int l = 0; l < 2 && l < testLength; ++l ){
			
			for( int i = 0; i < 3; ++i ){

				for( int j = l; j < testLength; ++j ){
					
					int r = rand();
					int sleep = floor(((float)100*(float)r)/(float)INT_MAX) * floor(((float)maxtestlength/(float)10000) / (float)testLength); 
					
					if(sleep > 0){
						printf("usleep(%i):",sleep);
						usleep(sleep);
					}
					
					
					if( i == 0 ){
						int * testValue = (int *)(malloc(sizeof(int)));
						*testValue = j;
						
						if( testingDoubleVoid == 1 ){
							int * dvtv = testValue;
							
							DoubleVoidKnock( testDoubleVoid );
							testDoubleVoid->func->push( testDoubleVoid, dvtv );
							
							printf("dv push(%i):%i ",j, *testValue); 
							if(verbosity > 0){
								printf("\n");
							}	
							DoubleVoidRelease( testDoubleVoid );
							
						}
						if( !(testingLinkList) && !(testingListItem) ){
							printf("\r");
						}
						if( testingListItem == 1 ){
							int * litv = testValue;
							testListItem->func->push( testListItem, litv );
							
							printf("lipush(%i):%i ",j, *testValue); 
							if(verbosity > 0){
								printf("\n");
							}	

						}
						if( !testingLinkList ){
							printf("\r");
						}
						if( testingLinkList == 1 ){
							int * lltv = testValue;
							testLinkList->func->push( testLinkList, lltv );
							/*printf("%p",testLinkList->lastItem);*/
							printf("llpush(%i):%i //\r",j, *testValue);
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
							printf("dvpop(%i):%i ",j,*dvReturn );
							if(verbosity > 0){
								printf("\n");
							}	

						}
						if( !(testingLinkList) && !(testingListItem) ){
							printf("\r");
						}
						if( testingListItem == 1){
							printf("lipop(%i):%i ", j, *liReturn );
							if(verbosity > 0){
								printf("\n");
							}	

						}if( !testingLinkList ){
							printf("\r");
						}
						if( testingLinkList == 1 ){
							int testIndex = floor(((float)(testLinkList->listLength - 1)*(float)r)/(float)INT_MAX);
							printf("ll(%i): set(%i):get(%i) //\r",testLinkList->listLength, testIndex, testIndex);
							testLinkList->func->set( testLinkList, testIndex, &testIndex );
							llReturn = (int *)ListItemGet((struct ListItem *)(testLinkList->func->get( testLinkList, testIndex )), 0);
							/*printf("%i   \r",*llReturn);*/
							if(verbosity > 0){
								printf("\n");
							}
						}
						
						/*free(returnedTestValue);*/
					}else if( i == 2){
						int testIndex = (testLength*(float)r)/(float)INT_MAX;
						int * dvReturn = NULL;
						int * liReturn = NULL;
						int * llReturn = NULL;
						
						
						/*remember to cast to avoid integer math*/
						/*int testIndex = j*20;*/
						if( testingDoubleVoid == 1 ){
							DoubleVoidKnock( testDoubleVoid );
							testDoubleVoid->func->set( testDoubleVoid, testIndex, &testIndex );
							dvReturn = (int *)(testDoubleVoid->func->get( testDoubleVoid, testIndex ));
							
							printf("dv: set(%i):get(%i):%i ", testIndex, testIndex, *dvReturn);
							if(verbosity > 0){
								printf("\n");
							}	

							DoubleVoidRelease( testDoubleVoid );
						}
						if( !(testingLinkList) && !(testingListItem) ){
							printf("\r");
						}
						if( testingListItem == 1 ){
							testListItem->func->set( testListItem, testIndex, &testIndex );
							liReturn = (int *)(testListItem->func->get( testListItem, testIndex ));
							printf("li: set(%i):get(%i):%i ", testIndex, testIndex, *liReturn);
							if(verbosity > 0){
								printf("\n");
							}	

						}if( !testingLinkList ){
							printf("\r");
						}
						if( testingLinkList == 1 ){
							llReturn = (int *)ListItemPop((struct ListItem *)(testLinkList->func->pop( testLinkList, 1 )), 1);
							printf("llpop(%i):%i //\r",j, *llReturn);
							if(verbosity > 0){
								printf("\n");
							}
						}
						
					}
				}
				printf("\ntest %i offset %i length %i concluded \n", i, l, testLength);
			}
		}
	}	
}

	DoubleVoidDestructRecursive( testDoubleVoid );
	return 0;
}
