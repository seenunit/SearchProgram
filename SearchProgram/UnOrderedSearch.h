#pragma once
#include "MatrixSearch.h"
class UnOrderedSearch :
    public MatrixSearch
{
public:
    UnOrderedSearch();
    ~UnOrderedSearch();

    void SearchSequence(MatrixDataType matrix, vector<int> sequence);
};

