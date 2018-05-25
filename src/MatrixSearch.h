#ifndef MATRIXSEARCH
#define MATRIXSEARCH

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> MatrixDataType;

// returns number of times sequence found in row
int LinearSearchSequenceCount(vector<int> row, vector<int> sequence, bool bCount = false);

// returns number of times value found in row
int LinearSearchValueCount(vector<int> row, int x, bool bCount = false);

// return row index of the value at first encounter
int LinearSearchValue(vector<int> row, int x);

class MatrixSearch
{
public:
    virtual void SearchSequence(MatrixDataType, vector<int>) = 0;
};

#endif //MATRIXSEARCH