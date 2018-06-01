#ifndef MATRIXSEARCH
#define MATRIXSEARCH

#include <iostream>
#include <vector>
#include <string>
//using namespace std;

typedef std::vector<std::vector<int>> MatrixDataType;

// returns number of times sequence found in row
int LinearSearchSequenceCount(const std::vector<int> &row, const std::vector<int> &sequence, bool bCount = false);

// returns number of times value found in row
int LinearSearchValueCount(const std::vector<int> &row, int x, bool bCount = false);

// return row index of the value at first encounter
int LinearSearchValue(const std::vector<int> &row, int x);

// return true value found in vector
bool InterpolationSearchValue(const std::vector<int> &row, int x);

// returns the sequence prefix vector
std::vector<int> GetSequenePrefixVector(const std::vector<int> &vecSequence);

// KMP algorithm search on given row
int KMPSearchSequenceCount(const std::vector<int> &row, const std::vector<int> &sequence, const std::vector<int> &vecSeqPrefix, bool bCount = false);

// return true if sequence is presernt in row using sequence search
int UnorderedSearchSortedSequence(const std::vector<int> &row, const std::vector<int> &sequence);

class MatrixSearch
{
public:
    virtual void SearchSequence(const MatrixDataType &, const MatrixDataType &, const std::vector<int> &, std::vector<int> &) = 0;
};

#endif //MATRIXSEARCH