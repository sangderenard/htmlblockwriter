#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "./cssdefs.h"

#define RATIORESOLVER 1

#define RESOLVERINT 1
#define RESOLVERFLOAT 2

struct CssValue
{
	void **resolverParameters;
	char resolverParameterType;
	char type;
	float numericValue;
	char *value;
	char unit[2];
	char resolverType;
	char *(*output)(const struct CssValue * const);
	void *(*input)(struct CssValue * const, const void * const);
	void *(*inputF)(struct CssValue * const, const float * const, const char * const);
	float (*numericResolver)(struct CssValue * const, void * const);
};

struct CssKeyValuePair
{
	char *key;
	char *value;
	struct CssValue cssValue;
	char *(*output)(const struct CssKeyValuePair * const);
	const char *(*input)(struct CssKeyValuePair * const, const char, const char * const);
	const char *(*setKey)(struct CssKeyValuePair * const, const char);
	char *(*renderValue)(struct CssKeyValuePair * const);
};

struct CssMargin
{
	struct CssKeyValuePair value;
	struct CssKeyValuePair marginBottom;
	struct CssKeyValuePair marginTop;
	struct CssKeyValuePair marginLeft;
	struct CssKeyValuePair marginRight;
	char *(*output)(struct CssMargin * const);
};

struct CssPadding
{
	struct CssKeyValuePair value;
	struct CssKeyValuePair paddingBottom;
	struct CssKeyValuePair paddingTop;
	struct CssKeyValuePair paddingLeft;
	struct CssKeyValuePair paddingRight;
	char *(*output)(struct CssPadding * const);
};

struct CssOutline
{
	
	struct CssKeyValuePair width;
	struct CssKeyValuePair style;
	struct CssKeyValuePair color;
	char *(*output)(struct CssOutline * const);
	char *(*renderValue)(struct CssOutline * const);
};

struct CssBorder
{
	struct CssKeyValuePair value;
	struct CssKeyValuePair borderLeftWidth;
	struct CssKeyValuePair borderRightWidth;
	struct CssKeyValuePair borderTopWidth;
	struct CssKeyValuePair borderBottomWidth;
	struct CssKeyValuePair borderLeftStyle;
	struct CssKeyValuePair borderRightStyle;
	struct CssKeyValuePair borderTopStyle;
	struct CssKeyValuePair borderBottomStyle;
	struct CssKeyValuePair borderLeftColor;
	struct CssKeyValuePair borderRightColor;
	struct CssKeyValuePair borderTopColor;
	struct CssKeyValuePair borderBottomColor;
	struct CssKeyValuePair borderRadius;
	struct CssKeyValuePair borderTopLeftRadius;
	struct CssKeyValuePair borderTopRightRadius;
	struct CssKeyValuePair borderBottomLeftRadius;
	struct CssKeyValuePair borderBottomRightRadius;
	char *(*output)(struct CssBorder * const);
	
};

struct CssBackground
{
	struct CssKeyValuePair backgroundAttachment;
	struct CssKeyValuePair backgroundBlendMode;
	struct CssKeyValuePair backgroundClip;
	struct CssKeyValuePair backgroundColor;
	struct CssKeyValuePair backgroundImage;
	struct CssKeyValuePair backgroundOrigin;
	struct CssKeyValuePair backgroundPosition;
	struct CssKeyValuePair backgroundRepeat;
	struct CssKeyValuePair backgroundSize;
	struct CssKeyValuePair mixBlendMode;
};

struct CssBoxShadow
{
	struct CssKeyValuePair value;
	struct CssValue hOffset;
	struct CssValue vOffset;
	struct CssValue blur;
	struct CssValue spread;
	struct CssValue color;
	char *option;
	char *(*output)(struct CssBoxShadow * const);
	struct CssBoxShadow *(*input)(struct CssBoxShadow * const, const void * const);
};

struct CssSize
{
	struct CssKeyValuePair width;
	struct CssKeyValuePair height;
	char *(*output)(struct CssSize * const);
};

struct CssPosition
{
	struct CssKeyValuePair position;
	struct CssKeyValuePair left;
	struct CssKeyValuePair top;
	struct CssKeyValuePair right;
	struct CssKeyValuePair bottom;
};

struct CssBoxOuterDressing
{
	struct CssMargin margin;
	struct CssOutline outline;
	struct CssBorder border;
	struct CssPadding padding;
	struct CssBoxShadow boxShadow;
	char *(*output)(struct CssBoxOuterDressing * const);

};

