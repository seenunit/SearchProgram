#include "MatrixData.h"
#include "OrderedSearch.h"
#include "UnOrderedSearch.h"
#include "BestMatchSearch.h"
#include "MatrixGenerator.h"
#include <algorithm>

void MatrixData::IntializeMatrix(vector<string> vecRows) {
    
    try {
        // check input argument
        if (vecRows.size() == 0) {
            throw runtime_error("Row has no elements");
        }

		int iRow = (m_row != vecRows.size()) ? vecRows.size() : m_row;

        for (auto row : vecRows)
        {
            // extract integers from row string
            vector<int> vecRow = extractStringValues<int>(row);

            int iCol = (m_column != vecRow.size()) ? vecRow.size() : m_column;

            // restrict number of columns in row
            vector<int> subRow(vecRow.begin(), vecRow.begin() + iCol);

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
    catch (exception ex) {
        cout << "Error: Matrix intialization is failed due to: " << ex.what() << endl;
    }

}

void MatrixData::PrintMatrixData() {
    try {
        cout << "Row: " << m_row << " Column: " << m_column << endl;
        for (auto row : m_Matrix) {
            for (auto col : row) {
                cout << col << " ";
            }
            cout << endl;
        }
    }
    catch (exception ex) {
        cout << "Error: Print Matrix failed due to " << ex.what() << endl;
    }
}

vector<int> MatrixData::SearchSequence(string searchLine) {
	vector<int> vecIndex{};
    try {
        // extract sequence from input string
        vector<int> seqInts = extractStringValues<int>(searchLine);
        // extract search type from input i.e. first string token
        string searcType = extractStringValues<string>(searchLine)[0];

#ifdef DEBUG
        for (auto val : seqInts) {
            cout << val << " ";
        }
        cout << endl;
        cout << searcType << endl;
#endif // DEBUG

        MatrixSearch *pSearch = GetMatrixSearch(searcType);

        if (pSearch) {
            if (searcType == "searchUnordered") {
				vecIndex = pSearch->SearchSequence(m_SortedMatrix, seqInts);
            }
            else {
				vecIndex = pSearch->SearchSequence(m_Matrix, seqInts);
            }
        }
        else {
            cout << "Error: Search type is not valid" << endl;
        }

    }
    catch (...) {
        cout << "Error: Sequence search failed" << endl;
    }

	return vecIndex;
}

MatrixSearch* MatrixData::GetMatrixSearch(string searchType) {

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