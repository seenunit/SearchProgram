#include "MatrixData.h"
#include <ctime>
#include <sstream>
#include <fstream>

struct TestData {
	std::string input;
	std::vector<int> baseOutput;
};

struct SearchDataTime{
	std::string searchtype;
	std::vector<int> sequence;
	std::vector<int> vecIndex;
	double elapsedtime;
};



void TestMatrixSearch() {

	// Hardcode the test data
	std::vector<std::string> vecRowLines{
		"25 45 12 78 34 23 987 465 23 45",
		"23 45 12 57 9 64 92 753 10 34",
		"12 57 -9 10 34 26 80 10 34 -89",
		"-34 29 29 29 29 29 -78 -54 76 30",
		"49 39 29 29 29 29 19 9 59 69",
		"29 29 29 -78 -54 76 30 -34 29 29",
		"35 48 35 35 48 35 22 45 -10 35",
		"35 48 35 35 48 35 35 48 35 26",
		"56 26 80 95 34 27 48 35 29 45"
	};

	std::vector<TestData> tests{
	{ "searchSequence 35 48 35 35", std::vector<int>{7, 8} },
	{ "searchBestMatch 35 48 35 35", std::vector<int>{7} },
	{ "searchUnordered 23 45 23", std::vector<int>{1} },
	{ "searchUnordered 29 29 29", std::vector<int>{4, 5, 6} },
	{ "searchSequence 10 34", std::vector<int>{2,3} },
	{ "searchSequence 29 29 29 -78", std::vector<int>{4,6} },
	{ "searchUnordered 10 10 34 10", std::vector<int>{} },
	{ "searchUnordered 29 29 29 29 29 29 29", std::vector<int>{} },
	{ "searchUnordered 987 465 23 45 -54", std::vector<int>{} },
	{ "searchBestMatch 23 45", std::vector<int>{1} },
	{ "searchSequence 29 29", std::vector<int>{4, 5, 6} },
	{ "searchBestMatch 29 29", std::vector<int>{4} },
	{ "searchBestMatch 30 31 32 33", std::vector<int>{4} },
	{ "searchSequence 30 31 32 33", std::vector<int>{} },
	{ "searchUnordered 30 31 32 33", std::vector<int>{} },
	{ "searchSequence 12 57 -9 10 34 26 80 10 34 -89 -1", std::vector<int>{} },
	{ "searchSequence 29 29 29 -78 -54 76 30", std::vector<int>{4, 6} },
	{ "searchBestMatch 35 48 35 29", std::vector<int>{7}}, // first best match row
	{ "searchBestMatch 20 72 41 95", std::vector<int>{9} }, // single last match - only 95
	{ "searchBestMatch -34 29 19 9 64", std::vector<int>{5} },// middle best match
	{ "searchBestMatch 56 26 80 10", std::vector<int>{9} }, // first best match compared to last best match
	{ "searchBestMatch 49 53 90 17", std::vector<int>{5} }, // single first match - only 49
	{ "searchBestMatch 50 53 90 17", std::vector<int>{} }, // no match found
	{ "searchBestMatch 50 48 35 29", std::vector<int>{9} } // last best match
	};

	// Create and intialize matrix
	MatrixData matrix(vecRowLines.size(), 10);
	matrix.IntializeMatrix(vecRowLines);

	matrix.PrintMatrixData();

	// supress cout statements
	std::cout.setstate(std::ios_base::failbit);

	std::vector<std::vector<int>> testsOutput;	

	// run through search functions using test data
	for (auto test : tests) {
		std::string searchType;
		std::vector<int> sequence;

		matrix.GetSearchInfo(test.input, searchType, sequence);

		int size = (int)sequence.size();

		int *pSequence = new int[size];
		for (int i = 0; i < size; i++)
		{
			pSequence[i] = sequence[i];
		}

		std::vector<int> vecIndex{};
		matrix.SearchSequence(searchType, pSequence, size, vecIndex);
		testsOutput.push_back(vecIndex);

		if (pSequence) delete[] pSequence;
	}
	
	// Revert back to original cout state
	std::cout.clear();


	// Compare base output and test oupt
	for (size_t i = 0; i < testsOutput.size() && i < tests.size(); i++)	{
		auto output = testsOutput[i];
		auto baseOutPut = tests[i].baseOutput;

		if (output == baseOutPut) {
			std::cout << tests[i].input << ": " << "passed" << std::endl;
		}
		else {
			std::cout << tests[i].input << ": " << "failed" << std::endl;
		}
	}
	
}

void TestRandomMatrixSearch(MatrixData &matrix) {
		
	clock_t begin_time = 0;
	std::ofstream timefile("time.txt");

	std::cout << "Random test is started" << std::endl;


	int testsize = 3000;
	int sequencesize = 20;


	double totaltime = 0;

	std::stringstream ss;

	ss << std::fixed;
	ss << std::setprecision(9);

	int  k = 0;

	// supress cout statements
	std::cout.setstate(std::ios_base::failbit);

	srand((unsigned int) time(nullptr));
	// Use current time as seed for random generator	
	for (int i = 0; i < testsize; i++)
	{
		SearchDataTime testdata;

		if (k == 0) {
			testdata.searchtype = "searchSequence";
			k++;
		}
		else if (k == 1) {
			testdata.searchtype = "searchUnordered";
			k++;
		}
		else if (k == 2) {
			testdata.searchtype = "searchBestMatch";
			k = 0;
		}

		for (int j = 0; j < sequencesize; j++)
		{
			// Storing the string into string stream
			testdata.sequence.push_back(rand());
		}
		
		int *pSequence = new int[sequencesize];
		for (int j = 0; j < sequencesize; j++)
		{
			pSequence[j] = testdata.sequence[j];
		}

		std::vector<int> vecIndex{};
		begin_time = clock();
		matrix.SearchSequence(testdata.searchtype, pSequence, sequencesize, vecIndex);
		double elapsedtime = (double(clock() - begin_time) / CLOCKS_PER_SEC) * 1000000;

		if (pSequence) delete[] pSequence;

		totaltime += elapsedtime;

		ss << testdata.searchtype << " ";
		for (auto value : testdata.sequence) {
			ss << value << " ";
		}
		ss << " , elapsed time: " << elapsedtime << " us, row values: ";
		for (auto index : vecIndex) {
			ss << index << " ";
		}
		ss << std::endl;

		std::cout << ss.str();
		timefile << ss.str();

		ss.clear();
	}
	
	// Revert back to original cout state
	std::cout.clear();
	
	double averagetime = totaltime / testsize;

	std::cout << "Average time taken: " << averagetime << " microseconds" << std::endl;
	timefile << "Average time taken: " << averagetime << " microseconds" << std::endl;

	std::cout << "File time.txt is generated with elapsed time(in microseconds)" << std::endl;

	return;
}
