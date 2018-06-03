#include "MatrixData.h"
#include "OrderedSearch.h"
#include "MatrixGenerator.h"

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
        //int ret = matGen.ReadMatrixFile(strDataFile, row, column, vecRowLines);
		int **ppMatrix = nullptr;
		int ret = matGen.ReadMatrixFile(strDataFile, row, column, ppMatrix);

        if (ret == 1) {
            
			std::cout << "intializing the matrix" << std::endl;
            // Create and intialize matrix
            MatrixData matrix(row, column);
			//matrix.IntializeMatrix(vecRowLines);
			//matrix.IntializeMatrixArray();
			matrix.IntializeMatrixArray(ppMatrix);

			// delete the local matrix data
			if (ppMatrix) {
				for (int i = 0; i < row; i++)
				{
					delete[] ppMatrix[i];
				}
				delete[] ppMatrix;

				ppMatrix = nullptr;
			}

			if (argc > 2) {

				std::string timearg = argv[2];

				if (timearg == "-testtime") {
					TestRandomMatrixSearch(matrix);

					std::cout << "Press any key to exit";
					std::cin.get();

					return 0;
				}

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

						int size = (int)sequence.size();

						int *pSequence = new int[size];
						for (int i = 0; i < size; i++)
						{
							pSequence[i] = sequence[i];
						}

						std::vector<int> vecIndex{};

						beginetime(begin_time);
						matrix.SearchSequence(searchType, pSequence, size, vecIndex);
						elapsedtimeFile(timefile, begin_time);

						if (pSequence) delete[] pSequence;

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

					int size = (int)sequence.size();

					int *pSequence = new int[size];
					for (int i = 0; i < size; i++)
					{
						pSequence[i] = sequence[i];
					}

					std::vector<int> vecIndex{};

					beginetime(begin_time);
					matrix.SearchSequence(searchType, pSequence, size, vecIndex);
					elapsedtimeFile(timefile, begin_time);

					if(pSequence) delete[] pSequence;

					printIndices(vecIndex);
				}
			}
        }
        else {
            std::cout << "Error: failed to read matrix file" << std::endl;
        }
		if (ppMatrix) {
			for (int i = 0; i < row; i++)
			{
				delete[] ppMatrix[i];
			}
			delete[] ppMatrix;

			ppMatrix = nullptr;
		}
    }
    else {
        std::cout << "Error: Not a valid arguments" << std::endl;
    }

    std::cout << "Press any key to exit";

    std::cin.get();

    return 0;
}