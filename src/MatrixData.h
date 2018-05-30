#ifndef MATRIXDATA
#define MATRIXDATA

#include "MatrixSearch.h"

void TestMatrixSearch();

class MatrixData
{
public:
    MatrixData() {}

    MatrixData(int row, int column) : m_row(row), m_column(column) {
        
    }

    ~MatrixData() {};

public:
	void IntializeMatrix(const vector<string> &vecStrings);
    void IntializeMatrix(const MatrixDataType &vecRows);
    vector<int> SearchSequence(string searchSeq);
    MatrixSearch *GetMatrixSearch(string searchType);

    void PrintMatrixData();

private:
    MatrixDataType m_Matrix;
    MatrixDataType m_SortedMatrix;
    int m_row{};
    int m_column{};
};

#endif //MATRIXDATA