#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./css.h"


const char *cssEnumToKey(const char cssKey){
	const char * output;
	switch( cssKey ){
		case CSSKEYDISPLAY:
			output = CSSKEYDISPLAYSTRING;
			break;
		case CSSKEYWIDTH:
			output = CSSKEYWIDTHSTRING;
			break;
		case CSSKEYHEIGHT:
			output = CSSKEYHEIGHTSTRING;
			break;
		case CSSKEYMARGIN:
			output = CSSKEYMARGINSTRING;
			break;
		case CSSKEYOUTLINEWIDTH:
			output = CSSKEYOUTLINEWIDTHSTRING;
			break;
		case CSSKEYOUTLINESTYLE:
			output = CSSKEYOUTLINESTYLESTRING;
			break;
		case CSSKEYOUTLINECOLOR:
			output = CSSKEYOUTLINECOLORSTRING;
			break;
		case CSSKEYBORDER:
			output = CSSKEYBORDERSTRING;
			break;
		case CSSKEYBORDERRADIUS:
			output = CSSKEYBORDERRADIUSSTRING;
			break;
		case CSSKEYPADDING:
			output = CSSKEYPADDINGSTRING;
			break;
		case CSSKEYBOXSHADOW:
			output = CSSKEYBOXSHADOWSTRING;
			break;
		case CSSKEYMARGINBOTTOM:
			output = CSSKEYMARGINBOTTOMSTRING;
			break;
		case CSSKEYMARGINTOP:
			output = CSSKEYMARGINTOPSTRING;
			break;
		case CSSKEYMARGINLEFT:
			output = CSSKEYMARGINLEFTSTRING;
			break;
		case CSSKEYMARGINRIGHT:
			output = CSSKEYMARGINRIGHTSTRING;
			break;
		case CSSKEYPADDINGBOTTOM:
			output = CSSKEYPADDINGBOTTOMSTRING;
			break;
		case CSSKEYPADDINGTOP:
			output = CSSKEYPADDINGTOPSTRING;
			break;
		case CSSKEYPADDINGLEFT:
			output = CSSKEYPADDINGLEFTSTRING;
			break;
		case CSSKEYPADDINGRIGHT:
			output = CSSKEYPADDINGRIGHTSTRING;
			break;
		case CSSKEYOUTLINE:
			output = CSSKEYOUTLINESTRING;
			break;
		case CSSKEYBORDERLEFTWIDTH:
			output = CSSKEYBORDERLEFTWIDTHSTRING;
			break;
		case CSSKEYBORDERRIGHTWIDTH:
			output = CSSKEYBORDERRIGHTWIDTHSTRING;
			break;
		case CSSKEYBORDERTOPWIDTH:
			output = CSSKEYBORDERTOPWIDTHSTRING;
			break;
		case CSSKEYBORDERBOTTOMWIDTH:
			output = CSSKEYBORDERBOTTOMWIDTHSTRING;
			break;
		case CSSKEYBORDERLEFTSTYLE:
			output = CSSKEYBORDERLEFTSTYLESTRING;
			break;
		case CSSKEYBORDERRIGHTSTYLE:
			output = CSSKEYBORDERRIGHTSTYLESTRING;
			break;
		case CSSKEYBORDERTOPSTYLE:
			output = CSSKEYBORDERTOPSTYLESTRING;
			break;
		case CSSKEYBORDERBOTTOMSTYLE:
			output = CSSKEYBORDERBOTTOMSTYLESTRING;
			break;
		case CSSKEYBORDERLEFTCOLOR:
			output = CSSKEYBORDERLEFTCOLORSTRING;
			break;
		case CSSKEYBORDERRIGHTCOLOR:
			output = CSSKEYBORDERRIGHTCOLORSTRING;
			break;
		case CSSKEYBORDERTOPCOLOR:
			output = CSSKEYBORDERTOPCOLORSTRING;
			break;
		case CSSKEYBORDERBOTTOMCOLOR:
			output = CSSKEYBORDERBOTTOMCOLORSTRING;
			break;
		case CSSKEYBORDERTOPLEFTRADIUS:
			output = CSSKEYBORDERTOPLEFTRADIUSSTRING;
			break;
		case CSSKEYBORDERTOPRIGHTRADIUS:
			output = CSSKEYBORDERTOPRIGHTRADIUSSTRING;
			break;
		case CSSKEYBORDERBOTTOMLEFTRADIUS:
			output = CSSKEYBORDERBOTTOMLEFTRADIUSSTRING;
			break;
		case CSSKEYBORDERBOTTOMRIGHTRADIUS:
			output = CSSKEYBORDERBOTTOMRIGHTRADIUSSTRING;
			break;
		case CSSKEYBACKGROUND:
			output = CSSKEYBACKGROUNDSTRING;
			break;
		case CSSKEYBACKGROUNDATTACHMENT:
			output = CSSKEYBACKGROUNDATTACHMENTSTRING;
			break;
		case CSSKEYBACKGROUNDBLENDMODE:
			output = CSSKEYBACKGROUNDBLENDMODESTRING;
			break;
		case CSSKEYBACKGROUNDCLIP:
			output = CSSKEYBACKGROUNDCLIPSTRING;
			break;
		case CSSKEYBACKGROUNDCOLOR:
			output = CSSKEYBACKGROUNDCOLORSTRING;
			break;
		case CSSKEYBACKGROUNDIMAGE:
			output = CSSKEYBACKGROUNDIMAGESTRING;
			break;
		case CSSKEYBACKGROUNDORIGIN:
			output = CSSKEYBACKGROUNDORIGINSTRING;
			break;
		case CSSKEYBACKGROUNDPOSITION:
			output = CSSKEYBACKGROUNDPOSITIONSTRING;
			break;
		case CSSKEYBACKGROUNDREPEAT:
			output = CSSKEYBACKGROUNDREPEATSTRING;
			break;
		case CSSKEYBACKGROUNDSIZE:
			output = CSSKEYBACKGROUNDSIZESTRING;
			break;
		case CSSKEYMIXBLENDMODE:
			output = CSSKEYMIXBLENDMODESTRING;
			break;
		case CSSKEYSIZE:
			output = CSSKEYSIZESTRING;
			break;
		case CSSKEYPOSITION:
			output = CSSKEYPOSITIONSTRING;
			break;
		case CSSKEYLEFT:
			output = CSSKEYLEFTSTRING;
			break;
		case CSSKEYTOP:
			output = CSSKEYTOPSTRING;
			break;
		case CSSKEYRIGHT:
			output = CSSKEYRIGHTSTRING;
			break;
		case CSSKEYBOTTOM:
			output = CSSKEYBOTTOMSTRING;
			break;
		case CSSKEYOUTERDRESSING:
			output = CSSKEYOUTERDRESSINGSTRING;
			break;
		case CSSKEYOVERFLOW:
			output = CSSKEYOVERFLOWSTRING;
			break;
		case CSSKEYOVERFLOWWRAP:
			output = CSSKEYOVERFLOWWRAPSTRING;
			break;
		case CSSKEYOVERFLOWX:
			output = CSSKEYOVERFLOWXSTRING;
			break;
		case CSSKEYOVERFLOWY:
			output = CSSKEYOVERFLOWYSTRING;
			break;
		case CSSKEYPERSPECTIVE:
			output = CSSKEYPERSPECTIVESTRING;
			break;
		case CSSKEYPERSPECTIVEORIGIN:
			output = CSSKEYPERSPECTIVEORIGINSTRING;
			break;
		case CSSKEYTRANSFORM:
			output = CSSKEYTRANSFORMSTRING;
			break;
		case CSSKEYTRANSFORMORIGIN:
			output = CSSKEYTRANSFORMORIGINSTRING;
			break;
		case CSSKEYTRANSFORMSTYLE:
			output = CSSKEYTRANSFORMSTYLESTRING;
			break;
		case CSSKEYTRANSITION:
			output = CSSKEYTRANSITIONSTRING;
			break;
		case CSSKEYTRANSITIONDELAY:
			output = CSSKEYTRANSITIONDELAYSTRING;
			break;
		case CSSKEYTRANSITIONDURATION:
			output = CSSKEYTRANSITIONDURATIONSTRING;
			break;
		case CSSKEYTRANSITIONPROPERTY:
			output = CSSKEYTRANSITIONPROPERTYSTRING;
			break;
		case CSSKEYTRANSITIONTIMINGFUNCTION:
			output = CSSKEYTRANSITIONTIMINGFUNCTIONSTRING;
			break;
		case CSSKEYBOX:
			output = CSSKEYBOXSTRING;
			break;
		case CSSKEYMAXSIZE:
			output = CSSKEYMAXSIZESTRING;
			break;
		case CSSKEYMINSIZE:
			output = CSSKEYMINSIZESTRING;
			break;
		case CSSKEYOPACITY:
			output = CSSKEYOPACITYSTRING;
			break;
		case CSSKEYFILTER:
			output = CSSKEYFILTERSTRING;
			break;
		case CSSKEYBACKFACEVISIBILITY:
			output = CSSKEYBACKFACEVISIBILITYSTRING;
			break;
		case CSSKEYCURSOR:
			output = CSSKEYCURSORSTRING;
			break;
		case CSSKEYPOINTEREVENTS:
			output = CSSKEYPOINTEREVENTSSTRING;
			break;
		case CSSKEYLINEBREAK:
			output = CSSKEYLINEBREAKSTRING;
			break;
		case CSSKEYLINEHEIGHT:
			output = CSSKEYLINEHEIGHTSTRING;
			break;
		case CSSKEYRESIZE:
			output = CSSKEYRESIZESTRING;
			break;
		case CSSKEYSCROLLBEHAVIOR:
			output = CSSKEYSCROLLBEHAVIORSTRING;
			break;
		case CSSKEYVERTICALALIGN:
			output = CSSKEYVERTICALALIGNSTRING;
			break;
		case CSSKEYVISIBILITY:
			output = CSSKEYVISIBILITYSTRING;
			break;
		case CSSKEYWHITESPACE:
			output = CSSKEYWHITESPACESTRING;
			break;
		case CSSKEYZINDEX:
			output = CSSKEYZINDEXSTRING;
			break;
		case CSSKEYCLIP:
			output = CSSKEYCLIPSTRING;
			break;
		case CSSKEYIMAGE:
			output = CSSKEYIMAGESTRING;
			break;
		case CSSKEYCLIPOBJECTFIT:
			output = CSSKEYCLIPOBJECTFITSTRING;
			break;
		case CSSKEYCLIPOBJECTPOSITION:
			output = CSSKEYCLIPOBJECTPOSITIONSTRING;
			break;
		case CSSKEYFONT:
			output = CSSKEYFONTSTRING;
			break;
		case CSSKEYFONTFAMILY:
			output = CSSKEYFONTFAMILYSTRING;
			break;
		case CSSKEYFONTFEATURESETTINGS:
			output = CSSKEYFONTFEATURESETTINGSSTRING;
			break;
		case CSSKEYFONTSIZE:
			output = CSSKEYFONTSIZESTRING;
			break;
		case CSSKEYFONTWEIGHT:
			output = CSSKEYFONTWEIGHTSTRING;
			break;
		case CSSKEYPAGEBREAK:
			output = CSSKEYPAGEBREAKSTRING;
			break;
		case CSSKEYPAGEBREAKBEFORE:
			output = CSSKEYPAGEBREAKBEFORESTRING;
			break;
		case CSSKEYPAGEBREAKAFTER:
			output = CSSKEYPAGEBREAKAFTERSTRING;
			break;
		case CSSKEYPAGEBREAKINSIDE:
			output = CSSKEYPAGEBREAKINSIDESTRING;
			break;
		case CSSKEYTEXTSHADOW:
			output = CSSKEYTEXTSHADOWSTRING;
			break;
		case CSSKEYTEXTDECORATION:
			output = CSSKEYTEXTDECORATIONSTRING;
			break;
		case CSSKEYTEXTDECORATIONCOLOR:
			output = CSSKEYTEXTDECORATIONCOLORSTRING;
			break;
		case CSSKEYTEXTDECORATIONLINE:
			output = CSSKEYTEXTDECORATIONLINESTRING;
			break;
		case CSSKEYTEXTDECORATIONSTYLE:
			output = CSSKEYTEXTDECORATIONSTYLESTRING;
			break;
		case CSSKEYTEXTDECORATIONSHADOW:
			output = CSSKEYTEXTDECORATIONSHADOWSTRING;
			break;
		case CSSKEYTEXT:
			output = CSSKEYTEXTSTRING;
			break;
		case CSSKEYCARETCOLOR:
			output = CSSKEYCARETCOLORSTRING;
		case CSSKEYCOLOR:
			output = CSSKEYCOLORSTRING;
			break;
		case CSSKEYHYPHENS:
			output = CSSKEYHYPHENSSTRING;
			break;
		case CSSKEYTABSIZE:
			output = CSSKEYTABSIZESTRING;
			break;
		case CSSKEYTEXTALIGN:
			output = CSSKEYTEXTALIGNSTRING;
			break;
		case CSSKEYTEXTALIGNLAST:
			output = CSSKEYTEXTALIGNLASTSTRING;
			break;
		case CSSKEYINDENT:
			output = CSSKEYINDENTSTRING;
			break;
		case CSSKEYJUSTIFY:
			output = CSSKEYJUSTIFYSTRING;
			break;
		case CSSKEYTEXTORIENTATION:
			output = CSSKEYTEXTORIENTATIONSTRING;
			break;
		case CSSKEYTEXTOVERFLOW:
			output = CSSKEYTEXTOVERFLOWSTRING;
			break;
		case CSSKEYTEXTTRANFORM:
			output = CSSKEYTEXTTRANFORMSTRING;
			break;
		case CSSKEYUSERSELECT:
			output = CSSKEYUSERSELECTSTRING;
			break;
		case CSSKEYWORDBREAK:
			output = CSSKEYWORDBREAKSTRING;
			break;
		case CSSKEYWORDWRAP:
			output = CSSKEYWORDWRAPSTRING;
			break;
		case CSSKEYWRITINGMODE:
			output = CSSKEYWRITINGMODESTRING;
			break;
	}
	return output;
}

