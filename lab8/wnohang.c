#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#define _GNU_SOURCE

int child_exited = 0;

void signal_handler(int signum){	
	int status;
	while(1){	
		waitpid(-1, &status, WNOHANG);			
		if(WIFEXITED(status)){
			child_exited = 1;
			break;	
		}
	}
}

int main(){
	signal(SIGCHLD, signal_handler);

	pid_t pid;
	if((pid = fork()) < 0){
		perror("Error: Failed to create child.\n");
		exit(1);
	}
	else if(pid == 0){
		printf("Child pid: %d has started...\n", getpid());
		sleep(5);
		printf("Child is exiting...\n");
		exit(0);
	}
	else{	
		while(child_exited == 0){
			printf("Parent is working...\n");
			sleep(1);
		}

		printf("Printed from parent WNOHANG after child process %d has finished...\n", pid);
	}
	return 0;
}
