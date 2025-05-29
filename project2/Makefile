C = gcc
CFLAGS = -Wall -pedantic -std=c99
MAIN = fs_emulator
OBJS = fs_emulator.o inode.o file_system.o

all: $(MAIN)

$(MAIN): $(OBJS) inode.h file_system.h
	$(CC) $(CFLAGS) -g -o $(MAIN) $(OBJS)

fs_emulator.o: fs_emulator.c inode.h file_system.h
	$(CC) $(CFLAGS) -c fs_emulator.c

inode.o: inode.c inode.h
	$(CC) $(CFLAGS) -c inode.c

file_system.o: file_system.c file_system.h
	$(CC) $(CFLAGS) -c file_system.c

clean:
	rm -f *.o $(MAIN) core

