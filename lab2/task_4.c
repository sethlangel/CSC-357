#include<stdio.h>

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Not enough arguments.\n");	
	}
	
	for(int i=0; i<argc; i++){
		if(argv[i][0] == '-'){
			printf("%s\n", argv[i]);
		}
	}

	return 0;
}
