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
	void IntializeMatrix(const std::vector<std::string> &vecStrings);
    void IntializeMatrix(const MatrixDataType &vecRows);
    void SearchSequence(const std::string &searchType, const std::vector<int> &sequence, std::vector<int> &vecIndex);
    MatrixSearch *GetMatrixSearch(const std::string &searchType);
	void GetSearchInfo(const std::string &searchLine, std::string &searchType, std::vector<int> &sequence);

    void PrintMatrixData();

private:
    MatrixDataType m_Matrix;
    MatrixDataType m_SortedMatrix;
    int m_row{};
    int m_column{};
};

void TestRandomMatrixSearch(MatrixData &matrix);

#endif //MATRIXDATA