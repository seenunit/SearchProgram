#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "MatrixGenerator.h"


MatrixGenerator::MatrixGenerator()
{
}


MatrixGenerator::~MatrixGenerator()
{
}

inline std::string &negateLine(std::string &line) {

	for (size_t i = 0; i < line.length(); i++)
	{
		line[i] = ~line[i];
	}

	return line;
};

int MatrixGenerator::GenerateMatrixFile(const std::string &filename, int row, int column, const std::vector<std::string> &vecIntValues) {

	std::vector<std::string>  vecString;

	std::string strRW = std::to_string(row) + " " + std::to_string(column);
	vecString.push_back(strRW);

	for (int i = 0; i < row; i++)
	{
		std::string line = vecIntValues[i];
		vecString.push_back(line);
	}

	// write the file with the modified contents
	{
		std::ofstream outfile(filename);         
		for (auto line : vecString) {
			std::string nline = m_key + line;
			outfile << negateLine(nline) << '\n';
		}
	}

	return 1;
}

int MatrixGenerator::GenerateRandomMatrixFile(const std::string &filename, int row, int column, bool bText) {
	
	std::ofstream outtextfile;
	if (bText == true) {
		outtextfile.open("matrix.txt");
	}

	std::ofstream outfile(filename);

	std::string strRW = std::to_string(row) + " " + std::to_string(column);
	if (outtextfile.is_open()) outtextfile << strRW << '\n';
	if (outfile.is_open()) {
		std::string nline = m_key + strRW;
		outfile << negateLine(nline) << '\n';
	}

	// Use current time as seed for random generator
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < row; i++)
	{
		std::string line{};

		for (int  j = 0; j < column; j++)
		{
			// Storing the string into string stream
			line +=  std::to_string(rand()) + " ";
		}

		if (outtextfile.is_open()) outtextfile << line << '\n';
		
		if (outfile.is_open()) {
			std::string nline = m_key + line;
			outfile << negateLine(nline) << '\n';
		}
		else {
			return 0;
		}
	}

	return 1;
}

int MatrixGenerator::ReadMatrixFile(const std::string &filename, int &row, int &column, std::vector<std::vector<int>> &outMatrix) {
	
	std::ifstream infile(filename);

	if (infile.is_open()) {

		std::string strLine;
		
		// get row and column from file
		getline(infile, strLine);

		std::string line(negateLine(strLine));

		std::string key(line.begin(), line.begin() + m_key.length());

		if (key == m_key) {

			std::string sequnence(line.begin() + m_key.length(), line.end());
			std::vector<int> vecRW{};
			extractStringValues<int>(sequnence, vecRW);

			row = vecRW[0];
			column = vecRW[1];
		}
		else {
			return 0;
		}

		for (int i = 0; i < row && getline(infile, strLine); i++) {

			std::string line(negateLine(strLine));
				   
			std::string key(line.begin(), line.begin() + m_key.length());
			
			if (key == m_key) {
				std::string sequnence(line.begin() + m_key.length(), line.end());
				std::vector<int> vecIntegers{};
				extractStringValues<int>(sequnence, vecIntegers);
				outMatrix.push_back(vecIntegers);
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

int MatrixGenerator::ReadMatrixFile(const std::string &filename, int &row, int &column, int **& outMatrix) {

	std::ifstream infile(filename);

	if (infile.is_open()) {

		std::string strLine;

		// get row and column from file
		getline(infile, strLine);

		std::string line(negateLine(strLine));

		std::string key(line.begin(), line.begin() + m_key.length());

		if (key == m_key) {

			std::string sequnence(line.begin() + m_key.length(), line.end());
			std::vector<int> vecRW{};
			extractStringValues<int>(sequnence, vecRW);

			row = vecRW[0];
			column = vecRW[1];
		}
		else {
			return 0;
		}

		outMatrix = new int*[row];

		for (int i = 0; i < row && getline(infile, strLine); i++) {

			std::string line(negateLine(strLine));

			std::string key(line.begin(), line.begin() + m_key.length());

			if (key == m_key) {
				std::string sequnence(line.begin() + m_key.length(), line.end());
				std::vector<int> vecIntegers{};
				extractStringValues<int>(sequnence, vecIntegers);

				outMatrix[i] = new int[column] {0};

				for (int j = 0; j < column && j < (int)vecIntegers.size(); j++)
				{
					outMatrix[i][j] = vecIntegers[j];
				}
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


int MatrixGenerator::ReadSearchFile(const std::string &filename, std::vector<std::string> &outStrings) {

	std::ifstream infile(filename);

	if (infile.is_open()) {
		std::string strLine{};
		while (getline(infile, strLine)) {
			outStrings.push_back(strLine);
		}
	}
	else {
		return 0;
	}

	return 1;
}