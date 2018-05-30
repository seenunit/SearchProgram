#include "BestMatchSearch.h"
#include <algorithm>



BestMatchSearch::BestMatchSearch()
{
}


BestMatchSearch::~BestMatchSearch()
{
}

std::vector<int> BestMatchSearch::SearchSequence(const MatrixDataType &matrix, const std::vector<int> &sequence)
{
    std::vector<int> vecIndex{};
	try {

		std::vector<int> vecMatchCount;

		std::vector<int> vecPrefix = GetSequenePrefixVector(sequence);

		// iterate thorugh each row
		for (auto row : matrix) {

			if (sequence.size() > row.size())
				continue;

			// find sequence match count on row
			//int count = LinearSearchSequenceCount(row, vecSequnce, true);
			int count = KMPSearchSequenceCount(row, sequence, vecPrefix, true);

			// push match count to vector
			vecMatchCount.push_back(count);
		}

		// get iterator of max match count in vector
		auto result = max_element(vecMatchCount.begin(), vecMatchCount.end());
				
		// check the max element value greater than 0
		if (*result > 0) {

			int rowIndex = distance(vecMatchCount.begin(), result) + 1;

			vecIndex.push_back(rowIndex);
		}
	}
	catch (std::exception ex) {
		std::cout << "Error: Best match of sequence failed due to: " << ex.what() << std::endl;
	}

    return vecIndex;
}