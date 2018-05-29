#ifndef MATRIXSEARCH
#define MATRIXSEARCH

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> MatrixDataType;

// returns number of times sequence found in row
int LinearSearchSequenceCount(const vector<int> &row, const vector<int> &sequence, bool bCount = false);

// returns number of times value found in row
int LinearSearchValueCount(const vector<int> &row, int x, bool bCount = false);

// return row index of the value at first encounter
int LinearSearchValue(const vector<int> &row, int x);

// returns the sequence prefix vector
vector<int> GetSequenePrefixVector(const vector<int> &vecSequence);

// KMP algorithm search on given row
int KMPSearchSequenceCount(const vector<int> &row, const vector<int> &sequence, const vector<int> &vecSeqPrefix, bool bCount = false);

// return true if sequence is presernt in row using sequence search
int UnorderedSearchSortedSequence(const vector<int> &row, const vector<int> &sequence);

class MatrixSearch
{
public:
    virtual vector<int> SearchSequence(const MatrixDataType &, const vector<int> &) = 0;
};

#endif //MATRIXSEARCH