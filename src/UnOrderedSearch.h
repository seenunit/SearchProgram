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
};

#endif //UNORDEREDSEARCH