#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#define _GNU_SOURC

int main(int argc, char *argv[]){
	if(argc > 3){
		printf("Error: Too many arguments. %s <program name> <name of file>\n", argv[0]);
		return 1;
	}
	
	if(argc < 3){
		printf("Error: Too little arguments. %s <program name> <name of file>\n", argv[0]);
		return 1;
	}

	int fd = open(argv[2], O_WRONLY | O_CREAT, 0644 );

	if(fd == -1){
		perror("Error: Issue opening or creating file.\n");
		return 1;
	}
	
	int backup_stdout;

	if((backup_stdout = dup(STDOUT_FILENO)) == -1){
		perror("Error: dup failed.\n");
		close(fd);
		return 1;
	}

	if(dup2(fd, STDOUT_FILENO) == -1){
		perror("Error: dup2 fd failed.\n");
		close(fd);
		return 1;
	}
	

	char *args[] = {argv[1], NULL};
	
	pid_t pid = fork();

	if(pid < 0){
		perror("Fork Failed.\n");		
	}
	else if(pid == 0){
		if(execvp(argv[1], args) == -1){
			perror("Error: Could not execute program.\n");
			exit(1);
		}
	}
	else{
		wait(NULL);
	}

	if(dup2(STDOUT_FILENO, backup_stdout) == -1){
		perror("dup2 STDOUT_FILENO failed.\n");
	}

	close(fd);
	return 0;
}
