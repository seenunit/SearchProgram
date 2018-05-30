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
    int GenerateMatrixFile(const string &filename, int row, int column, const vector<string> &vecIntValues);

	int GenerateRandomMatrixFile(const string &filename, int row, int column, bool bText = false);

    int ReadMatrixFile(const string &filename, int &row, int &column, vector<vector<int>> &outMatrix);

    int ReadSearchFile(const string &filename, vector<string> &outStrings);

private:
    string m_key{ "seenunit" };
};

template<class T>
vector<T> extractStringValues(const string &str)
{
    vector<T> vecValues;

	// Storing the string into string stream
    stringstream ss(str);

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