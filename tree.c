#ifdef __cplusplus
extern "C" {
#endif

/*struct TreeNode{
*	struct TreeNode * parent;
*	struct TreeNode * previousSibling;
*	struct TreeNode * nextSibling;
*	struct TreeNode * firstChild;
*	void * contents;
*}
*
*writing:
* add child, 
* remove child but keep it in RAM, 
* remove child from RAM entirely (those are the same in other languages but different in C)
* 
*reading: get child, 
*get parent, 
*is this my parent, 
*is this my child, 
*if this is my parent what are my next and previous sibling,
*recurse tree looking for nodes where this callback is true
*/




void TreeAddChild( struct TreeNode * parent, void * contents ){
	struct TreeNode * newChild = (struct TreeNode *)malloc(sizeof(struct TreeNode));
	newChild->contents = contents;
	newChild->firstChild = NULL;
	newChild->nextSibling = NULL;
	newChild->parent = parent;
	struct TreeNode * lastChild = parent->firstChild;
	if( lastChild == NULL ){
		parent->firstChild = newChild;
		newChild->previousSibling = NULL;
		return;
	}
	while( lastChild->nextSibling != NULL ){
		lastChild = lastChild->nextSibling;
	}
	lastChild->nextSibling = newChild;
	newChild->previousSibling = lastChild;
}

void TreeRemoveAndDestroyAllContents( struct TreeNode * node ){
	
}

void TreeRemoveAndDestroyButLeaveContents( struct TreeNode * node, char doWhatWithChildContents, void * contentsReturn ){
	struct ManagedDoubleVoid * appendedReturns;
	if( doWhatWithChildContents == 1 ){
		appendedReturns = (struct ManagedDoubleVoid *)contentsReturn;
		if( node->contents != NULL ){
			appendedReturns->func->push( appendedReturns, node->contents );
		}
	}else{
		contentsReturn = node->contents;
	}
	if( node->firstChild != NULL ){
		struct TreeNode * currentNode = node->firstChild;
		while( currentNode != NULL ){
			struct TreeNode * nextNode = currentNode->nextSibling;
			
			void * childContents;
			
			if( doWhatWithChildContents == 1 ){
				childContents = malloc(sizeof(struct ManagedDoubleVoid));
				initializeDoubleVoid((struct ManagedDoubleVoid *)childContents, NULL, appendedReturns->theCache );
			}
			
			TreeRemoveAndDestroyButLeaveContents( currentNode, doWhatWithChildContents, childContents );
			
			if( childContents != NULL ){
				if(doWhatWithChildContents == -1){
					free( childContents );
				}else if(doWhatWithChildContents == 1){
					int endOfAppendedReturns = appendedReturns->length;
					int endOfChildContents = ((struct ManagedDoubleVoid *)childContents)->length;
					appendedReturns->func->splice( (void *)appendedReturns, endOfAppendedReturns, 0, childContents, 0, endOfChildContents );
				}
				
			}
			currentNode = nextNode;
		}
		
	}
}

struct TreeNode * TreeRemoveWithoutDestroy( struct TreeNode * node ){
	if( node->parent != NULL ){
		if( node->parent->firstChild == node ){
			node->parent->firstChild = node->nextSibling;
		}
	}
	if( node->previousSibling != NULL ){
		node->previousSibling->nextSibling = node->nextSibling;
	}
	if( node->nextSibling != NULL ){
		node->nextSibling->previousSibling = node->previousSibling;
	}
}



#ifdef __cplusplus
}
#endif