struct CssOverflow
{
	struct CssKeyValuePair overflow;
	struct CssKeyValuePair overflowWrap;
	struct CssKeyValuePair overflowX;
	struct CssKeyValuePair overflowY;
};

struct CssPerspective
{
	struct CssKeyValuePair perspective;
	struct CssKeyValuePair origin;
};

struct CssTransform
{
	struct CssKeyValuePair transform;
	struct CssKeyValuePair origin;
	struct CssKeyValuePair style;
};

struct CssTransition
{
	struct CssKeyValuePair transition;
	struct CssKeyValuePair delay;
	struct CssKeyValuePair duration;
	struct CssKeyValuePair property;
	struct CssKeyValuePair timingFunction;
};

struct CssBox
{
	struct CssSize size;
	struct CssSize maxSize;
	struct CssSize minSize;

	struct CssBoxOuterDressing dressing;

	struct CssPosition position;
	struct CssPerspective perspective;
		
	struct CssKeyValuePair display;
	struct CssKeyValuePair opacity;

	struct CssKeyValuePair filter;
	struct CssBackground background;
	struct CssKeyValuePair backfaceVisibility;

	struct CssKeyValuePair cursor;
	struct CssKeyValuePair pointerEvents;
	
	struct CssKeyValuePair lineBreak;
	struct CssKeyValuePair lineHeight;

	struct CssOverflow overflow;
	struct CssKeyValuePair resize;
	struct CssKeyValuePair scrollBehavior;
	
	struct CssTransform transform;
	struct CssTransition transition;
	struct CssKeyValuePair verticalAlign;
	struct CssKeyValuePair visibility;
	struct CssKeyValuePair whitespace;
	struct CssKeyValuePair zIndex;
};

struct CssShape
{
	float *dimensions;
	char* type;
	char (*output)(const struct CssShape*);
};

struct CssClip
{
	struct CssKeyValuePair value;
	struct CssShape shape;
	char (*output)(const struct CssClip*);
};

struct CssImage
{
	struct CssClip clip;
	struct CssKeyValuePair objectFit;
	struct CssKeyValuePair objectPosition;
};

struct CssFont
{
	struct CssKeyValuePair fontFamily;
	struct CssKeyValuePair fontFeatureSettings;
	struct CssKeyValuePair fontSize;
	struct CssKeyValuePair fontWeight;
};

struct CssPagebreak
{
	struct CssKeyValuePair before;
	struct CssKeyValuePair after;
	struct CssKeyValuePair inside;
};

struct CssTextShadow
{
	struct CssKeyValuePair hShadow;
	struct CssKeyValuePair vShadow;
	struct CssKeyValuePair blur;
	struct CssKeyValuePair color;
	struct CssKeyValuePair option;
	
};

struct CssTextDecoration
{
	struct CssKeyValuePair decoration;
	struct CssKeyValuePair color;
	struct CssKeyValuePair line;
	struct CssKeyValuePair style;
	struct CssTextShadow shadow;
};

struct CssText
{
	struct CssKeyValuePair caretColor;
	struct CssKeyValuePair color;
	struct CssFont font;
	struct CssKeyValuePair hyphens;
	struct CssPagebreak pagebreak;
	struct CssKeyValuePair tabSize;
	struct CssKeyValuePair textAlign;
	struct CssKeyValuePair textAlignLast;
	struct CssTextDecoration textDecoration;
	struct CssKeyValuePair indent;
	struct CssKeyValuePair justify;
	struct CssKeyValuePair orientation;
	struct CssKeyValuePair overflow;
	struct CssKeyValuePair textTransform;
	struct CssKeyValuePair userSelect;
	struct CssKeyValuePair wordBreak;
	struct CssKeyValuePair wordWrap;
	struct CssKeyValuePair writingMode;
};

struct CssStyle
{
	char * activeKeys;
	int activeKeyCount;
	char type;
	char * name;
	struct CssBox box;
	struct CssText text;
	struct CssStyle *imports;
	const struct CssKeyValuePair *(*setValueByKey)(struct CssStyle * const, const char, const void * const);
	const struct CssKeyValuePair *(*setFValueByKey)(struct CssStyle * const, const char, const float * const, const char * const);
	char *(*getValueByKey)(struct CssStyle * const, const char);
	char *(*output)(struct CssStyle * const);
	void *(*getElement)(struct CssStyle * const, const char, char *);
	char *(*printBlock)(struct CssStyle * const, const char * const, const int);
	char *(*printBlockDefault)(struct CssStyle * const);
};

char *buildCSSStyleBlock( const struct CssStyle style[] );

#ifdef __cplusplus
}
#endif
