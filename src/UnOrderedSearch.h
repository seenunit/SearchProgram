#ifndef UNORDEREDSEARCH
#define UNORDEREDSEARCH

#include "MatrixSearch.h"
class UnOrderedSearch :
    public MatrixSearch
{
public:
    UnOrderedSearch();
    ~UnOrderedSearch();

    vector<int> SearchSequence(const MatrixDataType &matrix, const vector<int> &sequence);
};

#endif //UNORDEREDSEARCH