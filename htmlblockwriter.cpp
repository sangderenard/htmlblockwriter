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
	
	int maxPageCount=20;
	int maxThreadCount=20;
	int memosPerPage=20;
	
	struct ThreadManagerCache * testThreadManagerCache;
	
	testThreadManagerCache =  InitializeTheThreadManager( maxPageCount, maxThreadCount, memosPerPage );
	
	/* double void initialization process */
	
	struct ManagedDoubleVoid * testDoubleVoid = (struct ManagedDoubleVoid	*)malloc(sizeof(struct ManagedDoubleVoid));
	struct ThreadManagerPostOfficeBox * testDoubleVoidPostBox = DoubleVoidThreadManagerHandshake( testDoubleVoid, testThreadManagerCache );
	defineDoubleVoidFunctions();
	pthread_mutex_lock( testDoubleVoid->myThreadControlLock );	
	initializeDoubleVoid( testDoubleVoid, NULL );
	testDoubleVoid->theCache = testThreadManagerCache;
	pthread_mutex_unlock( testDoubleVoid->myThreadControlLock );
	
	/* end double void initialization process */
		
	struct ListItem * testListItem = (struct ListItem *)malloc(sizeof(struct ListItem));
	struct ThreadManagerPostOfficeBox * testListItemPostBox = ListItemThreadManagerHandshake(  testListItem, testThreadManagerCache );
	defineListItemFunctions();
	
	testListItem = ListItemCreate( testListItem, testThreadManagerCache );
	
	/*
	*struct LinkList	* testLinkList = (struct LinkList *)malloc(sizeof(struct LinkList));
	*
	*struct ThreadManagerPostOfficeBox * testListListPostBox = LinkListThreadManagerHandshake( testLinkList, testThreadManagerCache );
	*/
	/*void * testObjects[] = { testDoubleVoid, testListItem, testLinkList };*/

	int testLength = 1000000;
	
	int verbosity = 0;
	
	for( int i = 0; i < 2; ++i ){

		for( int j = 0; j < testLength; ++j ){
			
			int r = rand();
			/*usleep((10*r)/INT_MAX);  */

			
			
			if( i == 0 ){
				int * testValue = (int *)(malloc(sizeof(int)));
				*testValue = j;
		/*		DoubleVoidKnock( testDoubleVoid );
		*		testDoubleVoid->func->push( testDoubleVoid, testValue );
		*		
		*		printf("push(%i):%i     \r",j, *testValue); 
		*		DoubleVoidRelease( testDoubleVoid );
		*/		
				testListItem->func->push( testListItem, testValue );
				
				/*free( testValue );*/
			}else if( i == 1 ){
				/*testDoubleVoid->func->pop( testDoubleVoid, 1 );*/
				/*DoubleVoidKnock( testDoubleVoid );
				*int * returnedTestValue = (int *)(testDoubleVoid->func->pop( testDoubleVoid, 1 ));
				
				*printf("pop(%i):%i       \r",j,*returnedTestValue );
				*DoubleVoidRelease( testDoubleVoid );
				*/
				
				int * returnedValue = (int *)(testListItem->func->pop( testListItem, 1 ));
				printf("%i        \r", *returnedValue );
				
				/*free(returnedTestValue);*/
			}else if( i == 2){
				int testIndex = (testLength*(float)r)/(float)INT_MAX;
				/*remember to cast to avoid integer math*/
				/*int testIndex = j*20;*/
				DoubleVoidKnock( testDoubleVoid );
				testDoubleVoid->func->set( testDoubleVoid, testIndex, &testIndex );
				int * returnedTestValue = (int *)(testDoubleVoid->func->get( testDoubleVoid, testIndex ));
				
				printf("set(%i):get(%i):%i         \r", testIndex, testIndex, *returnedTestValue);
				DoubleVoidRelease( testDoubleVoid );
			}
		
		}

		printf("\n");
	}
	
	
	return 0;
}
