#ifndef BESTMATCHSEARCH
#define BESTMATCHSEARCH

#include "MatrixSearch.h"
class BestMatchSearch :
    public MatrixSearch
{
public:
    BestMatchSearch();
    ~BestMatchSearch();

    vector<int> SearchSequence(MatrixDataType matrix, vector<int> sequence);
};

#endif //BESTMATCHSEARCH