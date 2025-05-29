#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	char *endptr;
	long num = strtol(argv[1], &endptr, 10);

	for(int i = 0; i < num; i++){
		printf("%s\n", argv[2]);
	} 

	return 0;
}
