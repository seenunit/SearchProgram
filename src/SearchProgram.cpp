#include "MatrixData.h"
#include "OrderedSearch.h"
#include <fstream>

vector<string> FileRead(string strFileName) {    

    vector<string>  vecString;

    ifstream infile(strFileName);

    if (infile.is_open()) {
        string strLine;
        while (getline(infile, strLine)) {
            vecString.push_back(strLine);
        }
    }
        
    return vecString;
}

int main(int argc, char **argv) {
    
    string strDataFile;
    vector<string> vecRowLines;
    int row, column;

    if (argc == 1 || argc == 2) {
        
        if (argc == 1) {
            cout << "Enter the matrix data(.dat) file" << endl;
            cin >> strDataFile;
        }
        else {
            strDataFile = argv[1];
        }

        // Read row and column from console
        cout << "Enter the number of rows and columns: <row> <column>" << endl;
        cin >> row >> column;

        cout << "Enter the search type and sequence of integers e.g. as given below" << endl;
        cout << "<searchSequence 1 3 4 3 234 6 7>" << endl;
        cout << "<searchUnordered 1 3 4 2>" << endl;
        cout << "<searchBestMatch 2 4 5 3 5>" << endl;
        cout << "Type \"exit\" to exit the program" << endl;

        // Validate and read the matrix file
        vecRowLines = FileRead(strDataFile);

        // Create and intialize matrix
        MatrixData matrix(row, column);
        matrix.IntializeMatrix(vecRowLines);

#ifdef DEBUG
        matrix.PrintMatrixData();
#endif // DEBUG
        
        for (string line; std::getline(std::cin, line); )
        {
            // exit search program 
            if (line.compare("exit") == 0)
                break;

            if (!line.empty()) {
                matrix.SearchSequence(line);
            }
        }
    }
    else if(argc == 3) {

        strDataFile = argv[1];

        // Validate and read the matrix file
        vecRowLines = FileRead(strDataFile);

        // Create and intialize matrix
        MatrixData matrix;
        matrix.IntializeMatrix(vecRowLines);

        string strSearchFile = argv[2];

        vector<string> vecSerachSeqs = FileRead(strSearchFile);
        for (auto strSearch : vecSerachSeqs) {
            matrix.SearchSequence(strSearch);
        }        
    }
    else {
        cout << "Error: Not a valid arguments" << endl;
    }

    cout << "Goodbye.\n";

    cin.get();

    return 0;
}