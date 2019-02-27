#include <stdio.h>

#include "./htmldatatypes.c"

#define DIV "div"
#define ID "id="
#define STYLE "style="
#define CLASS "class="
#define MAXHTMLWORDLENGTH  50


char *divGrid(int width, int height, char style){
	
}

int main(void) {
	printf("<html><head><meta charset='utf-8'></head>");
	printf("<body style=\"padding-bottom: 2px; font-size: 0px; white-space: nowrap;\">");

	char value[] = "inline-block";

	struct CssStyle testSix;
	initializeCssStyle(&testSix);

	float fValue = .5;
	float fValueTwo = 3200;
	float fValueThree = 0;
	float fValueFour = 1;
	
	float *testParameters[4] = { &fValue, &fValueTwo, &fValueThree, &fValueFour };
	
	char * result;
		
	char stylesToPrint[] = { CSSKEYMARGINLEFT, CSSKEYWIDTH, CSSKEYHEIGHT, CSSKEYMARGIN, CSSKEYDISPLAY };
	testSix.setFValueByKey(&testSix, CSSKEYOPACITY, &fValue, "");
	CssValueSetRatioResolver(&(testSix.box.opacity.cssValue), testParameters);
	testSix.setFValueByKey(&testSix, CSSKEYWIDTH, &fValueFour, "px");
	testSix.setFValueByKey(&testSix, CSSKEYHEIGHT, &fValueFour, "px");
	testSix.setValueByKey(&testSix, CSSKEYDISPLAY, value);
	fValueFour = 0;
	
	
	char colorOne[] = "Red";
	char colorTwo[] = "Blue";
	char colorThree[] = "Yellow";
	char colorFour[] = "Green";
	
	char htmlTag[] = "DIV";
	char htmlId[] = "thisismyid";
	char htmlClass[] = "thisismyclass";
	
	struct LinkList * newLinkList;
	newLinkList = LinkListCreate( NULL );
	printf("created a linked list of length %i\n",newLinkList->listLength);
/*	ListItemPush(newLinkList->firstItem, &testSix);*/
		
	struct HtmlBlock testHtml;
	initializeHtmlBlock( &testHtml, htmlTag, htmlId, htmlClass, &testSix, NULL, NULL, 0 );
	
	printf("creating a void** item...\n");
	
	volatile void ** newListContents = (volatile void **)malloc(sizeof(void *));
/*	newListContents[0] = &testHtml;*/
newListContents = (volatile void **)testParameters;
	
	printf("pushing new item...\n");
	printf("the link list object is at %p\n", newLinkList);
	LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
	LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
		LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
/*	
*	printf("\n%i\n",newLinkList->listLength);
*	printf("I'm packing float** %p into a list item. its first value is %f at %p\n", testParameters, (*testParameters)[0], *testParameters);
*/
	/*ListItemPush( newLinkList->lastItem, testParameters );*/
/*	
*	printf("\n\n\n\nvoid* entry is: %p\n", *((void**)ListItemGet(newLinkList->lastItem, 1)));
*	printf("dereferenced it is: %p %i %f\n", *((void**)ListItemGet(newLinkList->lastItem, 1)),*((void**)ListItemGet(newLinkList->lastItem, 1)),*((void**)ListItemGet(newLinkList->lastItem, 1)));
*	
*	void ** recoveredarray = (void **)ListItemGet(newLinkList->lastItem, 1);
*	printf("I have recovered the void* %p\n", recoveredarray);
*	
*	float ** recoveredFloatList = (float**)(recoveredarray);
*	printf("%p:%p\n", testParameters[1], recoveredarray[1]);
*	printf("%f\n",*testParameters[1]);
*
*/

	LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
		LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
			LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );



/*
 * 
 * behavior of the dynamic array and linked list is currently as expected as implemented
 * considerable effort will need to be expended in noticing why things work now
 * and what has been left behind from previous ideas of how it should work
 * 
 * maybe make a goddamn chart telling you that *pointer is the value at a pointer
 * because you can't seem to fucking remember that.
 */




	
	/*printf("%f:%f:%f\n\n\n\n\n\n\n", fValueTwo, *testParameters[1], *(float*)recoveredarray[1]);*/
	
	for(int i = 0; i < 500; i++){
		for(int j = 0; j < 800; j++){

			/*fValueFour = .5 * cos(i/100.0) * sin((i+j)/(5.0 + sin((i*j)/77.0))) / (80.0/j);*/
			/*fValueThree=(i*j)/(i*j+1);*/
			/*testSix.setFValueByKey(&testSix, CSSKEYOPACITY, &fValueFour, "");*/
/*
*			if(i%3 == 0){
*				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorFour);
*				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorOne);
*				
*			}
*			if((i*j)%13 == 0){
*				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorTwo);
*				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorFour);
*			}
*			if(i%7 == 0){
*				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorTwo);
*				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorThree);
*			}
*			if(i%11 == 0){
*				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorOne);
*				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorThree);
*			}
*
*/			
LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
	result = testSix.printBlockDefault(&testSix);
	
	/*testHtml.printBlock(&testHtml);		*/
			
			
			/*printf("%s", result );*/
		
			/*void ** newStringContents = (void **)malloc(sizeof(void *));
			*newStringContents[0] = &result;
		*/
		/*	LinkListPush(newLinkList, LINKLISTBASIC, newStringContents, sizeof(char*), 1);*/
		
		/*
		*	LinkListPush(newLinkList, LINKLISTBASIC, newListContents, sizeof(struct HtmlBlock *), 1 );
		*/
			
		
			/*free(result);*/


		}
			
		/*printf("<br>");	*/
			
	}

/*	printf("</body></html>");
*
*	printf("\n");
*/
	return 0;
}
