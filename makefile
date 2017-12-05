CC = g++
DEBUG = -g
WARNING = -w #disable warnings in compiler
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
FILENAME = project

all: project

project: $(FILENAME).o node.o packet.o
	$(CC) $(LFLAGS) $(WARNING) -std=c++11 $(FILENAME).o -o project

$(FILENAME).o: $(FILENAME).cpp
	$(CC) $(CFLAGS) $(WARNING) -std=c++11 $(FILENAME).cpp

node.o: node.cpp
	$(CC) $(CFLAGS) $(WARNING) -std=c++11 node.cpp

packet.o: packet.cpp
	$(CC) $(CFLAGS) $(WARNING) -std=c++11 packet.cpp

clean: 
	rm -rf  *.o  $(FILENAME)
