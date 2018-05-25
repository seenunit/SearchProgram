#include "UnOrderedSearch.h"
#include <algorithm>
#include <map>



UnOrderedSearch::UnOrderedSearch()
{
}


UnOrderedSearch::~UnOrderedSearch()
{
}


void UnOrderedSearch::SearchSequence(MatrixDataType matrix, vector<int> vecSequnce)
{
	try {

        vector<int> rowMatch;

        vector<int> sortedSequence = vecSequnce;

        // sort the sequence
        sort(sortedSequence.begin(), sortedSequence.end());

        // search the sequence elements in each row
		for (int i = 0; i < matrix.size(); i++) {

			auto row = matrix[i];

			// sort the row 
            sort(row.begin(), row.end());

            bool hope = true;
			for (auto val : sortedSequence) {

				// use binary/interpolation search algorithm for optimization
				// TODO

				int index = LinearSearchValue(row, val);

                if (index == 0) {
                    hope = false;
                    break;
                }

                // remove the element at index or negate the value
                row[index] = -row[index];
			}

            // if hope still there consider that row
            if (hope == true) {
                rowMatch.push_back(i + 1);
            }
		}
		
		cout << "UnOrdered match rows: ";
		// go thorugh match vector 
		// display index of vector whose count more than 0
        for (auto index : rowMatch) {
            cout << index << " ";
        }
		cout << endl;
	}
	catch (exception ex) {
		cout << "Error: UnOrdered match of sequence failed due to: " << ex.what() << endl;
	}
	

    return; //TODO
}

// returns number of times value found in row
int LinearSearchValueCount(vector<int> row, int x, bool bCount) {
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
int LinearSearchValue(vector<int> row, int x) {

    for (size_t i = 0; i < row.size(); i++) {
        if (row[i] == x)
            return i + 1;
    }

    // return 0 if value not find
    return 0;
}
