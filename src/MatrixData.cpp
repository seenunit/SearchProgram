#include "MatrixData.h"
#include "OrderedSearch.h"
#include "UnOrderedSearch.h"
#include "BestMatchSearch.h"
#include "MatrixGenerator.h"
#include <algorithm>

int compare(const void * a, const void * b)
{
return (*(int*)a - *(int*)b);
}

void MatrixData::GetSearchInfo(const std::string &searchLine, std::string &searchType, std::vector<int> &sequence) {

	// extract sequence from input string
	extractStringValues<int>(searchLine, sequence);
	// extract search type from input i.e. first string token
	std::vector<std::string> seqStrings{};
	extractStringValues<std::string>(searchLine, seqStrings);
	searchType = seqStrings[0];

	return;

}

void MatrixData::IntializeMatrix(const std::vector<std::string> &vecRows) {

	try {
		// check input argument
		if (vecRows.size() == 0) {
			throw std::runtime_error("Row has no elements");
		}

		int iRow = (m_row != (int)vecRows.size()) ? vecRows.size() : m_row;

		for (auto row : vecRows)
		{
			// extract integers from row string
			std::vector<int> vecRow{};
			extractStringValues<int>(row, vecRow);

			int iCol = (m_column != (int)vecRow.size()) ? vecRow.size() : m_column;

			// restrict number of columns in row
			std::vector<int> subRow(vecRow.begin(), vecRow.begin() + iCol);

			// push row of int in to matrix
			m_Matrix.push_back(subRow);

			// sort the row
			sort(subRow.begin(), subRow.end());
			m_SortedMatrix.push_back(subRow);

			// restrict number of rows in matrix
			if (iRow == (int)m_Matrix.size())
				break;
		}

		for (int i = 0; i < m_row; i++)
		{
			auto row = m_Matrix[i];
			auto sortrow = m_SortedMatrix[i];

			for (int j = 0; j < m_column; j++)
			{
				m_MatrixArray.m_pMatrix[i][j] = row[j];
				m_MatrixArray.m_pSortMatrix[i][j] = sortrow[j];
			}
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: Matrix intialization is failed due to: " << ex.what() << std::endl;
	}

}

void MatrixData::IntializeMatrix(const MatrixDataType &vecRows) {
    
    try {
        // check input argument
        if (vecRows.size() == 0) {
            throw std::runtime_error("Row has no elements");
        }

		m_Matrix = vecRows;

        for (auto row : m_Matrix)
        {
            // sort the row
            sort(row.begin(), row.end());
            m_SortedMatrix.push_back(row);
        }

		for (int i = 0; i < m_row; i++)
		{
			auto row = m_Matrix[i];
			auto sortrow = m_SortedMatrix[i];

			for (int j = 0; j < m_column; j++)
			{
				m_MatrixArray.m_pMatrix[i][j] = row[j];
				m_MatrixArray.m_pSortMatrix[i][j] = sortrow[j];
			}
		}

    }
    catch (std::exception ex) {
        std::cout << "Error: Matrix intialization is failed due to: " << ex.what() << std::endl;
    }
}

void MatrixData::IntializeMatrixArray(int **pMatrix) {

	try {
		for (int i = 0; i < m_row; i++)
		{
			int *sortrow = new int[m_column];
			for (int j = 0; j < m_column; j++)
			{
				sortrow[j] = pMatrix[i][j];
			}

			qsort(sortrow, m_column, sizeof(int), compare);

			for (int j = 0; j < m_column; j++)
			{
				m_MatrixArray.m_pMatrix[i][j] = pMatrix[i][j];
				m_MatrixArray.m_pSortMatrix[i][j] = sortrow[j];
			}

			if (sortrow) delete[] sortrow;
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: Matrix intialization is failed due to: " << ex.what() << std::endl;
	}
}

void MatrixData::PrintMatrixData() {
    try {
        std::cout << "Row: " << m_row << " Column: " << m_column << std::endl;
        for (auto row : m_Matrix) {
            for (auto col : row) {
                std::cout << col << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (std::exception ex) {
        std::cout << "Error: Print Matrix failed due to " << ex.what() << std::endl;
    }
}

void MatrixData::SearchSequence(const std::string &searchType, const std::vector<int> &sequence, std::vector<int> &vecIndex) {

    try {
		
        MatrixSearch *pSearch = GetMatrixSearch(searchType);

		if (pSearch) {

			if (searchType == "searchSequence") {

				int size = (int)sequence.size();
				
				int *pSequence = new int[size];
				for (int i = 0; i < size; i++)
				{
					pSequence[i] = sequence[i];
				}

				pSearch->SearchSequence(m_MatrixArray, pSequence, size, vecIndex);

				delete[] pSequence;
			}
			else {
				pSearch->SearchSequence(m_Matrix, m_SortedMatrix, sequence, vecIndex);
			}
		}
        else {
            std::cout << "Error: Search type is not valid" << std::endl;
        }

    }
    catch (...) {
        std::cout << "Error: Sequence search failed" << std::endl;
    }

	return;
}

void MatrixData::SearchSequence(const std::string &searchType, const int sequence[], int size, std::vector<int> &vecIndex) {
	try {

		MatrixSearch *pSearch = GetMatrixSearch(searchType);

		if (pSearch) {


				pSearch->SearchSequence(m_MatrixArray, sequence, size, vecIndex);



		}
		else {
			std::cout << "Error: Search type is not valid" << std::endl;
		}

	}
	catch (...) {
		std::cout << "Error: Sequence search failed" << std::endl;
	}

	return;
}

MatrixSearch* MatrixData::GetMatrixSearch(const std::string &searchType) {

    MatrixSearch *pSearch = nullptr;

    if (searchType == "searchSequence") {
        pSearch = new OrderedSearch();
    }
    else if (searchType == "searchUnordered") {
        pSearch = new UnOrderedSearch();
    }
    else if (searchType == "searchBestMatch") {
        pSearch = new BestMatchSearch();
    }

    return pSearch;
}