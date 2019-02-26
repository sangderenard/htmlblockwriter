#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./basicutils.h"

char *stringCopy(const char * const source){
	size_t sourceSize = strlen(source);
	if( sourceSize < 1 ){
		char * output = (char *)malloc(1);
		output[0]='\0';
		return output;
	}
	++sourceSize;
	char * output;
	output = (char *)malloc(sourceSize);
	for(int i = 0; i < sourceSize; i++){
		output[i] = source[i];
	}
	return output;
}

char *stringCombine(char * stringOne, char * stringTwo, const char middleChar, const char endChar){
	if( stringOne[0] == '\0' ){
		if( stringTwo[0] == '\0' ){
			char * output = stringCopy("\0");
			return output;
		}
		return stringTwo;
	}else if( stringTwo[0] == '\0' ){
		return stringOne;
	}
	int stringOneSize = (int)strlen(stringOne);
	int stringTwoSize = (int)strlen(stringTwo);
	int middleCharSize = 0;
	if( middleChar != '\0' ){
		middleCharSize = 1;
	}
	int endCharSize = 0;
	if( endChar != '\0' ){
		endCharSize = 1;
	}
	
	int middleSize = stringOneSize + middleCharSize;
	int combinedSize = middleSize + stringTwoSize; 
	int stringSize = combinedSize + endCharSize;
	int outputSize = stringSize + 1;

	char * output = (char *)malloc((size_t)outputSize);
	
	for(int i = 0, j=0; i < outputSize; ++i){
		if(i < stringOneSize){
			output[i] = stringOne[i];
		}else if(i < middleSize){
			output[i] = middleChar;
		}else if(i < combinedSize){
			output[i] = stringTwo[j++];
		}else if(i < stringSize){
			output[i] = endChar;
		}else{
			output[i] = '\0';
		}
	}
free(stringTwo);

	return output;
}

char *stringArrayCombine(char * * strings, int length, const char middleChar, const char endChar){
	char * output = stringCopy("\0");
	int stringWritten = 0;
	for(int i = 0; i < length; ++i){
		if(strings[i] == '\0'){
			continue;
		}
		char * newOutput = stringCombine(output, strings[i], middleChar, endChar);
		free(output);
		output = newOutput;
		++stringWritten;
	}
	if(stringWritten == 0){
		return output;
	}
	return output;
}


const char addWithoutDuplicate(const char * const value, char ** array, int * size){
	/*if(*size > 6){
	*	printf("%p %i\n", size, *size);
	*	exit(1);
	*}
	* */
	int newSize = *size + 1;
	char * oldArray = *array;
	char * newArray = (char *)malloc(newSize);

	for(int i = 0; i < *size; ++i){
		if( oldArray[i] == *value ){
			free(newArray);
		/*	printf("this one would be a duplicate \"%i\":\"%i\":\"%i\"\n", oldArray[i], *value, *size);
		*	exit(1);
		*/
			return '\0';
		}
		/*printf("before:  i:\"%i\" *value:\"%i\" array[%i]:\"%i\"\n", i, *value, i, oldArray[i]);*/
		newArray[i] = oldArray[i];
		/*printf("after:   i:\"%i\" *value:\"%i\" array[%i]:\"%i\" newarray[%i]:\"%i\"\n", i, *value, i, oldArray[i], i, newArray[i]);*/
	}
	newArray[*size] = *value;
/*	
*		for(int i = 0; i < newSize; i++){
*		printf("array: %i\n", oldArray[i]);
*	}
*		for(int i = 0; i < newSize; i++){
*		printf("newarray: %i\n", newArray[i]);
*	}
*	
*	printf("%p\n", oldArray);
*/
/*	free(*array);*/
	*array = newArray;
/*	printf("newSize: \"%i\"\n", newSize);
*	printf("%i:%i\n", (*array)[*size], newArray[*size]);
*/
	*size = newSize;
	
/*	for(int i = 0; i < *size; i++){
*		printf("recap: %i\n", (*array)[i]);
*	}
*/	
/*	printf("%p\n", *array);*/
	return '\1';
}

char *packWithChildren( const struct StringTree trunk ) {
	return NULL;
}



#ifdef __cplusplus
}
#endif
