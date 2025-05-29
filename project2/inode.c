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

	inodeCount = fread(&inodeList, sizeof(Inode), 1024, fp);
		
	fclose(fp);
}

void saveInodeList(const char *path){
	FILE *fp = fopen(path, "wb");

	if(fp == NULL){
		printf("Error: Failed to open path: %s while trying to saveInodeList\n", path);
		exit(1);
	}

	fwrite(&inodeList, sizeof(Inode), inodeCount, fp);
	
	fclose(fp);
}
