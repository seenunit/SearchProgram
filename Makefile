CC=g++

CFLAGS=-c -std=c++11

SRCDIR   = src
MATGENDIR = matgensrc

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)

MATGENSRC = matgensrc/main.cpp src/MatrixGenerator.cpp src/MatrixGenerator.h

#$(CC) BestMatchSearch.cpp OrderedSearch.cpp SearchProgram.cpp UnOrderedSearch.cpp MatrixData.cpp  BestMatchSearch.h OrderedSearch.h MatrixData.h  MatrixSearch.h UnOrderedSearch.h -o SearchProgram

all:
	$(CC) $(SOURCES) $(INCLUDES) -o SearchProgram
	$(CC) -DLINUX_BUILD $(MATGENSRC) -o MatrixGenerator

SearchProgram:	
	$(CC) $(SOURCES) $(INCLUDES) -o SearchProgram

MatrixGenerator:
	$(CC) -DLINUX_BUILD $(MATGENSRC) -o MatrixGenerator
		
clean:
	rm -f *.o SearchProgram MatrixGenerator
			