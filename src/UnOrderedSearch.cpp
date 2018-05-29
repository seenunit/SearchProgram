#include "UnOrderedSearch.h"
#include <algorithm>
#include <map>



UnOrderedSearch::UnOrderedSearch()
{
}


UnOrderedSearch::~UnOrderedSearch()
{
}


vector<int> UnOrderedSearch::SearchSequence(const MatrixDataType &matrix, const vector<int> &sequence)
{
	vector<int> vecIndex{};
	try {

        vector<int> sortedSequence = sequence;

        // sort the sequence
        sort(sortedSequence.begin(), sortedSequence.end());

        // search the sequence elements in each row
		for (size_t i = 0; i < matrix.size(); i++) {

			auto row = matrix[i];

			if (sequence.size() > row.size())
				continue;

			// returns 1 of unordered sequence is found
			int ret = UnorderedSearchSortedSequence(row, sortedSequence);

            // if hope still there consider that row
            if (ret == 1) {
                vecIndex.push_back(i + 1);
            }
		}
		
		cout << "UnOrdered match rows: ";
		// go thorugh match vector 
		// display index of vector whose count more than 0
        for (auto index : vecIndex) {
            cout << index << " ";
        }
		cout << endl;
	}
	catch (exception ex) {
		cout << "Error: UnOrdered match of sequence failed due to: " << ex.what() << endl;
	}
	

    return vecIndex;
}

// returns number of times value found in row
int LinearSearchValueCount(const vector<int> &row, int x, bool bCount) {
	int count = 0;
	for (auto val : row) {
		if (val == x)
		{
			count++;
		}

        // break the loop for first match
        if (bCount == false && count > 0)
            break;
	}

	return count;
}

// return row index of the value at first encounter
int LinearSearchValue(const vector<int> &row, int x) {

    for (size_t i = 0; i < row.size(); i++) {
        if (row[i] == x)
            return i;
    }

    // return -1 if value not find
    return -1;
}

int UnorderedSearchSortedSequence(const vector<int> &row, const vector<int> &sequence) {

	int M = sequence.size();
	int N = row.size();

	int i = 0;  // index for row[]
	int j = 0;  // index for sequence[]
	while (i < N)
	{
		if (sequence[j] == row[i])
		{
			j++;
			i++;
		}

		if (j == M)
		{
			// Found sequence match
			return 1;
		}
		// mismatch after j matches
		else if (i < N && sequence[j] != row[i])
		{
			i = i + 1;
		}
	}
	
	// return -1 if unordered sequence not found
	return -1;
}