char *CssKeyValuePairOutput(const struct CssKeyValuePair * const me){
	if(me->key == NULL || me->value == NULL){
		return NULL;
	}else if(me->key[0] == '\0' || me->value[0] == '\0'){
		return NULL;
	}
	
	char * keyCopy = stringCopy(me->key);
	char * valueCopy = stringCopy(me->value);
	char * strings[] = { keyCopy, valueCopy };
	char *output;
	output = stringArrayCombine(strings, 2, ':', ';');

	
	return output;
}

char *CssOutlineRenderCssValue(struct CssOutline * const me){
	me->width.renderValue(&(me->width));
	me->style.renderValue(&(me->style));
	me->color.renderValue(&(me->color));	
	
	return 0;
}

char *CssKeyValuePairRenderCssValue(struct CssKeyValuePair * const me){
	char * renderedValue = me->cssValue.output(&(me->cssValue));
	free(me->value);

	me->value = renderedValue;
	return renderedValue;
}

const char *CssKeyValuePairSetKey(struct CssKeyValuePair * const me, const char cssKey){
	free(me->key);
	me->key = stringCopy(cssEnumToKey(cssKey));
	return me->key;
}

const char *CssKeyValuePairInput(struct CssKeyValuePair * const me , const char isKey, const char * const newValue){
	if(isKey == '1'){
		free(me->key);
		me->key = stringCopy(newValue);
		return me->key;
	}else if(isKey == '0'){
		free(me->value);
		me->value = stringCopy(newValue);
		return me->value;
	}else{
		return NULL;	
	}
	return NULL;
}

