#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	if(argc > 2){
		printf("Error: Too many args.");
		return 1;
	}

	if(argc < 2){
		printf("Error: Not enough args.");
		return 1;
	}

	char *endptr;
	long n = strtol(argv[1], &endptr, 10);

	for(int i = 1; i < n + 1; i++){
		if(i % 2 == 0){
			printf("\t%d\n", i);
		}
	}

	return 0;
}
