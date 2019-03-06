#ifdef __cplusplus
extern "C" {
#endif


 
long findStringAmongStrings( const char ** const strings, const long stringsLength, const char * const string ){
	int targetLength = strlen(string);
	for(long i = 0; i < stringsLength; ++i){
		int searchedLength = strlen( strings[i] );
		if( searchedLength != targetLength ){
			continue;
		}else if( strings[i][0] != string[0]){
			continue;
		}else{
			int breakout = 0;
			for(int j = 1; !breakout && j < targetLength; ++j){
				if( strings[i][j] != string[j] ){
					breakout = 1;
				}
			}
			if(breakout == 1){
				continue;
			}
			
			return i;
		}
	}
	return -1;
}


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
	for(unsigned int i = 0; i < sourceSize; i++){
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


#ifdef __cplusplus
}
#endif

