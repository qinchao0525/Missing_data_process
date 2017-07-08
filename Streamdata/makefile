.PHONY:clean all
CC=g++
CFLAGS=-Wall -g
BIN=datacreate
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -o $@

clean:
	rm -f *.o $(BIN)
