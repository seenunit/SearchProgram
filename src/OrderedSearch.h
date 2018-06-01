#ifndef ORDEREDSEARCH
#define ORDEREDSEARCH

#include "MatrixSearch.h"
class OrderedSearch :
    public MatrixSearch
{
public:
    OrderedSearch();
    ~OrderedSearch();

public:
   void SearchSequence(const MatrixDataType &matrix, const MatrixDataType &sortedMatrix, const std::vector<int> &sequence, std::vector<int> &vecIndex);
};

#endif //ORDEREDSEARCH