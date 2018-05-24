#ifndef MATRIXSEARCH
#define MATRIXSEARCH

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> MatrixDataType;

int BasicOrderedSearch(vector<int> row, vector<int> sequence);
int LinearFindValueCount(vector<int> row, int x);

class MatrixSearch
{
public:
    virtual void SearchSequence(MatrixDataType, vector<int>) = 0;
};

#endif //MATRIXSEARCH