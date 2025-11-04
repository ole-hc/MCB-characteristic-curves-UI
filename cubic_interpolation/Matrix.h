#pragma once
#include "libs.h"

class Matrix
{
private:
    int columns;
    int lines;
    vector<vector<float>> values;

public:
    Matrix(int _m, int _n, vector<vector<float>>& _values);
    ~Matrix();
    void printMatrix();
    float determinant();
    float underDeterminant(const Matrix& _undMatrix); 
};