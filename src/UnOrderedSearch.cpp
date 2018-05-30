#include "UnOrderedSearch.h"
#include <algorithm>
#include <map>



UnOrderedSearch::UnOrderedSearch()
{
}


UnOrderedSearch::~UnOrderedSearch()
{
}


std::vector<int> UnOrderedSearch::SearchSequence(const MatrixDataType &matrix, const std::vector<int> &sequence)
{
	std::vector<int> vecIndex{};
	try {

        std::vector<int> sortedSequence = sequence;

        // sort the sequence
        sort(sortedSequence.begin(), sortedSequence.end());

        // search the sequence elements in each row
		for (size_t i = 0; i < matrix.size(); i++) {

			auto row = matrix[i];

			if (sequence.size() > row.size())
				continue;

			// returns 1 of unordered sequence is found
			int ret = UnorderedSearchSortedSequence(row, sortedSequence);

			// add row index to vector if ret is sucessful
            if (ret == 1) {
                vecIndex.push_back(i + 1);
            }
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: UnOrdered match of sequence failed due to: " << ex.what() << std::endl;
	}
	

    return vecIndex;
}

// returns number of times value found in row
int LinearSearchValueCount(const std::vector<int> &row, int x, bool bCount) {
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
int LinearSearchValue(const std::vector<int> &row, int x) {

    for (size_t i = 0; i < row.size(); i++) {
        if (row[i] == x)
            return i;
    }

    // return -1 if value not find
    return -1;
}

int UnorderedSearchSortedSequence(const std::vector<int> &row, const std::vector<int> &sequence) {

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