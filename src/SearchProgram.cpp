#include "MatrixData.h"
#include "OrderedSearch.h"
#include "MatrixGenerator.h"
#include <fstream>

std::vector<std::string> FileRead(std::string strFileName) {    

    std::vector<std::string>  vecString;

    std::ifstream infile(strFileName);

    if (infile.is_open()) {
        std::string strLine;
        while (getline(infile, strLine)) {
            vecString.push_back(strLine);
        }
    }
        
    return vecString;
}

int main(int argc, char **argv) {

    std::string strDataFile;
    MatrixDataType vecRowLines;
    int row, column;
    MatrixGenerator matGen;

    if (argc == 1) {
        std::cout << "Specify matrix data (.dat) file as argument" << std::endl;
        std::cout << "./SearchProgram matrix.dat <search.txt>" << std::endl;
    }
    else if (argc == 2 || argc == 3) {

		strDataFile = argv[1];

		if (strDataFile == "-test") {

			TestMatrixSearch();

			std::cout << "Press any key to exit";
			std::cin.get();

			return 0;			
		}

        // Validate and read the matrix file
        //vecRowLines = FileRead(strDataFile);
		std::cout << "Reading the matrix file" << std::endl;
        int ret = matGen.ReadMatrixFile(strDataFile, row, column, vecRowLines);

        if (ret == 1) {
            
			std::cout << "intializing the matrix" << std::endl;
            // Create and intialize matrix
            MatrixData matrix(row, column);
            matrix.IntializeMatrix(vecRowLines);

			if (argc == 3) {

				std::string strSearchFile = argv[2];

				//std::vector<std::string> vecSerachSeqs = FileRead(strSearchFile);
				std::vector<std::string> vecSerachSeqs{};

				ret = matGen.ReadSearchFile(strSearchFile, vecSerachSeqs);

				if (ret == 1) {

					std::cout << "Matched row indices" << std::endl;
					for (auto strSearch : vecSerachSeqs) {
						matrix.SearchSequence(strSearch);
					}
				}
				else {
					std::cout << "Error: failed to read search file" << std::endl;
				}
			}

			// command line interface
			std::cout << "==============Command Line Interface for Search Program===============================" << std::endl;
			std::cout << "Enter the search type and sequence of integers e.g. as given below" << std::endl;
			std::cout << "<searchSequence 1 3 4 3 234 6 7>" << std::endl;
			std::cout << "<searchUnordered 1 3 4 2>" << std::endl;
			std::cout << "<searchBestMatch 2 4 5 3 5>" << std::endl;
			std::cout << "or type \"exit\" to exit the program" << std::endl;


			for (std::string line; std::getline(std::cin, line); )
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
            std::cout << "Error: failed to read matrix file" << std::endl;
        }
    }
    else {
        std::cout << "Error: Not a valid arguments" << std::endl;
    }

    std::cout << "Press any key to exit";

    std::cin.get();

    return 0;
}