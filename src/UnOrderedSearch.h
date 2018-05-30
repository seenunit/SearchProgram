#ifndef UNORDEREDSEARCH
#define UNORDEREDSEARCH

#include "MatrixSearch.h"
class UnOrderedSearch :
    public MatrixSearch
{
public:
    UnOrderedSearch();
    ~UnOrderedSearch();

    std::vector<int> SearchSequence(const MatrixDataType &matrix, const std::vector<int> &sequence);
};

#endif //UNORDEREDSEARCH