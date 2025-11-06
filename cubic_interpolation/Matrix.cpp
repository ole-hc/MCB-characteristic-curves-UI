#pragma once
#include "libs.h"
#include "Matrix.h"

// values is addressed values[line][column] in contrast to normal (column x lines) matrix addressing 
Matrix::Matrix(int _columns, int _lines, vector<vector<float>> &_values)
    :columns(_columns), lines(_lines), values(_values)
{
}

Matrix::Matrix(const Matrix &_matrix)
{
    columns = _matrix.columns;
    lines = _matrix.lines;
    values = _matrix.values;
}

Matrix::~Matrix()
{
}

void Matrix::printMatrix()
{
    for (size_t line = 0; line < lines; line++)
    {
        cout << "|\t";
        for (size_t column = 0; column < columns; column++)
        {
            cout << values[line][column] << "\t|\t"; 
        }
        cout << "\n";
    }
}

// calculates the determinant for a quadratic (m x m) matrix 
float Matrix::determinant()
{
    float determinant = 0.0f;
    float product = 1.0f;

    for (size_t n = 0; n < columns; n++)
    {
        for (size_t column = n; column < (n + columns); column++)
        {
            size_t deltaColumn = column;
            if(deltaColumn > (columns - 1)) {
                deltaColumn = column - columns;
            }
            product = product * values[(column - n)][deltaColumn];
        }
        determinant += product;
        product = 1.0f;
    } 

    for (size_t n = 0; n < columns; n++)
    {
        for (size_t column = n; column < (n + columns); column++)
        {
            size_t deltaColumn = column;
            if(deltaColumn > (columns - 1)) {
                deltaColumn = column - columns;
            }

            product = product * values[((columns - 1) - (column - n))][deltaColumn];
        }
        determinant -= product;
        product = 1.0f;
    } 

    return determinant;
}

int Matrix::getLines()
{
    return this->lines;
}

int Matrix::getColumns()
{
    return this->columns;
}

vector<vector<float>>& Matrix::getValues()
{
    return this->values;
}

float Matrix::getSpecificValue(int _column, int _line)
{
    return this->values[_column][_line];
}

void Matrix::setSpecificValue(int _column, int _line, float _value)
{
    this->values[_column][_line] = _value;
}
