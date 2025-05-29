#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
	if (argc != 3){
		printf("Error: Too many or not enough arguments passed in. (repeat.c [loopCount] [string]) \n");
		return 0;
	}

	char *endptr;
	long loopCount;

	loopCount = strtol(argv[1], &endptr, 10);	

	if (*endptr != '\0'){
		printf("Error: Invalid integer inputed. \n");
		return 0;
	}
	
	if (loopCount <= 0){
		printf("Error: The int you have inputted can not be negative \n");
		return 0;	
	}
	
	for (int i = 0; i < loopCount; i++){
		printf("%s \n", argv[2]);	
	} 
	
	return 0;
}
