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

		int max = 0;
		int maxindex = -1;

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
			int count = KMPSearchSequenceCount(row, matrixarray.column, sequence, size, pPrefixArray, true);

			if (count > max) {
				max = count;
				maxindex = i + 1;
			}
		}

		// add row index to vector if ret is sucessful
		if (maxindex > -1) {
			vecIndex.push_back(maxindex);
		}

		if (pPrefixArray) delete[] pPrefixArray;
	}
	catch (std::exception ex) {
		std::cout << "Error: Best match of sequence failed due to: " << ex.what() << std::endl;
	}

	return;
}