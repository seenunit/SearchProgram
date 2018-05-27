#include <iostream>
#include "../src/MatrixGenerator.h"

int main(int argc, char **argv) {

    int row, column;

    if (argc == 1 || argc == 2) {

        cout << "Enter the row, column and file name values as arguments" << endl;
        cout << "./MatrixGenerator row column <filename>" << endl;
    }
    else if(argc == 3 || argc == 4){

        row = atoi(argv[1]);
        column = atoi(argv[2]);

        string filename;

        if (argc == 4) {
            filename = argv[3];
        }
        else
        {
            filename = "matrix.dat";
        }

        int matrixLength = row * column;

        cout << "Enter the " << row << " rows of integers." << "for each row, enter " << column << " number of integers." << endl;
        cout << "To generate matrix(" << filename << ") file" << endl;
        
        vector<string> vecIntValues;

        // exit program after entering number of rows.
        string line;
        for (int i= 0; i < row && getline(std::cin, line); i++)
        {
            if (!line.empty()) {
                vecIntValues.push_back(line);
            }
        }
        MatrixGenerator matGen;

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