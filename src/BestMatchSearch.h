#ifndef BESTMATCHSEARCH
#define BESTMATCHSEARCH

#include "MatrixSearch.h"
class BestMatchSearch :
    public MatrixSearch
{
public:
    BestMatchSearch();
    ~BestMatchSearch();

    void SearchSequence(const MatrixDataType &matrix, const MatrixDataType &sortedMatrix,const std::vector<int> &sequence, std::vector<int> &vecIndex);
};

#endif //BESTMATCHSEARCH