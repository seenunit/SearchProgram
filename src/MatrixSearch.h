#ifndef MATRIXSEARCH
#define MATRIXSEARCH

#include <iostream>
#include <vector>
#include <string>
//using namespace std;

typedef std::vector<std::vector<int>> MatrixDataType;

struct MatrixMap {
	int value;
	int rowindex;
	int columnindex;
};

struct MatrixDataArray {
	int **m_pMatrix;
	int **m_pSortMatrix;
	MatrixMap *m_pMatrixMap;
	int row{};
	int column{};
};

// returns number of times sequence found in row
int LinearSearchSequenceCount(const std::vector<int> &row, const std::vector<int> &sequence, bool bCount = false);

// returns number of times value found in row
int LinearSearchValueCount(const std::vector<int> &row, int x, bool bCount = false);

// return row index of the value at first encounter
int LinearSearchValue(const std::vector<int> &row, int x);

// return true value found in vector
bool InterpolationSearchValue(const std::vector<int> &row, int x);

// return index of value otherwise returns -1
int InterpolationSearchValue(const int row[], int size, int x);

// returns the sequence prefix vector
std::vector<int> GetSequenePrefixVector(const std::vector<int> &vecSequence);

void GetSequencePrefixArray(const int *pSequence, int size, int *pPrefixArray);

// KMP algorithm search on given row
int KMPSearchSequenceCount(const std::vector<int> &row, const std::vector<int> &sequence, const std::vector<int> &vecSeqPrefix, bool bCount = false);

int KMPSearchSequenceCount(const int row[], int N, const int sequence[], int M, const int seqprefix[], bool bCount = false);

int SearchSequencePartial(const int row[], int N, const int sequence[], int M, const int seqprefix[]);

// return true if sequence is presernt in row using sequence search
int UnorderedSearchSortedSequence(const std::vector<int> &row, const std::vector<int> &sequence);

int UnorderedSearchSortedSequence(const int row[], int N, const int sequence[], int M);

int binarySearch(int arr[], int size, int x);

// Binary search through all the data of matrix map and find the possible rows for sequence search
void BinarySearchMatrixMap(const MatrixMap matrixmap[], int size, int value, std::vector<int> &vecRow);

// Binary search through all the data of matrix map and find the possible rows for sequence search
void BinarySearchSequenceSearchforBestMatch(const MatrixDataArray& matrixarray, const int sequence[], int seqsize, std::vector<int> &vecRow);

int compare(const void * a, const void * b);

int compareMatrixMap(const void *a, const void * b);

int compareMatrixMapKey(const void *a, const void * b);

class MatrixSearch
{
public:
    virtual void SearchSequence(const MatrixDataType &, const MatrixDataType &, const std::vector<int> &, std::vector<int> &) = 0;
	virtual void SearchSequence(const MatrixDataArray&, const int*, int size, std::vector<int> &) = 0;
};

#endif //MATRIXSEARCH