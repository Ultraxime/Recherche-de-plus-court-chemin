CC = gcc

CFLAGS = -Iinc 
LIBFLAGS = -lm -lSDL

SRC_FILES=$(wildcard src/*.c)

all: search

search: $(SRC_FILES)
	$(CC) -o $@ $(SRC_FILES) $(CFLAGS) $(LIBFLAGS)

clean:
	rm -f search
