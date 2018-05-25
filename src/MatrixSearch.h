#ifndef MATRIXSEARCH
#define MATRIXSEARCH

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> MatrixDataType;

int LinearSearchSequenceCount(vector<int> row, vector<int> sequence, bool bCount = false);
int LinearSearchValueCount(vector<int> row, int x, bool bCount = false);

class MatrixSearch
{
public:
    virtual void SearchSequence(MatrixDataType, vector<int>) = 0;
};

#endif //MATRIXSEARCH