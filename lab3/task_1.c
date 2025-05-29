#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	if (argc != 2){
		printf("Error: Too many or too little arguments passed in.");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	
	if (fp == NULL){
		printf("Error: Issue trying to open file.");
		return 1;
	}

	char *buff = NULL;
	ssize_t chars_read = 0;
	size_t buff_size = 0;
	
	char *last_line = NULL;
	char *second_last_line = NULL;
	
	while((chars_read = getline(&buff, &buff_size, fp)) != -1){
		free(second_last_line);
		second_last_line = last_line;
		last_line = buff;
		buff = NULL;
	}
	
	if (second_last_line){
		printf("%s", second_last_line);
		free(second_last_line);
	}
	
	if (last_line){
		printf("%s", last_line);
		free(last_line);
	}			

	free(buff);
	fclose(fp);
	return 0;
}
