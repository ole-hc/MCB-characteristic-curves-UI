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
    void divideMatrix(const Matrix& divident, const Matrix& devisor); 
};