float CssValueDefaultResolver(struct CssValue * const me, volatile void * const params){
	return 0;
}

struct CssValue *CssValueSetRatioResolver(struct CssValue * const me, float * parameterList[4]){
	me->resolverType = RATIORESOLVER;
	me->resolverParameterType = RESOLVERFLOAT;
	me->resolverParameters = (volatile void **)parameterList;
	return me;
}

char *CssValueOutput(const struct CssValue * const me){

	/*char * thisStringValue;*/
	
	float thisNumericValue = me->numericValue;
	
	if( me->resolverType != 0 ){
		if( me->resolverType == RATIORESOLVER ){
			if( me->resolverParameterType  == RESOLVERINT ){
				
			}else if( me->resolverParameterType == RESOLVERFLOAT ){
				
				float ** parameters = (float **)(me->resolverParameters);
				float * ratioA = parameters[0];
				float * ratioB = parameters[1];
				float * offsetA = parameters[2];
				float * offsetB = parameters[3];
				thisNumericValue = (*ratioA * (thisNumericValue + *offsetA) / *ratioB) + *offsetB;
			}
		}
		
		
	}else{
		
	}
	
	if( me->type == 's' ){
		return stringCopy(me->value);
	}
	int unitSize;
	if( me->unit[0] == 'p' ){
		unitSize = 2;
	}else if( me->unit[0] == '%' ){
		unitSize = 1;
	}else if( me->unit[0] == '\0' ){
		unitSize = 0;
	}
	
	int outputSize;
	char * output;                     
	if( me->type == 'f' ){
		int powersOfTen = 1;
		while((int)pow((double)10, (double)powersOfTen) <= fabs(thisNumericValue)){
			++powersOfTen;
		}
		
		int endOfNumber = powersOfTen + 1 + CSSPRECISION;
		int stringSize = endOfNumber + unitSize;
		outputSize = stringSize + 1;
		output = (char *) malloc(outputSize);
		/*printf("\n\nI am expecting a buffer of size %i\n\n", outputSize);*/
		/*alright, I'll be back if there's something else I wanna record for now the problem is solved*/
		
		snprintf(output, powersOfTen + 1 + CSSPRECISION + 1, "%."CSSPRECISIONSTRING"f", thisNumericValue);
		
		
		for(int i = endOfNumber, j = 0; i < stringSize; ++i, ++j){
			output[i] = me->unit[j];
		}
		output[stringSize] = '\0';
	}
	
	return output;
}

