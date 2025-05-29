#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"inode.h"
#include"file_system.h"

int main(int argc, char *argv[]){
	if(argc > 2){
		printf("Error: Too many arguments\n");
		return 1;
	}
	
	if(argc < 2){
		printf("Error: Missing argument\n");
		return 1;
	}
	const char *directory = argv[1];
	
	if(chdir(directory) != 0){
		printf("Error: Could not change to directory: %s\n", argv[1]);
		return 1;
	}
	
	loadInodeList("inodes_list");

	char userCommand[50];
	
	while(1){
		printf("fs_emulator > ");
		
		//Checking for EOF or Error on fgets if EOF or Error is hit we break out of the loop.	
		if(fgets(userCommand, sizeof(userCommand), stdin) != NULL){
			char *nullPos = strchr(userCommand, '\n');
			*nullPos = '\0';
		}
		else{
			//Adds newline for cmd prompt.
			printf("\n");
			break;
		}
		
		//Splitting userCommand to get both the command and the argument.
		char *cmdArray[2];
		cmdArray[0] = strtok(userCommand, " ");
		if(cmdArray[0] != NULL){
			cmdArray[1] = strtok(NULL, " ");
		}

		//Command loop for user.
		if(strcmp(cmdArray[0], "exit") == 0){
			break;
		}
		else if(strcmp(cmdArray[0], "cd") == 0){
			if(cmdArray[1] == NULL){
				printf("Directory name not given.\n");
			}
			else{
				changeDirectory(cmdArray[1]);
			}		
		}
		else if(strcmp(cmdArray[0], "ls") == 0){
			listContents();
		}
		else if(strcmp(cmdArray[0], "mkdir") == 0){
			if(cmdArray[1] == NULL){
				printf("Directory name not given.\n");
			}
			else{
				createDirectory(cmdArray[1]);
			}
		}
		else if(strcmp(cmdArray[0], "touch") == 0){
			if(cmdArray[1] == NULL){
				printf("File name not given.\n");
			}
			else {
				createFile(cmdArray[1]);
			}	
		}
		else{
			printf("Command not found.\n");		
		}
	}
	
	saveInodeList("inodes_list");
	
	return 0;
}

