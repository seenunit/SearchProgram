#include "MatrixData.h"

struct TestData {
	string input;
	vector<int> baseOutput;
};


void TestMatrixSearch() {

	// Hardcode the test data
	vector<string> vecRowLines{
		"23 45 12 78 34 27 987 465 23 45",
		"23 45 12 57 9 64 92 753 10 34",
		"12 57 -9 10 34 26 80 10 34 -89",
		"-34 29 29 29 29 29 -78 -54 76 30",
		"49 39 29 29 29 29 19 9 59 69",
		"29 29 29 -78 -54 76 30 -34 29 29 "
	};

	vector<TestData> tests{
	{ "searchSequence 10 34", vector<int>{2,3} },
	{ "searchSequence 29 29 29 -78", vector<int>{4,6} },
	{ "searchUnordered 10 10 34 10", vector<int>{} },
	{ "searchUnordered 29 29 29", vector<int>{4, 5, 6} },
	{ "searchUnordered 29 29 29 29 29 29 29", vector<int>{} },
	{ "searchUnordered 23 45 23", vector<int>{1} },
	{ "searchUnordered 987 465 23 45 -54", vector<int>{} },
	{ "searchBestMatch 23 45", vector<int>{1} },
	{ "searchSequence 29 29", vector<int>{4, 5, 6} },
	{ "searchBestMatch 29 29", vector<int>{4} },
	{ "searchBestMatch 30 31 32 33", vector<int>{} },
	{ "searchSequence 30 31 32 33", vector<int>{} },
	{ "searchUnordered 30 31 32 33", vector<int>{} },
	{ "searchSequence 12 57 -9 10 34 26 80 10 34 -89 -1", vector<int>{} },
	{ "searchSequence 29 29 29 -78 -54 76 30", vector<int>{4, 6} }
	};

	// Create and intialize matrix
	MatrixData matrix(vecRowLines.size(), 10);
	matrix.IntializeMatrix(vecRowLines);

	matrix.PrintMatrixData();

	// supress cout statements
	cout.setstate(std::ios_base::failbit);

	vector<vector<int>> testsOutput;	

	// run through search functions using test data
	for (auto test : tests) {
		vector<int> vecIndex = matrix.SearchSequence(test.input);
		testsOutput.push_back(vecIndex);
	}
	
	// Revert back to original cout state
	cout.clear();


	// Compare base output and test oupt
	for (size_t i = 0; i < testsOutput.size() && i < tests.size(); i++)	{
		auto output = testsOutput[i];
		auto baseOutPut = tests[i].baseOutput;

		if (equal(output.begin(), output.end(), baseOutPut.begin(), baseOutPut.end()) == true) {
			cout << tests[i].input << ": " << "passed" << endl;
		}
		else {
			cout << tests[i].input << ": " << "failed" << endl;
		}
	}
	
}
