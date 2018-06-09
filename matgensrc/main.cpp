#include <iostream>
#include "../src/MatrixGenerator.h"

int main(int argc, char **argv) {

	int row, column;

	if (argc == 1 || argc == 2) {

		std::cout << "Enter the row, column values and input text file as arguments" << std::endl;
		std::cout << "./MatrixGenerator row column" << std::endl;
	}
	else if(argc == 3 || argc == 4 ){

		row = atoi(argv[1]);
		column = atoi(argv[2]);

		std::string filename = "matrix.dat";

		std::vector<std::string> vecIntValues;
		MatrixGenerator matGen;

		bool bCreateText = false;

		if (argc == 4) {

			std::string infilename = argv[3];

			if (infilename == "-text") {
				bCreateText = true;
			}
			else {
				int ret = matGen.ReadSearchFile(infilename, vecIntValues);

				if (ret == 1) {
					ret = matGen.GenerateMatrixFile(filename, row, column, vecIntValues);

					if (ret == 1) {
						std::cout << "Matrix file " << filename << " is generated" << std::endl;
					}
					else {
						std::cout << "Warning: failed to generate the matrix file" << std::endl;
					}
				}
				else {
					std::cout << "Warning: failed to read input matrix file" << std::endl;
				}

				std::cout << "Press any key to exit";
				std::cin.get();
				return 0;
			}
		}

		int ret = matGen.GenerateRandomMatrixFile(filename, row, column, bCreateText);

		if (ret == 1) {
			std::cout << "Matrix file " << filename << " is generated" << std::endl;
		}
		else {
			std::cout << "Warning: failed to generate the matrix file" << std::endl;
		}

	}

	std::cout << "Press any key to exit";
	std::cin.get();

	return 0;
}