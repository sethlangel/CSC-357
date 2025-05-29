#ifndef INODE_H
#define INODE_H
#include<stdint.h>
typedef struct {
	uint32_t inode;
	uint32_t parentInode;
	char type;
	char name[32];
} Inode;

Inode inodeList[1024];
size_t inodeCount;
uint32_t currentInode;

void loadInodeList(const char *path);
void saveInodeList(const char *path);
#endif
