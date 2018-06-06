#ifndef MATRIXDATA
#define MATRIXDATA

#include <fstream>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "MatrixSearch.h"

class MatrixData
{
public:
    MatrixData() {}

    MatrixData(int row, int column) : m_row(row), m_column(column) {
		m_MatrixArray.row = m_row;
		m_MatrixArray.column = m_column;
		m_MatrixArray.m_pMatrixMap = new MatrixMap[m_row * m_column];

		m_MatrixArray.m_pMatrix = new int*[m_row];
		m_MatrixArray.m_pSortMatrix = new  int*[m_row];
		
		for (int i = 0; i < m_row; i++)
		{
			m_MatrixArray.m_pMatrix[i] = new int[m_column] {0};
			m_MatrixArray.m_pSortMatrix[i] = new int[m_column] {0};
		}
    }

    ~MatrixData() {
		if (m_MatrixArray.m_pMatrix != nullptr && m_MatrixArray.m_pSortMatrix != nullptr) {
			for (int i = 0; i < m_row; i++)
			{
				delete[] m_MatrixArray.m_pMatrix[i];
				delete[] m_MatrixArray.m_pSortMatrix[i];
			}
			delete[] m_MatrixArray.m_pMatrix;
			delete[] m_MatrixArray.m_pSortMatrix;

			m_MatrixArray.m_pMatrix = nullptr;
			m_MatrixArray.m_pSortMatrix = nullptr;
		}

		if (m_MatrixArray.m_pMatrixMap != nullptr) {
			delete[] m_MatrixArray.m_pMatrixMap;

			m_MatrixArray.m_pMatrixMap = nullptr;
		}
	};

public:
	void IntializeMatrix(const std::vector<std::string> &vecStrings);
    void IntializeMatrix(const MatrixDataType &vecRows);
	void IntializeMatrixArray(int **ppMatrix);
    void SearchSequence(const std::string &searchType, const std::vector<int> &sequence, std::vector<int> &vecIndex);
	void SearchSequence(const std::string &searchType, const int sequence[], int size, std::vector<int> &vecIndex);
    MatrixSearch *GetMatrixSearch(const std::string &searchType);
	void GetSearchInfo(const std::string &searchLine, std::string &searchType, std::vector<int> &sequence);

    void PrintMatrixData();

private:
    MatrixDataType m_Matrix;
    MatrixDataType m_SortedMatrix;
	MatrixDataArray m_MatrixArray;
    int m_row{};
    int m_column{};
};

void TestMatrixSearch();

void TestRandomMatrixSearch(MatrixData &matrix);

inline void beginetime(clock_t &time) {
	if (time != 0)
	{
		std::cout << std::fixed;
		std::cout << std::setprecision(9);
		time = clock();
	}
}

inline void elapsedtimeFile(std::ofstream &timefile, clock_t begin_time) {
	if (begin_time != 0) {

		double elapsedtime = (double(clock() - begin_time) / CLOCKS_PER_SEC) * 1000000;
		std::cout << "elapsed time: " << elapsedtime << " microseconds" << std::endl;

		if (timefile.is_open() == true)
			timefile << elapsedtime << '\n';
	}
}

inline void printIndices(std::vector<int> vecIndex) {
	// output the row indices
	if (vecIndex.size() == 0) {
		std::cout << "none";
	}
	else {
		for (auto index : vecIndex) {
			std::cout << index << " ";
		}
	}
	std::cout << std::endl;
}

#endif //MATRIXDATA