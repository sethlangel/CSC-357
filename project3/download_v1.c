#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<fcntl.h>
#define _GNU_SOURCE

typedef struct{
	char filename[256];
	char url[256];
	char time[16];
} line_info;

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

void retrieve_list(line_info **lines, FILE *fp, int *total_lines){	
	char *read_line = NULL;
	size_t len = 0;
	ssize_t nread;
	
	int n = 0;
	while((nread = getline(&read_line, &len, fp)) != -1){
		line_info *line = (line_info*) malloc(sizeof(line_info));

		if(line == NULL){
			printf("Error: Malloc call failed when trying to create a line.\n");
			exit(1);
		}

		char *filename = strtok(read_line, " \n");
		if(filename == NULL){
			printf("Error: Could not parse filename.\n");
			exit(1);
		}
		strcpy(line->filename, filename);

		char *url = strtok(NULL, " \n");
		if(url == NULL){
			printf("Error: Could not parse url.\n");
		}
		strcpy(line->url, url);

		char *time = strtok(NULL, " \n");
		if(time != NULL){
			strcpy(line->time, time);
		}
		else{
			strcpy(line->time, "0");
		}
	
		lines[n] = line;
		n++;						
	}

	*total_lines = n;
	
	fclose(fp);
	free(read_line);	
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
		
	char *endptr;
	long max_process_count = strtol(argv[2], &endptr, 10);

	if(max_process_count < 1){
		printf("Error: Invalid input for max process amount. Must be int greater than 0.\n");
		exit(1);
	}

	int total_lines;
	line_info **lines;
	if((lines = (line_info**) malloc(sizeof(line_info*) * 10)) == NULL){
		printf("Error: Malloc call failed when trying to create lines.\n");
		exit(1);
	}
	retrieve_list(lines, fp, &total_lines);	
	
	int total_processes_created = 0;

	while(total_processes_created < total_lines){
		for(int i = 0; i < max_process_count; i++){
			if(total_processes_created < total_lines){
				pid_t pid;

				if((pid = fork()) < 0){
					perror("Failed to fork.\n");
					exit(1);
				}
				else if(pid == 0){
					char *curl_args[] = {"curl", "-m", lines[total_processes_created]->time, "-o", lines[total_processes_created]->filename, "-s", lines[total_processes_created]->url, NULL};	
					execvp("curl", curl_args);
					return -1;
				}
				else{
					printf("Process %d processing line #%d\n", pid, total_processes_created+1);
					total_processes_created++;
				}
			}
		}
		
		for(int i = 0; i < max_process_count; i++){
			pid_t pid = wait(NULL);
			if(pid > 0)
				printf("Process %d finished.\n", pid);
		}						
	}

	for(int i = 0; i < total_lines; i++){
		free(lines[i]);
	}
	
	free(lines);
	return 0;
}
