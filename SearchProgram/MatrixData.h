#pragma once
#include "MatrixSearch.h"

class MatrixData
{
public:
    MatrixData() {}

    MatrixData(int row, int column) : m_row(row), m_column(column) {
        
    }

    MatrixData(int row, int column, vector<string> vecStrings) : m_row(row), m_column(column) {
        IntializeMatrix(vecStrings);
    }

    ~MatrixData() {};

public:
    void IntializeMatrix(vector<string> vecStrings);
    void SearchSequence(string searchSeq);
    MatrixSearch *GetMatrixSearch(string searchType);

    void PrintMatrixData();

private:
    MatrixDataType m_Matrix;
    int m_row{};
    int m_column{};
};

