CC = gcc
CFLAGS = -Wall -pedantic -std=c99
MAIN = fs_emulator
OBJS = fs_emulator.o inode.o

all: $(MAIN)

$(MAIN) : $(OBJS) inode.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fs_emulator.o : fs_emulator.c inode.h
	$(CC) $(CFLAGS) -c fs_emulator.c

inode.o : inode.c inode.h
	$(CC) $(CFLAGS) -c inode.c

clean :
	rm *.o $(MAIN) core
