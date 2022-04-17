OBJS	= main.o
SOURCE	= main.cpp
HEADER	= ../uniprofiler.h
OUT	= profiler
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++17
LFLAGS	 =  -lglfw

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp


clean:
	rm -f $(OBJS) $(OUT)

