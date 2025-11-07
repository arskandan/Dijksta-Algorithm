CC     =  gcc
CFLAGS = -lm -O3 -Wno-unused-result
DEPS   =  mylib.h priorityQueue.h
OBJ    =  dijkstra.o mylib.o priorityQueue.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: dijkstra.exe

dijkstra.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	del *.o *.exe
