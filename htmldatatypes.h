#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "./basicutils.c"
#include "./css.c"

#define HTMLDIV 0

struct HtmlBlock
{
	char *htmlTag;
	char *htmlId;
	char *htmlClass;
	struct CssStyle *htmlStyle;
	struct HtmlBlock *htmlParent;
	int orphan;
	struct HtmlBlock **htmlChildren;
	int childCount;
	char *(*printBlock)(struct HtmlBlock * const);
	
};


char *printWithChildren( const struct HtmlBlock topParent );

#ifdef __cplusplus
}
#endif
