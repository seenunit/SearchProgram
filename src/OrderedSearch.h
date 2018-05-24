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
    void SearchSequence(MatrixDataType matrix, vector<int> sequence);
};

#endif //ORDEREDSEARCH