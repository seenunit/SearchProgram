CC=g++

CFLAGS=-c -std=c++11

SRCDIR   = src

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)

#$(CC) BestMatchSearch.cpp OrderedSearch.cpp SearchProgram.cpp UnOrderedSearch.cpp MatrixData.cpp  BestMatchSearch.h OrderedSearch.h MatrixData.h  MatrixSearch.h UnOrderedSearch.h -o SearchProgram

all:	
	$(CC) $(SOURCES) $(INCLUDES) -o SearchProgram
		
clean:
	rm -f *.o SearchProgram
			