#include <iostream>
#include <fstream>
#include "MatrixGenerator.h"


MatrixGenerator::MatrixGenerator()
{
}


MatrixGenerator::~MatrixGenerator()
{
}

inline string negateLine(string line) {

    for (size_t i = 0; i < line.length(); i++)
    {
        line[i] = ~line[i];
    }

    return line;
};

int MatrixGenerator::GenerateMatrixFile(string filename, int row, int column, vector<string> vecIntValues) {

    vector<string>  vecString;

    string strRW = to_string(row) + " " + to_string(column);
    vecString.push_back(negateLine(m_key + strRW));

    for (size_t i = 0; i < row; i++)
    {
        string line = vecIntValues[i];
        vecString.push_back(negateLine(m_key + line));
    }

    // write the file with the modified contents
    {
        std::ofstream outfile(filename);         
        for (auto line : vecString) outfile << line << '\n';
    }

    return 1;
}

int MatrixGenerator::ReadMatrixFile(string filename, int &row, int &column, vector<string> &outStrings) {
    
    ifstream infile(filename);

    if (infile.is_open()) {

        string strLine;
        
        // get row and column from file
        getline(infile, strLine);

        string line(negateLine(strLine));

        string key(line.begin(), line.begin() + m_key.length());

        if (key == m_key) {

            string sequnence(line.begin() + m_key.length(), line.end());
            vector<int> vecRW = extractStringValues<int>(sequnence);

            row = vecRW[0];
            column = vecRW[1];
        }
        else {
            return 0;
        }

        for (size_t i = 0; i < row && getline(infile, strLine); i++) {

            string line(negateLine(strLine));
                   
            string key(line.begin(), line.begin() + m_key.length());
            
            if (key == m_key) {
                string sequnence(line.begin() + m_key.length(), line.end());
                outStrings.push_back(sequnence);
            }
            else {
                return 0;
            }
        }
    }
    else {
        return 0;
    }

    return 1;
}


int MatrixGenerator::ReadSearchFile(string strFileName, vector<string> &outStrings) {

    ifstream infile(strFileName);

    if (infile.is_open()) {
        string strLine;
        while (getline(infile, strLine)) {
            outStrings.push_back(strLine);
        }
    }
    else {
        return 0;
    }

    return 1;
}