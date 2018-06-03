#include "UnOrderedSearch.h"
#include <algorithm>
#include <map>

//int compare(const void * a, const void * b)
//{
//	return (*(int*)a - *(int*)b);
//}

UnOrderedSearch::UnOrderedSearch()
{
}


UnOrderedSearch::~UnOrderedSearch()
{
}


void UnOrderedSearch::SearchSequence(const MatrixDataType &matrix, const MatrixDataType &sortedMatrix, const std::vector<int> &sequence, std::vector<int> &vecIndex)
{

	try {
		if (sequence.size() > matrix[0].size())
			throw std::runtime_error("Sequence size is more than matrix row size");

        std::vector<int> sortedSequence = sequence;

        // sort the sequence
        sort(sortedSequence.begin(), sortedSequence.end());

        // search the sequence elements in each row
		for (size_t i = 0; i < sortedMatrix.size(); i++) {

			auto row = sortedMatrix[i];

			//if (std::binary_search(row.begin(), row.end(), sequence[0]) == false) {
			if (InterpolationSearchValue(row, sequence[0]) == false) {
				continue;
			}

			std::vector<int>::iterator it = std::find(row.begin(), row.end(), sortedSequence[0]);

			std::vector<int> subrow(it, row.end());

			// returns 1 of unordered sequence is found
			int ret = UnorderedSearchSortedSequence(subrow, sortedSequence);

			// add row index to vector if ret is sucessful
            if (ret == 1) {
                vecIndex.push_back(i + 1);
            }
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: UnOrdered match of sequence failed due to: " << ex.what() << std::endl;
	}
	

    return;
}

void UnOrderedSearch::SearchSequence(const MatrixDataArray& matrixarray, const int* sequence, int size, std::vector<int> &vecIndex) {
	try {
		if (size > matrixarray.column)
			throw std::runtime_error("Sequence size is more than matrix row size");

		int *sortsequence = new int[size];
		for (int i = 0; i < size; i++)
		{
			sortsequence[i] = sequence[i];
		}

		// get sorted sequence
		std::qsort(sortsequence, size, sizeof(int), compare);

		// iterate thorugh each row
		for (int i = 0; i < matrixarray.row; i++) {

			auto sortrow = matrixarray.m_pSortMatrix[i];

			int index = InterpolationSearchValue(sortrow, matrixarray.column, sortsequence[0]);
			if (index == -1)
				continue;

			// find sequence match count on row
			// check for single sequence match 
			//int count = LinearSearchSequenceCount(row, vecSequnce, false);
			int ret = UnorderedSearchSortedSequence(sortrow, matrixarray.column, sortsequence, size);

			// add row index to vector if ret is sucessful
			if (ret == 1) {
				vecIndex.push_back(i + 1);
			}
		}

		if (sortsequence) delete[] sortsequence;
	}
	catch (std::exception ex) {
		std::cout << "Error: UnOrdered match of sequence failed due to: " << ex.what() << std::endl;
	}

	return;
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

void InsertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
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

int UnorderedSearchSortedSequence(const int row[], int N, const int sequence[], int M) {

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