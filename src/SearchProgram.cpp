#include "MatrixData.h"
#include "OrderedSearch.h"
#include "MatrixGenerator.h"
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
    MatrixDataType vecRowLines;
    int row, column;
    MatrixGenerator matGen;

    if (argc == 1) {
        cout << "Specify matrix data (.dat) file as argument" << endl;
        cout << "./SearchProgram matrix.dat <search.txt>" << endl;
    }
    else if (argc == 2 || argc == 3) {

		strDataFile = argv[1];

		if (strDataFile == "-test") {

			TestMatrixSearch();

			cout << "Press any key to exit";
			cin.get();

			return 0;			
		}

        // Validate and read the matrix file
        //vecRowLines = FileRead(strDataFile);
		cout << "Reading the matrix file" << endl;
        int ret = matGen.ReadMatrixFile(strDataFile, row, column, vecRowLines);

        if (ret == 1) {
            
			cout << "intializing the matrix" << endl;
            // Create and intialize matrix
            MatrixData matrix(row, column);
            matrix.IntializeMatrix(vecRowLines);

			if (argc == 3) {

				string strSearchFile = argv[2];

				//vector<string> vecSerachSeqs = FileRead(strSearchFile);
				vector<string> vecSerachSeqs{};

				ret = matGen.ReadSearchFile(strSearchFile, vecSerachSeqs);

				if (ret == 1) {

					cout << "Matched row indices" << endl;
					for (auto strSearch : vecSerachSeqs) {
						matrix.SearchSequence(strSearch);
					}
				}
				else {
					cout << "Error: failed to read search file" << endl;
				}
			}

			// command line interface
			cout << "==============Command Line Interface for Search Program===============================" << endl;
			cout << "Enter the search type and sequence of integers e.g. as given below" << endl;
			cout << "<searchSequence 1 3 4 3 234 6 7>" << endl;
			cout << "<searchUnordered 1 3 4 2>" << endl;
			cout << "<searchBestMatch 2 4 5 3 5>" << endl;
			cout << "or type \"exit\" to exit the program" << endl;


			for (string line; std::getline(std::cin, line); )
			{
				// exit search program 
				if (line.compare("exit") == 0)
					return 0;

				if (!line.empty()) {
					matrix.SearchSequence(line);
				}
			}
        }
        else {
            cout << "Error: failed to read matrix file" << endl;
        }
    }
    else {
        cout << "Error: Not a valid arguments" << endl;
    }

    cout << "Press any key to exit";

    cin.get();

    return 0;
}