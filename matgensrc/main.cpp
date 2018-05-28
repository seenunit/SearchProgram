#include <iostream>
#include "../src/MatrixGenerator.h"

int main(int argc, char **argv) {

    int row, column;

    if (argc == 1 || argc == 2) {

        cout << "Enter the row, column values and input text file as arguments" << endl;
        cout << "./MatrixGenerator row column <filename.txt>(optional)" << endl;
    }
    else if(argc == 3 || argc == 4 ){

        row = atoi(argv[1]);
        column = atoi(argv[2]);

        string filename = "matrix.dat";

		int matrixLength = row * column;
		vector<string> vecIntValues;
		MatrixGenerator matGen;

        if (argc == 4) {
            string infilename = argv[3];
			int ret = matGen.ReadSearchFile(infilename, vecIntValues);
			
			if (ret == 0) {
				cout << "Warning: failed to read input matrix file" << endl;
			}

        }
		else
		{
			cout << "Enter the " << row << " rows of integers." << "for each row, enter " << column << " number of integers." << endl;
			cout << "To generate matrix(" << filename << ") file" << endl;

			// exit program after entering number of rows.
			string line;
			for (int i = 0; i < row && getline(std::cin, line); i++)
			{
				if (!line.empty()) {
					vecIntValues.push_back(line);
				}
			}
		}

        int ret = matGen.GenerateMatrixFile(filename, row, column, vecIntValues);

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