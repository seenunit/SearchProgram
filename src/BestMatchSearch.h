#ifndef BESTMATCHSEARCH
#define BESTMATCHSEARCH

#include "MatrixSearch.h"
class BestMatchSearch :
    public MatrixSearch
{
public:
    BestMatchSearch();
    ~BestMatchSearch();

    void SearchSequence(MatrixDataType matrix, vector<int> sequence);
};

#endif //BESTMATCHSEARCH