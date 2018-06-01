#ifndef MATRIXGENERATOR
#define MATRIXGENERATOR

#include <vector>
#include <string>
#include <sstream>

//using namespace std;

class MatrixGenerator
{
public:
    MatrixGenerator();
    ~MatrixGenerator();

public:
    int GenerateMatrixFile(const std::string &filename, int row, int column, const std::vector<std::string> &vecIntValues);

	int GenerateRandomMatrixFile(const std::string &filename, int row, int column, bool bText = false);

    int ReadMatrixFile(const std::string &filename, int &row, int &column, std::vector<std::vector<int>> &outMatrix);

    int ReadSearchFile(const std::string &filename, std::vector<std::string> &outStrings);

private:
    std::string m_key{ "seenunit" };
};

template<class T>
void extractStringValues(const std::string &str, std::vector<T> &vecValues)
{
	// Storing the string into string stream
    std::stringstream ss(str);

	// Running loop till the end of the stream 
	std::string temp;
	T found;
	while (!ss.eof()) {

		// extracting word by word from stream
		ss >> temp;

		// Checking the given word is integer or not
		if (std::stringstream(temp) >> found)
			vecValues.push_back(found);

		// To save from space at the end of string
		temp = "";
	}

    return;
}

#endif //MATRIXGENERATOR