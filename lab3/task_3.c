#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE 8192

int main(){
	FILE *fd = fopen("/usr/lib/locale/locale-archive", "r");

	if (fd == NULL){
		printf("Error: Issue when trying to open file.");
		return 1;
	}

	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	while((bytes_read = fread(buffer, BUFFER_SIZE, 1, fd)) > 0){
	}
	
	fclose(fd);
	return 0;
}
