#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "./htmldatatypes.h"

#define HTMLOPENOPEN "<"
#define HTMLOPENCLOSE ">"
#define HTMLCLOSEOPEN "</"
#define HTMLCLOSECLOSE ">"


char * HtmlPrintBlock(struct HtmlBlock * const me){
	/*size_t tagSize = strlen(me->htmlTag);
	*size_t idSize = strlen(me->htmlId);
	*size_t classSize = strlen(me->htmlClass);
	*/
	
	char * styleBlock;
	styleBlock = me->htmlStyle->printBlockDefault(me->htmlStyle);
	
	char * output;
	
	char * styleStart = stringCopy("style=\"");
	char * styleEnd = stringCopy("\"");
		
	char * simpleStrings[] = { styleStart, styleBlock, styleEnd };
	
	char * styleTag = stringArrayCombine(simpleStrings, 3, '\0', '\0');

	char * htmlOpen = stringCopy("<div id=\"");
	char * idString = stringCopy(me->htmlId);
	char * htmlMiddle = stringCopy("\" ");
	char * htmlClose = stringCopy(">&#x1F609;</div>");
	
	char * htmlBlock[] = { htmlOpen, idString, htmlMiddle, styleTag, htmlClose };

	output = stringArrayCombine(htmlBlock, 5, '\0', '\0');
	
	return output;
}


struct HtmlBlock * initializeHtmlBlock(struct HtmlBlock * const me, char * newTag, char * newId, char * newClass, struct CssStyle * htmlStyle, struct HtmlBlock * htmlParent, struct HtmlBlock * * htmlChildren, const int childCount){
	me->printBlock = &HtmlPrintBlock;
	
	if(htmlChildren != NULL){
		me->htmlChildren = htmlChildren;
		me->childCount = childCount;
	}else{
		me->childCount = 0;
		me->htmlChildren = NULL;
	}if(htmlParent != NULL){
		me->htmlParent = htmlParent;
		me->orphan = 0;
	}else{
		me->htmlParent = NULL;
		me->orphan = 1;
	}if(htmlStyle != NULL){
		me->htmlStyle = htmlStyle;
	}else{
		initializeCssStyle(me->htmlStyle);
	}if(newTag != NULL){
		me->htmlTag = newTag;
	}if(newId != NULL){
		me->htmlId = newId;
	}if(newClass != NULL){
		me->htmlClass = newClass;
	}
	
	return me;
}






#ifdef __cplusplus
}
#endif
