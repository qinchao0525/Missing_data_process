.PHONY:clean
CC=gcc
CFLAGS=-Wall -g
BIN=dataprocess
OBJS=dataprocessing.o GenerateGaussNoise.o checktabRead.o comparison.o dataclassimp.o graypre.o interpolation.o spaceKnn.h
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