void initializeCssValue(struct CssValue * const, const char, const char * const);

void *CssValueInput(struct CssValue * const me, const void * const newValue)
{
	
	if(me->type == 'f'){
		me->numericValue = *(float*)newValue;
		return (void*)(&(me->numericValue));
	}else if(me->type == 's'){
		free(me->value);
		me->value = stringCopy((const char * const)newValue);
	}
	
	return NULL;
}

void *CssValueFloatInput(struct CssValue * const me, const float * const newValue, const char * const  unit)
{
	me->type = 'f';
	
	for(unsigned int i = 0; i < strlen(unit) && i < 2; i++){
		if(i < strlen(unit)){
			me->unit[i] = unit[i];
		}else{
			me->unit[i] = '\0';
		}
	}
	
	me->input(me, (void *)newValue);
	return (void *)&(me->numericValue);
}

char *CssMarginOutput(struct CssMargin * const me){
	char * output;
	output = me->value.output(&(me->value));
	return output;
}
char *CssOutlineOutput(struct CssOutline * const me){
	char * widthOutput = me->width.output(&(me->width));
	char * styleOutput = me->style.output(&(me->style));
	char * colorOutput = me->color.output(&(me->color));
	char * output;
	char * sources[] = {widthOutput, styleOutput, colorOutput};
	output = stringArrayCombine( sources, 3, '\0', '\0');
	return output;
}
char *CssBorderOutput(struct CssBorder * const me){
	char * output;
	output = me->value.output(&(me->value));
	return output;
}
char *CssPaddingOutput(struct CssPadding * const me){
	char * output;
	output = me->value.output(&(me->value));
	return output;
}

char *CssBoxOuterDressingOutput(struct CssBoxOuterDressing * const me){
	me->margin.value.renderValue(&(me->margin.value));
	me->outline.renderValue(&(me->outline));
	me->border.value.renderValue(&(me->border.value));
	me->padding.value.renderValue(&(me->padding.value));
	me->boxShadow.value.renderValue(&(me->boxShadow.value));
	
	char * marginOutput;
	char * outlineOutput;
	/*char * borderOutput;
	*char * paddingOutput;
	*char * boxShadowOutput;
	*/
	marginOutput = me->margin.value.output(&(me->margin.value));
	outlineOutput = me->outline.output(&(me->outline));
	/*borderOutput = me->border.output(&(me->border));
	*paddingOutput = me->padding.output(&(me->padding));
	*boxShadowOutput = me->boxShadow.output(&(me->boxShadow));
	*
	*char * sources[] = { marginOutput, outlineOutput , borderOutput, paddingOutput, boxShadowOutput };
	*char * output = stringArrayCombine(sources, 4, '\0', '\0');
	*/
	
	char * sources[] = { marginOutput, outlineOutput };
	char * output = stringArrayCombine(sources, 2, '\0', '\0');
		
	return output;	
	
	return NULL;
}

char *CssSizeOutput(struct CssSize * const me){
	me->height.renderValue(&(me->height));
	me->width.renderValue(&(me->width));
	const char * heightOutput;
	heightOutput = me->height.output(&(me->height));
	if(heightOutput == NULL){
		heightOutput = "";
	}
	const char * widthOutput;
	widthOutput = me->width.output(&(me->width));
	if(widthOutput == NULL){
		widthOutput = "";
	}
	char * output;
	int heightSize = strlen(heightOutput);
	int outputSize = heightSize + strlen(widthOutput);
	++outputSize;
	output = (char *)malloc((size_t)outputSize);
	for(int i = 0, j=0; i < outputSize; ++i){
		if(i < heightSize){
			output[i] = heightOutput[i];
		}else{
			output[i] = widthOutput[j++];
		}
	}
	return output;
}

char *CssStyleOutput(struct CssStyle * const me){
	return 0;
}

char *CssStylePrintBlock(struct CssStyle * const me, const char * const keys, const int length){
	char * preappendedOutput[length];
	
	for(int i = 0; i < length; i++){
		
		char * newLine = me->getValueByKey(me, (char)keys[i]);
		
		preappendedOutput[i] = newLine;
	}
	
	
	return stringArrayCombine(preappendedOutput, length, '\0', '\0');
	 
}

char *CssStylePrintBlockDefault(struct CssStyle * const me){
	return CssStylePrintBlock(me, me->activeKeys, me->activeKeyCount);
}

char *CssStyleGetByKey(struct CssStyle * const me, const char cssKey){

	char * output;
	const struct CssKeyValuePair * target = (const struct CssKeyValuePair *)(me->getElement(me, cssKey, NULL));
	output = target->output(target);
	
	return output;
}

void initializeCssKeyValuePair(struct CssKeyValuePair * const );

