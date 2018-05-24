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

		map<int,int> mapMatchCount;
		
		// search the sequence elements in each row
		for (int i = 0; i < matrix.size(); i++) {

			auto row = matrix[i];

			// sort the row for large row size
			// TODD

			vector<int> vecValCount;
			int prev = 0;
			for (auto val : vecSequnce) {
				
				// use binary/interpolation search algorithm for optimization
				// TODO

				int count = LinearFindValueCount(row, val);

				if (count == 0)
					break;				

				if (prev == count)
					vecValCount.push_back(count);
				else {
					if (prev == 0) {
						prev = count;
						vecValCount.push_back(count);
					}
					else
					{
						break;
					}						
				}					
			}

			if (vecValCount.size() == vecSequnce.size()) {
				mapMatchCount.insert(make_pair(i + 1, vecValCount[0]));
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
int LinearFindValueCount(vector<int> row, int x)
{
	int count = 0;
	for (auto val : row) {
		if (val == x)
		{
			count++;
		}
	}

	return count;
}
