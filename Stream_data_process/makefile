.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=stream_data_processing
OBJS=dataprocessing.o dataclass.o  
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
dataprocessing.o:dataprocessing.cpp  interpolation.h graypre.h
	$(CC) $(CFLAGS) -c $< -o $@
dataclass.o: dataclass.h dataclass.cpp
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f *.o $(BIN)