const struct CssKeyValuePair *CssStyleSetFByKey(struct CssStyle * const me, const char cssKey, const float * const value, const char * const unitString){
	struct CssKeyValuePair * target = (struct CssKeyValuePair * )(me->getElement(me, cssKey, NULL));
	
	if( addWithoutDuplicate(&cssKey, &(me->activeKeys), &(me->activeKeyCount)) == 1){
		initializeCssKeyValuePair(target);
		target->setKey(target, cssKey);
	}
	
	target->cssValue.inputF(&(target->cssValue), value, unitString);
	target->renderValue(target);
	return target;
}

const struct CssKeyValuePair *CssStyleSetByKey(struct CssStyle * const me, const char cssKey, const void * const value){
	struct CssKeyValuePair * target = (struct CssKeyValuePair * )(me->getElement(me, cssKey, NULL));
	
	if( addWithoutDuplicate(&cssKey, &(me->activeKeys), &(me->activeKeyCount)) == 1){
		initializeCssKeyValuePair(target);
		target->setKey(target, cssKey);
	}
	
	target->cssValue.input(&(target->cssValue), value);
	target->renderValue(target);
	return target;
}

void * CssStyleEnumToKeyAndElement(struct CssStyle * const me, const char cssKey, char * keyValue){
	void * output;
	if( keyValue != NULL ){
		keyValue = stringCopy(cssEnumToKey(cssKey));
	}
	switch( cssKey ){
		case CSSKEYDISPLAY:
			output = &(me->box.display);
			break;
		case CSSKEYWIDTH:
			output = &(me->box.size.width);
			break;
		case CSSKEYHEIGHT:
			output = &(me->box.size.height);
			break;
		case CSSKEYMARGIN:
			output = &(me->box.dressing.margin);
			break;
		case CSSKEYOUTLINEWIDTH:
			output = &(me->box.dressing.outline.width);
			break;
		case CSSKEYOUTLINESTYLE:
			output = &(me->box.dressing.outline.style);
			break;
		case CSSKEYOUTLINECOLOR:
			output = &(me->box.dressing.outline.color);
			break;
		case CSSKEYBORDER:
			output = &(me->box.dressing.border);
			break;
		case CSSKEYBORDERRADIUS:
			output = &(me->box.dressing.border.borderRadius);
			break;
		case CSSKEYPADDING:
			output = &(me->box.dressing.padding);
			break;
		case CSSKEYBOXSHADOW:
			output = &(me->box.dressing.boxShadow);
			break;
		case CSSKEYMARGINBOTTOM:
			output = &(me->box.dressing.margin.marginBottom);
			break;
		case CSSKEYMARGINTOP:
			output = &(me->box.dressing.margin.marginTop);
			break;
		case CSSKEYMARGINLEFT:
			output = &(me->box.dressing.margin.marginLeft);
			break;
		case CSSKEYMARGINRIGHT:
			output = &(me->box.dressing.margin.marginRight);
			break;
		case CSSKEYPADDINGBOTTOM:
			output = &(me->box.dressing.padding.paddingBottom);
			break;
		case CSSKEYPADDINGTOP:
			output = &(me->box.dressing.padding.paddingTop);
			break;
		case CSSKEYPADDINGLEFT:
			output = &(me->box.dressing.padding.paddingLeft);
			break;
		case CSSKEYPADDINGRIGHT:
			output = &(me->box.dressing.padding.paddingRight);
			break;
		case CSSKEYOUTLINE:
			output = &(me->box.dressing.outline);
			break;
		case CSSKEYBORDERLEFTWIDTH:
			output = &(me->box.dressing.border.borderLeftWidth);
			break;
		case CSSKEYBORDERRIGHTWIDTH:
			output = &(me->box.dressing.border.borderRightWidth);
			break;
		case CSSKEYBORDERTOPWIDTH:
			output = &(me->box.dressing.border.borderTopWidth);
			break;
		case CSSKEYBORDERBOTTOMWIDTH:
			output = &(me->box.dressing.border.borderBottomWidth);
			break;
		case CSSKEYBORDERLEFTSTYLE:
			output = &(me->box.dressing.border.borderLeftStyle);
			break;
		case CSSKEYBORDERRIGHTSTYLE:
			output = &(me->box.dressing.border.borderRightStyle);
			break;			
		case CSSKEYBORDERTOPSTYLE:
			output = &(me->box.dressing.border.borderTopStyle);
			break;
		case CSSKEYBORDERBOTTOMSTYLE:
			output = &(me->box.dressing.border.borderBottomStyle);
			break;
		case CSSKEYBORDERLEFTCOLOR:
			output = &(me->box.dressing.border.borderLeftColor);
			break;
		case CSSKEYBORDERRIGHTCOLOR:
			output = &(me->box.dressing.border.borderRightColor);
			break;
		case CSSKEYBORDERTOPCOLOR:
			output = &(me->box.dressing.border.borderTopColor);
			break;
		case CSSKEYBORDERBOTTOMCOLOR:
			output = &(me->box.dressing.border.borderBottomColor);
			break;
		case CSSKEYBORDERTOPLEFTRADIUS:
			output = &(me->box.dressing.border.borderTopLeftRadius);
			break;
		case CSSKEYBORDERTOPRIGHTRADIUS:
			output = &(me->box.dressing.border.borderTopRightRadius);
			break;
		case CSSKEYBORDERBOTTOMLEFTRADIUS:
			output = &(me->box.dressing.border.borderBottomLeftRadius);
			break;
		case CSSKEYBORDERBOTTOMRIGHTRADIUS:
			output = &(me->box.dressing.border.borderBottomRightRadius);
			break;
		case CSSKEYBACKGROUND:
			output = &(me->box.background);
			break;
		case CSSKEYBACKGROUNDATTACHMENT:
			output = &(me->box.background.backgroundAttachment);
			break;
		case CSSKEYBACKGROUNDBLENDMODE:
			output = &(me->box.background.backgroundBlendMode);
			break;
		case CSSKEYBACKGROUNDCLIP:
			output = &(me->box.background.backgroundClip);
			break;
		case CSSKEYBACKGROUNDCOLOR:
			output = &(me->box.background.backgroundColor);
			break;
		case CSSKEYBACKGROUNDIMAGE:
			output = &(me->box.background.backgroundImage);
			break;
		case CSSKEYBACKGROUNDORIGIN:
			output = &(me->box.background.backgroundOrigin);
			break;
		case CSSKEYBACKGROUNDPOSITION:
			output = &(me->box.background.backgroundPosition);
			break;
		case CSSKEYBACKGROUNDREPEAT:
			output = &(me->box.background.backgroundRepeat);
			break;
		case CSSKEYBACKGROUNDSIZE:
			output = &(me->box.background.backgroundSize);
			break;
		case CSSKEYMIXBLENDMODE:
			output = &(me->box.background.mixBlendMode);
			break;
		case CSSKEYSIZE:
			output = &(me->box.size);
			break;
		case CSSKEYPOSITION:
			output = &(me->box.position);
			break;
		case CSSKEYLEFT:
			output = &(me->box.position.left);
			break;
		case CSSKEYTOP:
			output = &(me->box.position.top);
			break;
		case CSSKEYRIGHT:
			output = &(me->box.position.right);
			break;
		case CSSKEYBOTTOM:
			output = &(me->box.position.bottom);
			break;
		case CSSKEYOUTERDRESSING:
			output = &(me->box.dressing);
			break;
		case CSSKEYOVERFLOW:
			output = &(me->box.overflow);
			break;
		case CSSKEYOVERFLOWWRAP:
			output = &(me->box.overflow.overflowWrap);
			break;
		case CSSKEYOVERFLOWX:
			output = &(me->box.overflow.overflowX);
			break;
		case CSSKEYOVERFLOWY:
			output = &(me->box.overflow.overflowY);
			break;
		case CSSKEYPERSPECTIVE:
			output = &(me->box.perspective);
			break;
		case CSSKEYPERSPECTIVEORIGIN:
			output = &(me->box.perspective.origin);
			break;
		case CSSKEYTRANSFORM:
			output = &(me->box.transform);
			break;
		case CSSKEYTRANSFORMORIGIN:
			output = &(me->box.transform.origin);
			break;
		case CSSKEYTRANSFORMSTYLE:
			output = &(me->box.transform.style);
			break;
		case CSSKEYTRANSITION:
			output = &(me->box.transition);
			break;
		case CSSKEYTRANSITIONDELAY:
			output = &(me->box.transition.delay);
			break;
		case CSSKEYTRANSITIONDURATION:
			output = &(me->box.transition.duration);
			break;
		case CSSKEYTRANSITIONPROPERTY:
			output = &(me->box.transition.property);
			break;
		case CSSKEYTRANSITIONTIMINGFUNCTION:
			output = &(me->box.transition.timingFunction);
			break;
		case CSSKEYBOX:
			output = &(me->box);
			break;
		case CSSKEYMAXSIZE:
			output = &(me->box.maxSize);
			break;
		case CSSKEYMINSIZE:
			output = &(me->box.minSize);
			break;
		case CSSKEYOPACITY:
			output = &(me->box.opacity);
			break;
		case CSSKEYFILTER:
			output = &(me->box.filter);
			break;
		case CSSKEYBACKFACEVISIBILITY:
			output = &(me->box.backfaceVisibility);
			break;
		case CSSKEYCURSOR:
			output = &(me->box.cursor);
			break;
		case CSSKEYPOINTEREVENTS:
			output = &(me->box.pointerEvents);
			break;
		case CSSKEYLINEBREAK:
			output = &(me->box.lineBreak);
			break;
		case CSSKEYLINEHEIGHT:
			output = &(me->box.lineHeight);
			break;
		case CSSKEYRESIZE:
			output = &(me->box.resize);
			break;
		case CSSKEYSCROLLBEHAVIOR:
			output = &(me->box.scrollBehavior);
			break;
		case CSSKEYVERTICALALIGN:
			output = &(me->box.verticalAlign);
			break;
		case CSSKEYVISIBILITY:
			output = &(me->box.visibility);
			break;
		case CSSKEYWHITESPACE:
			output = &(me->box.whitespace);
			break;
		case CSSKEYZINDEX:
			output = &(me->box.zIndex);
			break;
		case CSSKEYCLIP:
			output = NULL;
			break;
		case CSSKEYIMAGE:
			output = NULL;
			break;
		case CSSKEYCLIPOBJECTFIT:
			output = NULL;
			break;
		case CSSKEYCLIPOBJECTPOSITION:
			output = NULL;
			break;
		case CSSKEYFONT:
			output = &(me->text.font);
			break;
		case CSSKEYFONTFAMILY:
			output = &(me->text.font.fontFamily);
			break;
		case CSSKEYFONTFEATURESETTINGS:
			output = &(me->text.font.fontFeatureSettings);
			break;
		case CSSKEYFONTSIZE:
			output = &(me->text.font.fontSize);
			break;
		case CSSKEYFONTWEIGHT:
			output = &(me->text.font.fontWeight);
			break;
		case CSSKEYPAGEBREAK:
			output = &(me->text.pagebreak);
			break;
		case CSSKEYPAGEBREAKBEFORE:
			output = &(me->text.pagebreak.before);
			break;
		case CSSKEYPAGEBREAKAFTER:
			output = &(me->text.pagebreak.after);
			break;
		case CSSKEYPAGEBREAKINSIDE:
			output = &(me->text.pagebreak.inside);
			break;
		case CSSKEYTEXTSHADOW:
			output = NULL;
			break;
		case CSSKEYTEXTDECORATION:
			output = &(me->text.textDecoration);
			break;
		case CSSKEYTEXTDECORATIONCOLOR:
			output = &(me->text.textDecoration.color);
			break;
		case CSSKEYTEXTDECORATIONLINE:
			output = &(me->text.textDecoration.line);
			break;
		case CSSKEYTEXTDECORATIONSTYLE:
			output = &(me->text.textDecoration.style);
			break;
		case CSSKEYTEXTDECORATIONSHADOW:
			output = NULL;
			break;
		case CSSKEYTEXT:
			output = &(me->text);
			break;
		case CSSKEYCARETCOLOR:
			output = &(me->text.caretColor);
			break;
		case CSSKEYCOLOR:
			output = &(me->text.color);
			break;
		case CSSKEYHYPHENS:
			output = &(me->text.hyphens);
			break;
		case CSSKEYTABSIZE:
			output = &(me->text.tabSize);
			break;
		case CSSKEYTEXTALIGN:
			output = &(me->text.textAlign);
			break;
		case CSSKEYTEXTALIGNLAST:
			output = &(me->text.textAlignLast);
			break;
		case CSSKEYINDENT:
			output = &(me->text.indent);
			break;
		case CSSKEYJUSTIFY:
			output = &(me->text.justify);
			break;
		case CSSKEYTEXTORIENTATION:
			output = NULL;
			break;
		case CSSKEYTEXTOVERFLOW:
			output = &(me->text.overflow);
			break;
		case CSSKEYTEXTTRANFORM:
			output = &(me->text.textTransform);
			break;
		case CSSKEYUSERSELECT:
			output = &(me->text.userSelect);
			break;
		case CSSKEYWORDBREAK:
			output = &(me->text.wordBreak);
			break;
		case CSSKEYWORDWRAP:
			output = &(me->text.wordWrap);
			break;
		case CSSKEYWRITINGMODE:
			output = &(me->text.writingMode);
			break;
	}
	return output;
}


