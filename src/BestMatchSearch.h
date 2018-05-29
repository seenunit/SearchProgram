#ifndef BESTMATCHSEARCH
#define BESTMATCHSEARCH

#include "MatrixSearch.h"
class BestMatchSearch :
    public MatrixSearch
{
public:
    BestMatchSearch();
    ~BestMatchSearch();

    vector<int> SearchSequence(const MatrixDataType &matrix, const vector<int> &sequence);
};

#endif //BESTMATCHSEARCH