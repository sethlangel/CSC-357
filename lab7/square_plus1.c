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
	
	char buff[256];	
	int num;
	int pipe1[2], pipe2[2], pipe3[2];
	pid_t child1, child2;

	if(pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1){
		perror("Pipe failed.\n");
		exit(0);
	}

	if((child1 = fork()) < 0){
		perror("Child1 Failed.\n");
		exit(0);
	}

	if(child1 == 0){
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe3[0]);
		close(pipe3[1]);

		while(1){
			if(read(pipe1[0], &num, sizeof(num)) <=0){
				break;
			}
			num *= num;
			write(pipe2[1], &num, sizeof(num));
		}

		close(pipe1[0]);
		close(pipe2[1]);
		exit(0);
	}
	
	if((child2 = fork()) < 0){
		perror("child2 failed.\n");
		exit(1);
	}

	if(child2 == 0){
		close(pipe1[0]);
		close(pipe2[1]);
		close(pipe3[0]);

		while(1){
			if(read(pipe2[0], &num, sizeof(num)) <= 0){
				break;
			}
			
			num++;
			write(pipe3[1], &num, sizeof(num));
		}
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe3[1]);
		exit(0);
	}

	close(pipe2[0]);
	close(pipe2[1]);
	
	while(fgets(buff, sizeof(buff), stdin) != NULL){
		if(sscanf(buff, "%d", &num) == 1){
			write(pipe1[1], &num, sizeof(num));

			read(pipe3[0], &num, sizeof(num));

			printf("Final: %d\n", num);
		}
	}
	
	close(pipe1[0]);
	close(pipe1[1]);
	close(pipe3[0]);
	close(pipe3[1]);

	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);

	return 0;
}