void initializeCssValue(struct CssValue * const me, const char type, const char * const unit){
	me->value = stringCopy("\0");
	me->type = type;
	me->resolverType = '\0';
	int unitLength = strlen(unit);
	for(int i = 0; i <= unitLength; ++i){
		me->unit[i] = unit[i];
	} 
	
	
	if(type == 'f'){
		
	}
	
	me->input = &CssValueInput;
	me->output = &CssValueOutput;
	me->inputF = &CssValueFloatInput;
	me->numericResolver = &CssValueDefaultResolver;

}


void initializeCssKeyValuePair(struct CssKeyValuePair * const me){
	me->value = stringCopy("\0");
	me->key = stringCopy("\0");
	me->input = &CssKeyValuePairInput;
	me->output = &CssKeyValuePairOutput;
	me->renderValue = &CssKeyValuePairRenderCssValue;
	me->setKey = &CssKeyValuePairSetKey;
	initializeCssValue(&(me->cssValue),'s',"");
}

void initializeCssMargin(struct CssMargin * const me){
	initializeCssKeyValuePair(&(me->value));
	me->value.setKey(&(me->value), CSSKEYMARGIN);
	initializeCssKeyValuePair(&(me->marginBottom));
	me->marginBottom.setKey(&(me->marginBottom), CSSKEYMARGINBOTTOM);
	initializeCssKeyValuePair(&(me->marginTop));
	me->marginTop.setKey(&(me->marginTop), CSSKEYMARGINTOP);
	initializeCssKeyValuePair(&(me->marginLeft));
	me->marginLeft.setKey(&(me->marginLeft), CSSKEYMARGINLEFT);
	initializeCssKeyValuePair(&(me->marginRight));
	me->marginRight.setKey(&(me->marginRight), CSSKEYMARGINRIGHT);
	me->output = &CssMarginOutput;
}


