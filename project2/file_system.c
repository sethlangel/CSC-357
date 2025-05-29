#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include"inode.h"

void changeDirectory(const char *name){
	//Checks for cd to parent directory. If not continue to see if file name exists in currentInode and that the inode type is a directory.
	if(strcmp("..", name) == 0){
		currentInode = inodeList[currentInode].parentInode;
	}
	else {
		int found = 0;
		for(size_t i = 0; i < inodeCount; i++){
			if(strcmp(inodeList[i].name, name) == 0 && inodeList[i].parentInode == currentInode && inodeList[i].type == 'd'){
				currentInode = i;
				found = 1;
				break;
			}
		}	
		
		if(found == 0){
			printf("Directory %s is not found.\n", name);	
		}
	}
}

void listContents(){
	for(size_t i = 0; i < inodeCount; i++){
		if(inodeList[i].parentInode == currentInode){
			printf("inode: %d, type: %c, name: %s\n", inodeList[i].inode, inodeList[i].type, inodeList[i].name);
		}
	}
}

void createDirectory(const char *name){
	//if a directory name already exists within the currentInode then we can't mkdir
	for(size_t i = 0; i < inodeCount; i++){
		if(strcmp(inodeList[i].name, name) == 0 && inodeList[i].type == 'd' && inodeList[i].parentInode == currentInode){
			printf("Directory name already exists.\n");
			return;
		}
	}

	if(inodeCount >= 1024){
		printf("Inode capacity reached.\n");
		return;
	}
	
	Inode newInode;
	newInode.inode = inodeCount;
	newInode.parentInode = currentInode;
	newInode.type = 'd';
	strncpy(newInode.name, name, sizeof(newInode.name) - 1);
	newInode.name[31] = '\0';
	
	inodeList[inodeCount] = newInode;
	inodeCount++;

	//Converts inode number to string and then the filename buffer is used for the path in the fopen.
	char filename[5];
	snprintf(filename, sizeof(filename), "%u", newInode.inode);

	FILE *fp = fopen(filename, "w");
		
	if(fp == NULL){
		printf("Error: Could not create directory inode file %s.\n", filename);
		return;
	}

	fprintf(fp, ". %u\n.. %u\n", newInode.inode, newInode.parentInode);
	fclose(fp);
}

void createFile(const char *name){
	//Check for file with the same name and if it exists as a child in the currentInode we can't create a file.
	for(size_t i = 0; i < inodeCount; i++){
		if(strcmp(inodeList[i].name, name) == 0 && inodeList[i].type == 'f' && inodeList[i].parentInode == currentInode){
			printf("File name already exists.\n");
			return;
		}
	}

	if(inodeCount >= 1024){
		printf("Inode capacity reached.\n");
		return;
	}

	Inode newInode;
	newInode.inode = inodeCount;
	newInode.parentInode = currentInode;
	newInode.type = 'f';
	strncpy(newInode.name, name, sizeof(newInode.name) - 1);
	newInode.name[31] = '\0';

	inodeList[inodeCount] = newInode;
	inodeCount++;
	
	//Converts inode number to string and then the filename bufferis used for the path in the fopen.
	char filename[5];
	snprintf(filename, sizeof(filename), "%u", newInode.inode);

	FILE *fp = fopen(filename, "w");

	if(fp == NULL){
		printf("Error: Coult not create file inode file %s.\n", filename);
		return;
	}

	fprintf(fp, "%s", newInode.name);
	fclose(fp);
}
