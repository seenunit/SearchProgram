#include "MatrixData.h"
#include "OrderedSearch.h"
#include "MatrixGenerator.h"
#include <fstream>
#include <ctime>

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

inline void beginetime(clock_t &time) {
	if (time != 0)
		time = clock();
}

inline void elapsedtimeFile(std::ofstream &timefile, clock_t begin_time) {
	if (begin_time != 0) {
		float elapsedtime = float(clock() - begin_time) / CLOCKS_PER_SEC;
		std::cout << "elapsed time: " << elapsedtime << std::endl;
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

int main(int argc, char **argv) {

    std::string strDataFile;
    MatrixDataType vecRowLines;
    int row, column;
    MatrixGenerator matGen;

    if (argc == 1) {
        std::cout << "Specify matrix data (.dat) file as argument" << std::endl;
        std::cout << "./SearchProgram matrix.dat <search.txt>" << std::endl;
    }
    else if (argc == 2 || argc == 3 || argc == 4) {

		strDataFile = argv[1];

		if (strDataFile == "-test") {

			TestMatrixSearch();

			std::cout << "Press any key to exit";
			std::cin.get();

			return 0;			
		}

		std::ofstream timefile;
		clock_t begin_time = 0;

		if (argc == 4) {

			std::string timearg = argv[3];

			if (timearg == "-time") {
				timefile.open("time.txt");
				begin_time = clock();
			}
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

			if (argc == 4) {
				std::string timearg = argv[3];

				if (timearg == "-testtime") {
					TestRandomMatrixSearch(matrix);
				}
			}

			if (argc > 2) {

				std::string strSearchFile = argv[2];

				//std::vector<std::string> vecSerachSeqs = FileRead(strSearchFile);
				std::vector<std::string> vecSerachSeqs{};

				ret = matGen.ReadSearchFile(strSearchFile, vecSerachSeqs);

				if (ret == 1) {

					std::cout << "Matched row indices" << std::endl;
					for (auto strSearch : vecSerachSeqs) {

						std::string searchType;
						std::vector<int> sequence;

						matrix.GetSearchInfo(strSearch, searchType, sequence);

						std::vector<int> vecIndex{};

						beginetime(begin_time);
						matrix.SearchSequence(searchType, sequence, vecIndex);
						elapsedtimeFile(timefile, begin_time);

						printIndices(vecIndex);
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

					std::string searchType;
					std::vector<int> sequence;

					matrix.GetSearchInfo(line, searchType, sequence);

					std::vector<int> vecIndex{};

					beginetime(begin_time);
					matrix.SearchSequence(searchType, sequence, vecIndex);
					elapsedtimeFile(timefile, begin_time);

					printIndices(vecIndex);
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