void initializeCssOutline(struct CssOutline * const me){
	initializeCssKeyValuePair(&(me->width));
	me->width.setKey(&(me->width), CSSKEYOUTLINEWIDTH);
	initializeCssKeyValuePair(&(me->style));
	me->style.setKey(&(me->style), CSSKEYOUTLINESTYLE);
	initializeCssKeyValuePair(&(me->color));
	me->color.setKey(&(me->color), CSSKEYOUTLINECOLOR);
	me->output = &CssOutlineOutput;
	me->renderValue = &CssOutlineRenderCssValue;
}


void initializeCssBorder(struct CssBorder * const me){
	initializeCssKeyValuePair(&(me->value));
	me->value.setKey(&(me->value), CSSKEYBORDER);
	initializeCssKeyValuePair(&(me->borderLeftWidth));
	me->borderLeftWidth.setKey(&(me->borderLeftWidth), CSSKEYBORDERLEFTWIDTH);
	initializeCssKeyValuePair(&(me->borderRightWidth));
	me->borderRightWidth.setKey(&(me->borderRightWidth), CSSKEYBORDERRIGHTWIDTH);
	initializeCssKeyValuePair(&(me->borderTopWidth));
	me->borderTopWidth.setKey(&(me->borderTopWidth), CSSKEYBORDERTOPWIDTH);
	initializeCssKeyValuePair(&(me->borderBottomWidth));
	me->borderBottomWidth.setKey(&(me->borderBottomWidth), CSSKEYBORDERBOTTOMWIDTH);
	initializeCssKeyValuePair(&(me->borderLeftStyle));
	me->borderLeftStyle.setKey(&(me->borderLeftStyle), CSSKEYBORDERLEFTSTYLE);
	initializeCssKeyValuePair(&(me->borderRightStyle));
	me->borderRightStyle.setKey(&(me->borderRightStyle), CSSKEYBORDERRIGHTSTYLE);
	initializeCssKeyValuePair(&(me->borderTopStyle));
	me->borderTopStyle.setKey(&(me->borderTopStyle), CSSKEYBORDERTOPSTYLE);
	initializeCssKeyValuePair(&(me->borderBottomStyle));
	me->borderBottomStyle.setKey(&(me->borderBottomStyle), CSSKEYBORDERBOTTOMSTYLE);
	initializeCssKeyValuePair(&(me->borderLeftColor));
	me->borderLeftColor.setKey(&(me->borderLeftColor), CSSKEYBORDERLEFTCOLOR);
	initializeCssKeyValuePair(&(me->borderRightColor));
	me->borderRightColor.setKey(&(me->borderRightColor), CSSKEYBORDERRIGHTCOLOR);
	initializeCssKeyValuePair(&(me->borderTopColor));
	me->borderTopColor.setKey(&(me->borderTopColor), CSSKEYBORDERTOPCOLOR);
	initializeCssKeyValuePair(&(me->borderBottomColor));
	me->borderBottomColor.setKey(&(me->borderBottomColor), CSSKEYBORDERBOTTOMCOLOR);
	initializeCssKeyValuePair(&(me->borderRadius));
	me->borderRadius.setKey(&(me->borderRadius), CSSKEYBORDERRADIUS);
	initializeCssKeyValuePair(&(me->borderTopLeftRadius));
	me->borderTopLeftRadius.setKey(&(me->borderTopLeftRadius), CSSKEYBORDERTOPLEFTRADIUS);
	initializeCssKeyValuePair(&(me->borderTopRightRadius));
	me->borderTopRightRadius.setKey(&(me->borderTopRightRadius), CSSKEYBORDERTOPRIGHTRADIUS);
	initializeCssKeyValuePair(&(me->borderBottomLeftRadius));
	me->borderBottomLeftRadius.setKey(&(me->borderBottomLeftRadius), CSSKEYBORDERBOTTOMLEFTRADIUS);
	initializeCssKeyValuePair(&(me->borderBottomRightRadius));
	me->borderBottomRightRadius.setKey(&(me->borderBottomRightRadius), CSSKEYBORDERBOTTOMRIGHTRADIUS);
}


