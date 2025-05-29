#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"inode.h"

Inode inodeList[1024];
size_t inodeCount = 0;
uint32_t currentInode = 0;

void loadInodeList(const char *path){
	FILE *fp = fopen(path, "rb");

	if(fp == NULL){
		printf("Error: Failed to open path: %s while trying to loadInodeList\n", path);
		exit(1);
	}

	inodeCount = fread(inodeList, sizeof(Inode), 1024, fp);
	
	fclose(fp);

	//I know the assignment asks for throwing an error and to terminate. The issue is that the inodes_list file in the empty directory given in the GitHub repo does not have a readable directory.
	//Thus making the program exit and not letting the user create a root directory in empty. I have simiplied it to this error check below and prints out saying that since 0 inodes were read
	//there is no root directory and it will be created on the first mkdir. Below this if statement is the error check for if inodeList[0] is directory, it is commented out to prevent issues with
	//the empty dir. 
	if(inodeCount == 0){
		printf("Error: inodeList read 0 inodes. This also means there is no root directory. Create a dir with \"mkdir [dir name]\".\n");
	}

	/*
	if(inodeList[currentInode].type == 'f'){
		printf("Inode 0 is not a directory. Therefore there is no root directory. Exiting...
		exit(1);
	}
	*/
}

void saveInodeList(const char *path){
	FILE *fp = fopen(path, "wb");

	if(fp == NULL){
		printf("Error: Failed to open path: %s while trying to saveInodeList\n", path);
		exit(1);
	}
	
	if(fwrite(inodeList, sizeof(Inode), inodeCount, fp) != inodeCount){
		printf("Error: Failed to write full contents of inodeList\n");
		fclose(fp);
		exit(1);
	}
	
	fclose(fp);
}
