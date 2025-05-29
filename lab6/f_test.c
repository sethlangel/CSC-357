#include<string.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/resource.h>
#define _GNU_SOURCE
void limit_fork(rlim_t max_procs){
	struct rlimit rl;
	
	if(getrlimit(RLIMIT_NPROC, &rl)){
		perror("getrlimit");
		exit(-1);
	}
	
	rl.rlim_cur = max_procs;
	
	if(setrlimit(RLIMIT_NPROC, &rl)){
		perror("setrlimit");
		exit(-1);
	}
}

int main(int argc, char *argv[]){
	limit_fork(50);
	
	if(argc > 2){
		printf("Error: Too many args.");
		return 1;
	}

	if(argc < 2){
		printf("Error: Not enough args.");
		return 1;
	}
	char* endptr;
	long n = strtol(argv[1], &endptr, 10);
	
	pid_t pid = fork();

	if(pid < 0){
		perror("Fork Failed.");
	}
	else if(pid == 0){
		for(int i = 1; i < n + 1; i++){
			if(i % 2 == 1){
				printf("%d\n", i);
			}
		}
		
		exit(0);
	}
	else{
		for(int i = 1; i < n + 1; i++){
			if(i % 2 == 0){
				printf("\t%d\n", i);
			}
		}
		
		wait(NULL);
	}
	

	return 0;
}