void initializeCssPadding(struct CssPadding * const me){
		initializeCssKeyValuePair(&(me->value));
		me->value.setKey(&(me->value), CSSKEYPADDING);
		initializeCssKeyValuePair(&(me->paddingLeft));
	me->paddingLeft.setKey(&(me->paddingLeft), CSSKEYPADDINGLEFT);
		initializeCssKeyValuePair(&(me->paddingRight));
	me->paddingRight.setKey(&(me->paddingRight), CSSKEYPADDINGRIGHT);
		initializeCssKeyValuePair(&(me->paddingTop));
	me->paddingTop.setKey(&(me->paddingTop), CSSKEYPADDINGTOP);
		initializeCssKeyValuePair(&(me->paddingBottom));
	me->paddingBottom.setKey(&(me->paddingBottom), CSSKEYPADDINGBOTTOM);
}


void initializeCssBoxShadow(struct CssBoxShadow * const me){
	initializeCssKeyValuePair(&(me->value));
	me->value.setKey(&(me->value), CSSKEYBOXSHADOW);
	initializeCssValue(&(me->hOffset), 'f', "px");
	initializeCssValue(&(me->vOffset), 'f', "px");
	initializeCssValue(&(me->blur), 'f', "px");
	initializeCssValue(&(me->spread), 'f', "px");
	initializeCssValue(&(me->color), 's', "");
	
}


void initializeCssBoxOuterDressing(struct CssBoxOuterDressing * const me){
	initializeCssMargin(&(me->margin));
	initializeCssOutline(&(me->outline));
	initializeCssBorder(&(me->border));
	initializeCssPadding(&(me->padding));
	initializeCssBoxShadow(&(me->boxShadow));
	me->output = &CssBoxOuterDressingOutput;
}

void initializeCssSize(struct CssSize * const me){
	initializeCssKeyValuePair(&(me->height));
	me->height.setKey(&(me->height), CSSKEYHEIGHT);
	initializeCssKeyValuePair(&(me->width));
	me->width.setKey(&(me->width), CSSKEYWIDTH);
	me->output = &CssSizeOutput;
}

void initializeCssBox(struct CssBox * const me){
	initializeCssSize(&(me->size));
	initializeCssBoxOuterDressing(&(me->dressing));
	initializeCssKeyValuePair(&(me->display));
	me->display.setKey(&(me->display), CSSKEYDISPLAY);
	initializeCssKeyValuePair(&(me->background.backgroundColor));
	me->background.backgroundColor.setKey(&(me->background.backgroundColor), CSSKEYBACKGROUNDCOLOR);
}



void initializeCssStyle(struct CssStyle * const me){
	char newActiveKeys[] = "\0";
	me->activeKeys = newActiveKeys;
	me->activeKeyCount = 0;
	/*initializeCssBox(&(me->box));*/
	me->setFValueByKey = &CssStyleSetFByKey;
	me->setValueByKey = &CssStyleSetByKey;
	me->getValueByKey = &CssStyleGetByKey;
	me->output = &CssStyleOutput;
	me->getElement = &CssStyleEnumToKeyAndElement;
	me->printBlock = &CssStylePrintBlock;
	me->printBlockDefault = &CssStylePrintBlockDefault;
}



char *buildCSSStyleBlock( const struct CssStyle style[] ){
	int arrayLength = sizeof(const struct CssStyle ) / sizeof(struct CssStyle);
	
	for ( int i = 0; i < arrayLength; ++i ){
			return NULL;
	}
	
	return NULL;
}


#ifdef __cplusplus
}
#endif
