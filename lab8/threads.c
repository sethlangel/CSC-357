#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#define _GNU_SOURCE

void PrintEven(int n){
	for(int i = 1; i < n + 1; i++){
		if(i % 2 == 0){
			printf("%d\n", i);
		}
	}
}


void PrintOdd(int n){
	for(int i = 1; i < n + 1; i++){
		if(i % 2 == 1){
			printf("\t%d\n", i);
		}
	}
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Invalid usage: ./threads <number>\n");
		exit(1);
	}

	char *endptr;
	int n = strtol(argv[1], &endptr, 10);

	pthread_t threads[2];
	int rc_e;
	int rc_o;
		
	rc_e = pthread_create(&threads[0], NULL, PrintEven, (void *) n);
	rc_o = pthread_create(&threads[1], NULL, PrintOdd, (void *) n);

	if(rc_e || rc_o){
		printf("Error: Pthread failed.\n");
		exit(1);
	}

	for(int i = 0; i < 2; i++){
		pthread_join(threads[i], NULL);
	}

	return 0;	
}
