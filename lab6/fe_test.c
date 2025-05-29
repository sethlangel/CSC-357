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
	
	pid_t pid1, pid2;
	
	pid1 = fork();

	if(pid1 < 0){
		perror("Fork Failed.");
	}
	else if(pid1 == 0){
		execl("./odds", "odds", argv[1], NULL);

		perror("Execl Failed.");
		exit(1);
	}
	else{
		pid2 = fork();

		if(pid2 < 0){
			perror("pid2 fork failed.");
		}
		else if(pid2 == 0){
			execl("./evens", "evens", argv[1], NULL);
			
			perror("Execl Failed");
			exit(1);
		}
		else{
			wait(NULL);
		}
		
		wait(NULL);
	}
	

	return 0;
}
