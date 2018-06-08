#include "BestMatchSearch.h"
#include <algorithm>

BestMatchSearch::BestMatchSearch()
{
}


BestMatchSearch::~BestMatchSearch()
{
}

void BestMatchSearch::SearchSequence(const MatrixDataType &matrix, const MatrixDataType &sortedMatrix, const std::vector<int> &sequence, std::vector<int> &vecIndex)
{
	try {

		if (sequence.size() > matrix[0].size())
			throw std::runtime_error("Sequence size is more than matrix row size");

		int max = 0;
		int maxindex = -1;

		std::vector<int> vecPrefix = GetSequenePrefixVector(sequence);

		// iterate thorugh each row
		for (size_t i = 0; i < matrix.size(); i++) {

			auto sortrow = sortedMatrix[i];

			if (std::binary_search(sortrow.begin(), sortrow.end(), sequence[0]) == false) {
			//if(InterpolationSearchValue(sortrow, sequence[0]) == false) {
				
				continue;
			}

			auto row = matrix[i];

			std::vector<int>::iterator it = std::find(row.begin(), row.end(), sequence[0]);

			std::vector<int> subrow(it, row.end());

			// find sequence match count on row
			//int count = LinearSearchSequenceCount(row, vecSequnce, true);
			int count = KMPSearchSequenceCount(subrow, sequence, vecPrefix, true);

			if (count > max) {
				max = count;
				maxindex = i + 1;
			}
		}

		// add row index to vector if ret is sucessful
		if (maxindex > 0) {
			vecIndex.push_back(maxindex);
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: Best match of sequence failed due to: " << ex.what() << std::endl;
	}

    return;
}

void BestMatchSearch::SearchSequence(const MatrixDataArray& matrixarray, const int* sequence, int size, std::vector<int> &vecIndex) {
	try {
		if (size > matrixarray.column)
			throw std::runtime_error("Sequence size is more than matrix row size");

		BinarySearchSequenceSearchforBestMatch(matrixarray, sequence, size, vecIndex);
	}
	catch (std::exception ex) {
		std::cout << "Error: Best match of sequence failed due to: " << ex.what() << std::endl;
	}

	return;
}

void BinarySearchSequenceSearchforBestMatch(const MatrixDataArray& matrixarray, const int sequence[], int seqsize, std::vector<int> &vecRowIndex) {
	
	MatrixMap *matrixmap = matrixarray.m_pMatrixMap;
	int size = matrixarray.row * matrixarray.column;

	int maxrow = -1;
	int maxj = -1;
	
	for (int i = 0; i < seqsize; i++)
	{
		int subseqsize = seqsize - i;

		if (maxj == subseqsize) {
			break;
		}

		int mapindex = -1;
		int l = 0;
		int r = size - 1;

		while (l <= r)
		{
			int m = l + (r - l) / 2;

			if (m >= size)
				break;

			// Check if x is present at mid
			if (matrixmap[m].value == sequence[i]) {
				mapindex = m;
				break;
			}

			// If x greater, ignore left half
			if (matrixmap[m].value < sequence[i])
				l = m + 1;

			// If x is smaller, ignore right half
			else
				r = m - 1;
		}

		if (mapindex == -1)
			continue;

		// go to first match
		while (mapindex > 0) {

			if (matrixmap[mapindex - 1].value == sequence[i]) {

				//if (matrixmap[mapindex].matrixrow != matrixmap[mapindex - 1].matrixrow)
				//	vecRow.push_back(matrixmap[mapindex - 1].matrixrow);
				mapindex--;
			}
			else
				break;
		}

		std::vector<int> vecRow;

		vecRow.push_back(matrixmap[mapindex].rowindex);

		// then collect row number up to last match
		while (mapindex < size - 1) {

			if (matrixmap[mapindex + 1].value == sequence[i]) {

				// find that row is already exist in vector
				auto it = std::find(vecRow.begin(), vecRow.end(), matrixmap[mapindex + 1].rowindex);

				// if not there collect it
				if (it == vecRow.end()) {

					vecRow.push_back(matrixmap[mapindex + 1].rowindex);
				}
				mapindex++;
			}
			else
				break;
		}

		// sort the row index vector
		std::sort(vecRow.begin(), vecRow.end());

		// get prefix array
		int *pPrefixArray = new int[subseqsize];

		GetSequencePrefixArray(&sequence[i], subseqsize, pPrefixArray);

		for (size_t j = 0; j < vecRow.size(); j++)
		{
			auto row = matrixarray.m_pMatrix[vecRow[j]];
						
			int matches = SearchSequencePartial(row, matrixarray.column, &sequence[i], subseqsize, pPrefixArray);

			if (matches == subseqsize) {
				maxrow = vecRow[j]; 
				maxj = subseqsize;
				break;
			}

			if (matches > maxj) {
				maxrow = vecRow[j];
				maxj = matches;
			}
		}

		if (pPrefixArray) {
			delete[] pPrefixArray; 
			pPrefixArray = nullptr;
		}

		if (maxj == subseqsize) {
			break;
		}
	}

	if(maxrow != -1 && maxj != -1)
		vecRowIndex.push_back(maxrow + 1);
	
	return;
}


int SearchSequencePartial(const int row[], int N, const int sequence[], int M, const int seqprefix[]) {

	int maxj = -1;

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
			// reached end of sequence
			return j;
		}
		else if (i < N && sequence[j] != row[i])// mismatch after j matches
		{
			// check for max sequence size match
			if (j > maxj)
				maxj = j;

			// Do not match vecSeqPrefix[0..vecSeqPrefix[j-1]] integers,
			// they will match anyway
			if (j != 0)
				j = seqprefix[j - 1];
			else
				i = i + 1;
		}
	}
	// return -1 if unordered sequence not found
	return maxj;
}