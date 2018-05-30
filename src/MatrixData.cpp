#include "MatrixData.h"
#include "OrderedSearch.h"
#include "UnOrderedSearch.h"
#include "BestMatchSearch.h"
#include "MatrixGenerator.h"
#include <algorithm>

void MatrixData::IntializeMatrix(const std::vector<std::string> &vecRows) {

	try {
		// check input argument
		if (vecRows.size() == 0) {
			throw std::runtime_error("Row has no elements");
		}

		int iRow = (m_row != vecRows.size()) ? vecRows.size() : m_row;

		for (auto row : vecRows)
		{
			// extract integers from row string
			std::vector<int> vecRow = extractStringValues<int>(row);

			int iCol = (m_column != vecRow.size()) ? vecRow.size() : m_column;

			// restrict number of columns in row
			std::vector<int> subRow(vecRow.begin(), vecRow.begin() + iCol);

			// push row of int in to matrix
			m_Matrix.push_back(subRow);

			// sort the row
			sort(subRow.begin(), subRow.end());
			m_SortedMatrix.push_back(subRow);

			// restrict number of rows in matrix
			if (m_Matrix.size() == iRow)
				break;
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

std::vector<int> MatrixData::SearchSequence(std::string searchLine) {
	std::vector<int> vecIndex{};
    try {

        // extract sequence from input string
        std::vector<int> seqInts = extractStringValues<int>(searchLine);
        // extract search type from input i.e. first string token
		std::vector<std::string> seqStrings = extractStringValues<std::string>(searchLine);
		std::string searcType = seqStrings[0];
		
        MatrixSearch *pSearch = GetMatrixSearch(searcType);

        if (pSearch) {
            if (searcType == "searchUnordered") {
				vecIndex = pSearch->SearchSequence(m_SortedMatrix, seqInts);
            }
            else {
				vecIndex = pSearch->SearchSequence(m_Matrix, seqInts);
            }
						
			// output the row indices
			if(vecIndex.size() == 0){
				std::cout << "none";
			}
			else {
				for (auto index : vecIndex) {
					std::cout << index << " ";
				}
			}
			std::cout << std::endl;
        }
        else {
            std::cout << "Error: Search type is not valid" << std::endl;
        }

    }
    catch (...) {
        std::cout << "Error: Sequence search failed" << std::endl;
    }

	return vecIndex;
}

MatrixSearch* MatrixData::GetMatrixSearch(std::string searchType) {

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