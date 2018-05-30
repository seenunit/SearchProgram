#include <iostream>
#include "../src/MatrixGenerator.h"

int main(int argc, char **argv) {

    int row, column;

    if (argc == 1 || argc == 2) {

        cout << "Enter the row, column values and input text file as arguments" << endl;
        cout << "./MatrixGenerator row column" << endl;
    }
    else if(argc == 3 || argc == 4 ){

        row = atoi(argv[1]);
        column = atoi(argv[2]);

        string filename = "matrix.dat";

		vector<string> vecIntValues;
		MatrixGenerator matGen;

		bool bCreateText = false;

        if (argc == 4) {

            string infilename = argv[3];

			if (infilename == "-text") {
				bCreateText = true;
			}
			else {
				int ret = matGen.ReadSearchFile(infilename, vecIntValues);

				if (ret == 1) {
					ret = matGen.GenerateMatrixFile(filename, row, column, vecIntValues);

					if (ret == 1) {
						cout << "Matrix file " << filename << " is generated" << endl;
					}
					else {
						cout << "Warning: failed to generate the matrix file" << endl;
					}
				}
				else {
					cout << "Warning: failed to read input matrix file" << endl;
				}

				cout << "Press any key to exit";
				cin.get();
				return 0;
			}
        }

		int ret = matGen.GenerateRandomMatrixFile(filename, row, column, bCreateText);

		if (ret == 1) {
			cout << "Matrix file " << filename << " is generated" << endl;
		}
		else {
			cout << "Warning: failed to generate the matrix file" << endl;
		}

    }

    cout << "Press any key to exit";
    cin.get();

    return 0;
}