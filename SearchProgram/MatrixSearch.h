#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<int>> MatrixDataType;

class MatrixSearch
{
public:
    virtual void SearchSequence(MatrixDataType, vector<int>) = 0;
};

