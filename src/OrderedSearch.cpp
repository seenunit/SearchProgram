#include "OrderedSearch.h"



OrderedSearch::OrderedSearch()
{
}


OrderedSearch::~OrderedSearch()
{
}

/*
Algorithm:
1. Take each row from the matrix
2. Find number of times match found with sequence in row
3. Push match count in to vector 
4. Display the (index + 1) of vector which are having more than 0 matches
*/

vector<int> OrderedSearch::SearchSequence(MatrixDataType matrix, vector<int> vecSequnce)
{

	vector<int> vecIndex{};
	try {

		vector<int> vecMatchCount;

		vector<int> vecPrefix = GetSequenePrefixVector(vecSequnce);

		// iterate thorugh each row
		for (auto row : matrix) {

			if (vecSequnce.size() > row.size())
				continue;

			// find sequence match count on row
            // check for single sequence match 
			//int count = LinearSearchSequenceCount(row, vecSequnce, false);
			int count = KMPSearchSequenceCount(row, vecSequnce, vecPrefix, false);

			// push match count to vector
			vecMatchCount.push_back(count);
		}

		cout << "Ordered match rows: ";
		// go thorugh match count vector 
		// display index of vector whose count more than 0
		for (size_t i = 0; i < vecMatchCount.size(); i++) {
			if (vecMatchCount[i] > 0) {
				vecIndex.push_back(i + 1);
				cout << i + 1 << " ";
			}
		}
		cout << endl;
	}
	catch (exception ex) {
		cout << "Error: Ordered match of sequence failed due to: " << ex.what() << endl;
	}

    return vecIndex;
}

/*
Algorithm:
1. Iterate through input row
2. Check first element of sequence match with the row ith element 
3. If it matches, then get sub row starting from that element
	- iterate thorugh sub row and sequence 
	- check all sequence elements matching
	- If macthes increase the match count.
	- If not break the loop
4. If not matches, Go for next element 
5. return the number match count
*/
int LinearSearchSequenceCount(vector<int> row, vector<int> sequence, bool bCount)
{
	int count = 0;

	// Iterate through row elements
	for (size_t i = 0; i < row.size(); i++) {

		// Check first element of sequence match with the row's ith element 
		if (row[i] == sequence[0]) {

			// get sub row vector
			vector<int> subRow(row.begin() + i, row.end());

			for (size_t j = 1; j < sequence.size() && j < subRow.size(); j++) {

				// check sub row element matches with sequence element
				if (sequence[j] != subRow[j])
					break;
				// if all elements are matching then increase the match count
				if (j == sequence.size() - 1)
					count++;
                
                // break the loop for first sequence match
                if (bCount == false && count > 0)
                    break;
			}
		}
	}

	return count;
}


vector<int> GetSequenePrefixVector(vector<int> vecSequence) {

	vector<int> vecLongestPrefix;

	int size = vecSequence.size();

	// count of previous value
	int count = 0;

	// first one is always 0
	vecLongestPrefix.push_back(0);

	int i = 1;
	while (i < size) {

		if (vecSequence[i] == vecSequence[count]) {
			count++;
			vecLongestPrefix.push_back(count);
			i++;
		}
		else {
			if (count != 0) {
				count = vecLongestPrefix[count - 1];
			}
			else
			{
				vecLongestPrefix.push_back(0);
				i++;
			}
		}
	}

	return vecLongestPrefix;
}

int KMPSearchSequenceCount(vector<int> row, vector<int> sequence, vector<int> vecSeqPrefix, bool bCount) {

	int count = 0;

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
			count++;

			// break the loop for first sequence match
			if (bCount == false && count > 0)
				break;

			j = vecSeqPrefix[j - 1];
		}

		// mismatch after j matches
		else if (i < N && sequence[j] != row[i])
		{
			// Do not match vecSeqPrefix[0..vecSeqPrefix[j-1]] integers,
			// they will match anyway
			if (j != 0)
				j = vecSeqPrefix[j - 1];
			else
				i = i + 1;
		}
	}

	return count;
}