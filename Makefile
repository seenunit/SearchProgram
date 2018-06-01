CC=g++

CFLAGS=-std=c++11 -Wall -O3

SRCDIR   = src
MATGENDIR = matgensrc

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)

MATGENSRC = matgensrc/main.cpp src/MatrixGenerator.cpp src/MatrixGenerator.h

#$(CC) BestMatchSearch.cpp OrderedSearch.cpp SearchProgram.cpp UnOrderedSearch.cpp MatrixData.cpp  BestMatchSearch.h OrderedSearch.h MatrixData.h  MatrixSearch.h UnOrderedSearch.h -o SearchProgram

all: SearchProgram
	
SearchProgram:	
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o SearchProgram

MatrixGenerator:
	$(CC) $(CFLAGS) $(MATGENSRC) -o MatrixGenerator
		
clean:
	rm -f *.o SearchProgram MatrixGenerator
			