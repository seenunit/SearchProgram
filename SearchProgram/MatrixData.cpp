#include <sstream>
#include "MatrixData.h"
#include "OrderedSearch.h"
#include "UnOrderedSearch.h"
#include "BestMatchSearch.h"

template<class T>
vector<T> extractStringValues(string str)
{
    vector<T> vecValues;

    stringstream ss;

    // Storing the string into string stream
    ss << str;

    // Running loop till the end of the stream 
    string temp;
    T found;
    while(!ss.eof()) {

        // extracting word by word from stream
        ss >> temp;

        // Checking the given word is integer or not
        if (stringstream(temp) >> found)
            vecValues.push_back(found);

        // To save from space at the end of string
        temp = "";
    }

    return vecValues;
}

void MatrixData::IntializeMatrix(vector<string> vecRows) {
    
    try {
        // check input argument
        if (vecRows.size() == 0) {
            throw exception("Row has no elements");
        }

        for (auto row : vecRows)
        {
            // extract integers from row string
            vector<int> vecRow = extractStringValues<int>(row);

            int iCol = (m_column == 0) ? vecRow.size() : m_column;
            int iRow = (m_row == 0) ? vecRows.size() : m_row;

            // restrict number of columns in row
            vector<int> subRow(vecRow.begin(), vecRow.begin() + iCol);

            // push row of int in to matrix
            m_Matrix.push_back(subRow);

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

void MatrixData::SearchSequence(string searchLine) {
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
            pSearch->SearchSequence(m_Matrix, seqInts);
        }
        else {
            cout << "Error: Search type is not valid" << endl;
        }

    }
    catch (...) {
        cout << "Error: Sequence search failed" << endl;
    }
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