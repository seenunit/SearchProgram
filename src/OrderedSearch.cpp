#include "OrderedSearch.h"
#include <algorithm>


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

void OrderedSearch::SearchSequence(const MatrixDataType &matrix, const MatrixDataType &sortedMatrix, const std::vector<int> &sequence, std::vector<int> &vecIndex)
{

	try {

		if (sequence.size() > matrix[0].size())
			throw std::runtime_error("Sequence size is more than matrix row size");

		std::vector<int> vecMatchCount;

		std::vector<int> vecPrefix = GetSequenePrefixVector(sequence);

		// iterate thorugh each row
		for (size_t i = 0; i < matrix.size(); i++) {

			auto sortrow = sortedMatrix[i];

			if (std::binary_search(sortrow.begin(), sortrow.end(), sequence[0]) == false) {
			//if (InterpolationSearchValue(sortrow, sequence[0]) == false) {
				continue;
			}

			auto row = matrix[i];

			std::vector<int>::iterator it = std::find(row.begin(), row.end(), sequence[0]);

			std::vector<int> subrow(it, row.end());

			// find sequence match count on row
            // check for single sequence match 
			//int count = LinearSearchSequenceCount(row, vecSequnce, false);
			int count = KMPSearchSequenceCount(subrow, sequence, vecPrefix, false);

			// add row index to vector if ret is sucessful
			if (count > 0) {
				vecIndex.push_back(i + 1);
			}
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: Ordered match of sequence failed due to: " << ex.what() << std::endl;
	}

    return;
}

void OrderedSearch::SearchSequence(const MatrixDataArray& matrixarray, const int* sequence, int size, std::vector<int> &vecIndex) {

	try {
		if(size > matrixarray.column)
			throw std::runtime_error("Sequence size is more than matrix row size");

		int *pPrefixArray = new int[size];
		
		GetSequencePrefixArray(sequence, size, pPrefixArray);

		// iterate thorugh each row
		for (int i = 0; i < matrixarray.row; i++) {

			auto sortrow = matrixarray.m_pSortMatrix[i];

			if (std::binary_search(sortrow, sortrow + matrixarray.column, sequence[0]) == false)
				continue;

			//int index = binarySearch(sortrow, matrixarray.column, sequence[0]);
			//if (index == -1)
			//	continue;

			auto row = matrixarray.m_pMatrix[i];
			
			// find sequence match count on row
			// check for single sequence match 
			//int count = LinearSearchSequenceCount(row, vecSequnce, false);
			int count = KMPSearchSequenceCount(row, matrixarray.column, sequence, size, pPrefixArray, false);

			// add row index to vector if ret is sucessful
			if (count > 0) {
				vecIndex.push_back(i + 1);
			}
		}

		if (pPrefixArray) delete[] pPrefixArray;
	}
	catch (std::exception ex) {
		std::cout << "Error: Ordered match of sequence failed due to: " << ex.what() << std::endl;
	}

	return;
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
int LinearSearchSequenceCount(const std::vector<int> &row, const std::vector<int> &sequence, bool bCount)
{
	int count = 0;

	// Iterate through row elements
	for (size_t i = 0; i < row.size(); i++) {

		// Check first element of sequence match with the row's ith element 
		if (row[i] == sequence[0]) {

			// get sub row vector
			std::vector<int> subRow(row.begin() + i, row.end());

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

std::vector<int> GetSequenePrefixVector(const std::vector<int> &vecSequence) {

	std::vector<int> vecLongestPrefix;

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

void GetSequencePrefixArray(const int *pSequence, int size, int *pPrefixArray) {
	
	// count of previous value
	int count = 0;

	// first one is always 0
	pPrefixArray[0] = 0;

	int i = 1;
	while (i < size) {

		if (pSequence[i] == pSequence[count]) {
			count++;
			pPrefixArray[i] = count;
			i++;
		}
		else {
			if (count != 0) {
				count = pPrefixArray[count - 1];
			}
			else
			{
				pPrefixArray[i] = 0;
				i++;
			}
		}
	}

	return;
}

/*
Algorithm:

*/
int KMPSearchSequenceCount(const std::vector<int> &row, const std::vector<int> &sequence, const std::vector<int> &vecSeqPrefix, bool bCount) {
;
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
			if (bCount == false)
				break;

			j = vecSeqPrefix[j - 1];
		}
		else if (i < N && sequence[j] != row[i])// mismatch after j matches
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

int KMPSearchSequenceCount(const int row[], int N, const int sequence[], int M, const int seqprefix[], bool bCount) {

	int count = 0;

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
			if (bCount == false)
				break;

			j = seqprefix[j - 1];
		}
		else if (i < N && sequence[j] != row[i])// mismatch after j matches
		{
			// Do not match vecSeqPrefix[0..vecSeqPrefix[j-1]] integers,
			// they will match anyway
			if (j != 0)
				j = seqprefix[j - 1];
			else
				i = i + 1;
		}
	}

	return count;
}

// return true value found in vector
bool InterpolationSearchValue(const std::vector<int> &row, int x) {
	int lo = 0, hi = (int)row.size()-1;

	// Since vector is sorted, an element present
	// in array must be in range defined by corner
	while (lo <= hi && x >= row[lo] && x <= row[hi])
	{
		// Probing the position with keeping
		// uniform distribution in mind.
		int pos = lo + (int)(((double)(hi - lo) /
			(row[hi] - row[lo]))*(x - row[lo]));

		// Condition of target found
		if (row[pos] == x)
			return true;

		// If x is larger, x is in upper part
		if (row[pos] < x)
			lo = pos + 1;

		// If x is smaller, x is in the lower part
		else
			hi = pos - 1;
	}
	return false;
}

int InterpolationSearchValue(const int row[], int size, int x) {

	int lo = 0, hi = size - 1;

	// Since vector is sorted, an element present
	// in array must be in range defined by corner
	while (lo <= hi && x >= row[lo] && x <= row[hi])
	{
		// Probing the position with keeping
		// uniform distribution in mind.
		int pos = lo + (int)(((double)(hi - lo) /
			(row[hi] - row[lo]))*(x - row[lo]));

		if (pos >= size)
			break;

		// Condition of target found
		if (row[pos] == x)
			return pos;

		// If x is larger, x is in upper part
		if (row[pos] < x)
			lo = pos + 1;

		// If x is smaller, x is in the lower part
		else
			hi = pos - 1;
	}
	return -1;
}

// A iterative binary search function. It returns 
// location of x in given array arr[l..r] is present, 
// otherwise -1
int binarySearch(int arr[], int size, int x)
{
	int l = 0;
	int r = size - 1;

	while (l <= r)
	{
		int m = l + (r - l) / 2;

		if (m >= size)
			break;

		// Check if x is present at mid
		if (arr[m] == x)
			return m;

		// If x greater, ignore left half
		if (arr[m] < x)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	// We reach here when element is not 
	// present in array
	return -1;
}

void BinarySearchMatrixMap(const MatrixMap matrixmap[], int size, int value, std::vector<MatrixMap> &outMatrixMap) {

	int l = 0;
	int r = size - 1;

	int mapindex = -1;

	while (l <= r)
	{
		int m = l + (r - l) / 2;

		if (m >= size)
			break;

		// Check if x is present at mid
		if (matrixmap[m].matrixvalue == value) {
			mapindex = m;
			break;
		}

		// If x greater, ignore left half
		if (matrixmap[m].matrixvalue < value)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	if (mapindex == -1)
		return;

	//TODO

	return;
}