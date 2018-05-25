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

        vector<int> sortedSequence = vecSequnce;

        // sort the sequence
        sort(sortedSequence.begin(), sortedSequence.end());
        
        // search the sequence elements in each row
		for (int i = 0; i < matrix.size(); i++) {

			auto row = matrix[i];

			// sort the row 
            sort(row.begin(), row.end());

			map<int, > vecValCount;
			int prevCount = 0;
            int prevValue = 0;
			for (auto val : sortedSequence) {

                if (prevValue == val) {
                    continue;
                }
                else {
                    prevValue = val;
                }
				
				// use binary/interpolation search algorithm for optimization
				// TODO

				int count = LinearSearchValueCount(row, val, true);

				if (count == 0)
					break;				

				if (prevCount == count)
					vecValCount.push_back(count);
				else {
					if (prevCount == 0) {
						prevCount = count;
						vecValCount.push_back(count);
					}
					else
					{
						break;
					}						
				}					
			}


		}
		
		cout << "UnOrdered match rows: ";
		// go thorugh match count vector 
		// display index of vector whose count more than 0

		for (auto it : mapMatchCount) {
			cout << it.first << " ";
		}

		cout << endl;
	}
	catch (exception ex) {
		cout << "Error: UnOrdered match of sequence failed due to: " << ex.what() << endl;
	}
	

    return; //TODO
}

// returns number of times value found in row
int LinearSearchValueCount(vector<int> row, int x, bool bCount)
{
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
