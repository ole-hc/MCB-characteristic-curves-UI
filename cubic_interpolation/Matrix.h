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
    Matrix(const Matrix& _matrix);
    ~Matrix();
    void printMatrix();
    float determinant();
    int getLines();
    int getColumns();
    vector<vector<float>>& getValues();
    float getSpecificValue(int _column, int _line);
    void setSpecificValue(int _column, int _line, float _value);
};