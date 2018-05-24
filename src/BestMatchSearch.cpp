#include "BestMatchSearch.h"
#include <algorithm>



BestMatchSearch::BestMatchSearch()
{
}


BestMatchSearch::~BestMatchSearch()
{
}

void BestMatchSearch::SearchSequence(MatrixDataType matrix, vector<int> vecSequnce)
{
	try {

		vector<int> vecMatchCount;

		// iterate thorugh each row
		for (auto row : matrix) {

			// find sequence match count on row
			int count = BasicOrderedSearch(row, vecSequnce);

			// push match count to vector
			vecMatchCount.push_back(count);
		}

		// get iterator of max match count in vector
		auto result = max_element(vecMatchCount.begin(), vecMatchCount.end());

		cout << "best match row: ";

		// check the max element value is greater than 0
		if (*result > 0) {
			cout << distance(vecMatchCount.begin(), result) + 1 << endl;
		}
		else {
			cout << "None" << endl;
		}
	}
	catch (exception ex) {
		cout << "Error: Best match of sequence failed due to: " << ex.what() << endl;
	}

    return; 
}