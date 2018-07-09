Challenge Project - Search Program

This is a challenge project to search 2 dimensional integer matrix for the rows that matches search criteria as given below:

1. Find all rows that have a specific sequence of numbers (if that number sequence appears more than once for that row, you only need to print it once)
2. Find all rows that contain all of the required numbers (if number repeats, that row must contain at least that many number)
3. Find the row that has the closest match to a specific number sequence (just need to consider the number of matches)

The application is developed in C++ (C++11) and created two programs SearchProgram and MatrixGenerator. SearchProgram is used to search the matrix file with search criteria and MatrixGenerator generates the matrix file. Makefile provided to build the programs, use below make commands to build and clean the programs.

> make 

> make clean

**SearchProgram** is a command line interface to perform the search. user must provide the matrix file as parameter to start SerachProgram. search function can be performed multiple times (with different number sequence) but using the same matrix data file which 

> ./SearchProgram matrix.dat

The matrix.dat is a encrypted file with 2 dimensional matrix of integers, and olny SearchProgram can decrypt and the matrix data. below are example commands to search the sequence in matrix file. 

> searchSequence 1 3 4 3 234 6 7

> searchUnordered 1 3 4 2

> searchBestMatch 2 4 5 3 5

the SearchProgram provides three search functions and outputs the row indices of the two dimensional matrix that match the input sequence for a given search condition. 

Alternatively user can also include a file to include sequence of search.

> ./SearchProgram matrix.dat search.txt

This will run our program with matrix.dat as our matrix file and use the sequence of text in search.txt instead of the Command Line interface, so for e.g. search.txt will have

> searchSequence 67 3 4 3 234 65 74

> searchSequence 3 333 4 3 234 66 87

> searchSequence 1 3 455 31 234 62 73

> searchUnordered 1 3 455 31 234 62 73

**MatrixGenerator** is a sub-program allows user to set row and column count as parameters (argc/argv) and generates the matrix.dat file.

> ./MatrixGenerator 100 100
