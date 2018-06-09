#ifndef UNORDEREDSEARCH
#define UNORDEREDSEARCH

#include "MatrixSearch.h"
class UnOrderedSearch :
	public MatrixSearch
{
public:
	UnOrderedSearch();
	~UnOrderedSearch();

	void SearchSequence(const MatrixDataType &matrix, const MatrixDataType &sortedMatrix, const std::vector<int> &sequence, std::vector<int> &vecIndex);
	void SearchSequence(const MatrixDataArray& matrixarray, const int* sequence, int size, std::vector<int> &vecIndex);
};

#endif //UNORDEREDSEARCH