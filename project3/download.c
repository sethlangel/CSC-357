#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<fcntl.h>
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

	if(argc != 3){
		printf("Usage: %s <filename.txt> <max_process_count>\n", argv[0]);
		exit(1);
	}

	FILE *fp;

	if((fp = fopen(argv[1], "r")) == NULL){
		printf("Error: Failed to open file %s.\n", argv[1]);
		exit(1);
	}
	
	//Get the max process count from the arguments given by the user and check to see if it is a valid int by checking for 0.	
	char *endptr;
	long max_process_count = strtol(argv[2], &endptr, 10);	
	if(max_process_count < 1){
		printf("Error: Incorrect value for max process amount. Must be int greater than 0 Must be int greater than 0\n");
		exit(1);
	}
	
	char *read_line = NULL;
	size_t len = 0;
	ssize_t nread;
	
	int line_number = 0;	
	int total_processes_running = 0;
	char *filename, *url, *time;
	
	//We are running until we run out of lines to read in the file.
	while((nread = getline(&read_line, &len, fp)) != -1){
		line_number++;
	 	//Use strtok() to parse each argument of the line that is given in the .txt file.
		filename = strtok(read_line, " \n");
		if(filename == NULL){
			printf("Error: Could not parse filename.\n");
			exit(1);
		}

		url = strtok(NULL, " \n");
		if(url == NULL){
			printf("Error: Could not parse url.\n");
			exit(1);
		}

		time = strtok(NULL, " \n");
		if(time == NULL){
			time = "0";
		}
		//If a process can't be created due to the max amount being reached we will wait until a process finishes to then be able to start a new one.
		if(total_processes_running >= max_process_count){
			pid_t pid = wait(NULL);
			printf("Process %d finished.\n", pid);
			total_processes_running--;
		}
		
		pid_t pid;
		//Create a new child process, error check and then in the child we are running the curl command on the current line of the .txt file. In the parent we are printing out which child process is running and what line it is working on.
		if((pid = fork()) < 0){
			perror("Failed to fork.\n");
			exit(1);
		}
		else if(pid == 0){
			char *curl_args[] = {"curl", "-m", time, "-o", filename, "-s", url, NULL};	
			execvp("curl", curl_args);
			return -1;
		}
		else{
			printf("Process %d processing line #%d\n", pid, line_number);
			total_processes_running++;
		}
	}
	//Once we are out of the while loop we will wait for the rest of the processes to finish.	
	for(int i = 0; i < max_process_count; i++){
		pid_t pid = wait(NULL);
		if(pid >0)
			printf("Process %d finished.\n", pid);	
	}						

	free(read_line);
	fclose(fp);	

	return 0;
}
