CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -g
MAIN = download
SRC = download.c
all: $(MAIN)

$(MAIN) : $(SRC)
	$(CC) $(CFLAGS) -o $(MAIN) $(SRC)

clean:
	rm -f *.o $(MAIN) core
