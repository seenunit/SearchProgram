#ifndef MATRIXGENERATOR
#define MATRIXGENERATOR

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class MatrixGenerator
{
public:
    MatrixGenerator();
    ~MatrixGenerator();

public:
    int GenerateMatrixFile(string filename, int row, int column, vector<string> vecIntValues);

    int ReadMatrixFile(string filename, int &row, int &column, vector<string> &outSTrings);

    int ReadSearchFile(string filename, vector<string> &outSTrings);

private:
    string m_key{ "netvrita" };
};

template<class T>
vector<T> extractStringValues(string str)
{
    vector<T> vecValues;

    stringstream ss;

    // Storing the string into string stream
    ss << str;

    // Running loop till the end of the stream 
    string temp;
    T found;
    while (!ss.eof()) {

        // extracting word by word from stream
        ss >> temp;

        // Checking the given word is integer or not
        if (stringstream(temp) >> found)
            vecValues.push_back(found);

        // To save from space at the end of string
        temp = "";
    }

    return vecValues;
}

#endif //MATRIXGENERATOR