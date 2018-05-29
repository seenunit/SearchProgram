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
    vector<int> SearchSequence(const MatrixDataType &matrix, const vector<int> &sequence);
};

#endif //ORDEREDSEARCH