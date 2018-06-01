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
	float elapsedtime;
};



void TestMatrixSearch() {

	// Hardcode the test data
	std::vector<std::string> vecRowLines{
		"23 45 12 78 34 27 987 465 23 45",
		"23 45 12 57 9 64 92 753 10 34",
		"12 57 -9 10 34 26 80 10 34 -89",
		"-34 29 29 29 29 29 -78 -54 76 30",
		"49 39 29 29 29 29 19 9 59 69",
		"29 29 29 -78 -54 76 30 -34 29 29",
		"35 48 35 35 48 35 35 48 35 35",
		"35 48 35 35 48 35 35 48 35 26"
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
	{ "searchBestMatch 30 31 32 33", std::vector<int>{} },
	{ "searchSequence 30 31 32 33", std::vector<int>{} },
	{ "searchUnordered 30 31 32 33", std::vector<int>{} },
	{ "searchSequence 12 57 -9 10 34 26 80 10 34 -89 -1", std::vector<int>{} },
	{ "searchSequence 29 29 29 -78 -54 76 30", std::vector<int>{4, 6} }
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

		std::vector<int> vecIndex{};
		matrix.SearchSequence(searchType, sequence, vecIndex);
		testsOutput.push_back(vecIndex);
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

	std::vector<SearchDataTime> tests{};

	// Use current time as seed for random generator
	srand((unsigned int)time(nullptr));
	for (int i = 0, k=0; i < 1000; i++, k++)
	{
		SearchDataTime testdata;

		for (int j = 0; j < 20; j++)
		{
			// Storing the string into string stream
			testdata.sequence.push_back(rand());
		}

		if (k == 0) {
			testdata.searchtype = "searchSequence";
		}
		else if (k == 1) {
			testdata.searchtype = "searchUnordered";
		}
		else if (k == 2) {
			testdata.searchtype = "searchBestMatch";
			k = 0;
		}		
		tests.push_back(testdata);
	}
	

	// supress cout statements
	std::cout.setstate(std::ios_base::failbit);

	std::vector<std::vector<int>> testsOutput;

	// run through search functions using test data
	for (size_t i = 0; i < tests.size(); i++)
	{	
		auto test = tests[i];
		std::vector<int> vecIndex{};
		begin_time = clock();
		matrix.SearchSequence(test.searchtype, test.sequence, vecIndex);
		float elapsedtime = float(clock() - begin_time) / CLOCKS_PER_SEC;
		tests[i].elapsedtime = elapsedtime;
		tests[i].vecIndex = vecIndex;
	}

	// Revert back to original cout state
	std::cout.clear();

	std::stringstream ss;
	// Compare base output and test oupt
	for (size_t i = 0; i < tests.size() && i < tests.size(); i++) {
		
		ss << tests[i].searchtype << " elapsed time: " << tests[i].elapsedtime << " row values: ";
		for (auto index : tests[i].vecIndex) {
			ss << index << " ";
		}
		ss << std::endl;

		std::cout << ss.str();
		timefile << ss.str();

		ss.clear();
	}
}
