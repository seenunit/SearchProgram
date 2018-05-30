#ifndef BESTMATCHSEARCH
#define BESTMATCHSEARCH

#include "MatrixSearch.h"
class BestMatchSearch :
    public MatrixSearch
{
public:
    BestMatchSearch();
    ~BestMatchSearch();

    std::vector<int> SearchSequence(const MatrixDataType &matrix, const std::vector<int> &sequence);
};

#endif //BESTMATCHSEARCH