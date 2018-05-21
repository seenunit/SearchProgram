#include "OrderedSearch.h"



OrderedSearch::OrderedSearch()
{
}


OrderedSearch::~OrderedSearch()
{
}

void OrderedSearch::SearchSequence(MatrixDataType matrix, vector<int> vecSequnce)
{
    cout << "Ordered Search of Sequence rows: ";

	vector<int> vecOutPut;

	for (int index = 0; index < matrix.size(); index++) {

		auto row = matrix[index];

		for (int i = 0; i < row.size(); i++) {

			if (row[i] == vecSequnce[0]) {

				// get sub row vector
				vector<int> subRow(row.begin() + i, row.end());

				for (int j = 0; j < vecSequnce.size() && j < subRow.size(); j++) {

					if (vecSequnce[j] != subRow[j])
						break;

					if (j == vecSequnce.size() - 1)
						vecOutPut.push_back(index + 1);
				}
			}
		}
	}

	for (auto val : vecOutPut) {
		cout << val << " ";
	}

	cout << endl;


    return;
}