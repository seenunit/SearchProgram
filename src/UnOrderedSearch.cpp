#include "UnOrderedSearch.h"
#include <algorithm>
#include <map>



UnOrderedSearch::UnOrderedSearch()
{
}


UnOrderedSearch::~UnOrderedSearch()
{
}


vector<int> UnOrderedSearch::SearchSequence(MatrixDataType matrix, vector<int> vecSequnce)
{
	vector<int> vecIndex{};
	try {

        vector<int> sortedSequence = vecSequnce;

        // sort the sequence
        //sort(sortedSequence.begin(), sortedSequence.end());

        // search the sequence elements in each row
		for (size_t i = 0; i < matrix.size(); i++) {

			auto row = matrix[i];

			if (vecSequnce.size() > row.size())
				continue;
			
			// sort the row 
            //sort(row.begin(), row.end());

            bool hope = true;
			for (auto val : sortedSequence) {

				// binary search the row for a value
				int index = BinarySearchValue(row, val);

                // if returns -1 then value not found in row
                if (index == -1) {
                    hope = false;
                    break;
                }
				
                // remove the element at index or negate the value
                //row[index] = -row[index];
				row.erase(row.begin() + index);
			}

            // if hope still there consider that row
            if (hope == true) {
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
            return i;
    }

    // return -1 if value not find
    return -1;
}

// Binary search for a value and returns index
int BinarySearchValue(vector<int> row, int x)
{
	int l = 0;
	int r = row.size()-1;

	while (r >= l)
	{
		int mid = l + (r - l) / 2;

		if (row[mid] == x)
		{
			return mid;
		}
		if (row[mid] > x)
		{
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}

	// return -1 if value not find
	return -1;
}
