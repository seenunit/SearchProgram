#pragma once
#include "MatrixSearch.h"
class BestMatchSearch :
    public MatrixSearch
{
public:
    BestMatchSearch();
    ~BestMatchSearch();

    void SearchSequence(MatrixDataType matrix, vector<int> sequence);
};

