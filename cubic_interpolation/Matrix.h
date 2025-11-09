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
    Matrix(int _columns, int _lines);
    Matrix(const Matrix& _matrix);
    ~Matrix();
    void printMatrix();
    float determinant();
    void switchLines(int lineA, int lineB);
    int findLineBiggestAbsoluteValue(int column, int startLine);
    float findCoefficientForLineBminusXA(int column, int lineB, int lineA);
    void subtractTwoLinesWithCoefficient(int lineA, int lineB, float coefficient);
    Matrix multiplyMatrix(Matrix& factor);
    int getLines();
    int getColumns();
    vector<vector<float>>& getValues();
    float getSpecificValue(int _column, int _line);
    void setSpecificValue(int _column, int _line, float _value);
};