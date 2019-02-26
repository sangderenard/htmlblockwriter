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
	printf("<body style=\"padding-bottom: 2px; font-size: xx-small; white-space: nowrap;\">");

	char value[] = "inline-block";

	struct CssStyle testSix;
	initializeCssStyle(&testSix);

	float fValue = .5;
	float fValueTwo = 3200;
	float fValueThree = 0;
	float fValueFour = 9;
	
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
	
	struct HtmlBlock testHtml;
	initializeHtmlBlock( &testHtml, htmlTag, htmlId, htmlClass, &testSix, NULL, NULL, 0 );
	
	for(int i = 0; i < 200; i++){
		for(int j = 0; j < 200; j++){

			fValueFour = .5 * cos(i/100.0) * sin((i+j)/(5.0 + sin((i*j)/77.0))) / (80.0/j);
			fValueThree=(i*j)/(i*j+1);
			testSix.setFValueByKey(&testSix, CSSKEYOPACITY, &fValueFour, "");

			if(i%3 == 0){
				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorFour);
				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorOne);
				
			}
			if((i*j)%13 == 0){
				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorTwo);
				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorFour);
			}
			if(i%7 == 0){
				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorTwo);
				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorThree);
			}
			if(i%11 == 0){
				testSix.setValueByKey(&testSix, CSSKEYCOLOR, colorOne);
				testSix.setValueByKey(&testSix, CSSKEYBACKGROUNDCOLOR, colorThree);
			}
			

			result = testHtml.printBlock(&testHtml);
			printf("%s", result );
		
			free(result);


		}
			
		printf("<br>");	
			
	}

	printf("</body></html>");

	printf("\n");
	return 0;
}
