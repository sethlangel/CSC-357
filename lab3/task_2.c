#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFFER_SIZE 8192

int main(){
	int fd = open("/usr/lib/locale/locale-archive", O_RDONLY);

	if (fd == -1){
		perror("Error: Issue when trying to open file.");
		return 1;
	}

	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	while((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0){
	}
	
	if (bytes_read == -1){
		perror("Error: Failed to read from file.");
		exit(1);
	}
	
	close(fd);
	return 0;
}
