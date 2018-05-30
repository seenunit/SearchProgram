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
    std::vector<int> SearchSequence(const MatrixDataType &matrix, const std::vector<int> &sequence);
};

#endif //ORDEREDSEARCH