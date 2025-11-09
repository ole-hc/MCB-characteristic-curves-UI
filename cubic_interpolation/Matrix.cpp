#pragma once
#include "libs.h"
#include "Matrix.h"

// values is addressed values[line][column] in contrast to normal (column x lines) matrix addressing 
Matrix::Matrix(int _columns, int _lines, vector<vector<float>> &_values)
    :columns(_columns), lines(_lines), values(_values)
{
}

// creates identity matrix 
Matrix::Matrix(int _columns, int _lines)
{
    columns = _columns;
    lines = _lines;
    vector<vector<float>> _values;
    for (size_t line = 0; line < lines; line++)
    {
        vector<float> _valuesLine;
        for (size_t zeroBegin = 0; zeroBegin < line; zeroBegin++)
        {
            _valuesLine.push_back(0.0f);
        }
        _valuesLine.push_back(1.0f);
        for (size_t zeroEnd = (line + 1); zeroEnd < columns; zeroEnd++)
        {
            _valuesLine.push_back(0.0f);
        }
        _values.push_back(_valuesLine);
    }
    values = _values;
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

void Matrix::switchLines(int lineA, int lineB)
{
    // decrement to match 1..n matrix addressing to 0..n-1 vector addressing
    lineA--;
    lineB--;

    vector<float> saveLine = values[lineA];
    values[lineA] = values[lineB];
    values[lineB] = saveLine;
}

int Matrix::findLineBiggestAbsoluteValue(int column, int startLine)
{
    // decrement to match 1..n matrix addressing to 0..n-1 vector addressing
    column--;
    startLine--;

    int biggestAbsoluteValueIndex = startLine;
    for (size_t line = startLine; line < lines; line++)
    {
        if(fabs(values[line][column]) > fabs(values[biggestAbsoluteValueIndex][column]))
            biggestAbsoluteValueIndex = line;
    }
    
    // increment to match 1..n matrix addressing to 0..n-1 vector addressing
    return (biggestAbsoluteValueIndex + 1);
}

// returns the coefficient with witch line A must be multiplied for a B - A substraction to equate to zero
float Matrix::findCoefficientForLineBminusXA(int column, int lineB, int lineA)
{
    // decrement to match 1..n matrix addressing to 0..n-1 vector addressing
    lineA--;
    lineB--;
    column--;
    return (values[lineB][column] / values[lineA][column]);
}


// lineA = lineA - (c * lineB)
void Matrix::subtractTwoLinesWithCoefficient(int lineA, int lineB, float coefficient)
{
    for (size_t column = 0; column < columns; column++)
    {
        values[lineA][column] = (values[lineA][column] - (coefficient *  values[lineB][column]));
    }
}

// return = self * factor
Matrix Matrix::multiplyMatrix(Matrix &factor)
{
    if (this->columns != factor.getLines())
    {
        cout << "Error while multiplying matrixes: lines and columns do not match!" << endl;
        return factor;
    }
    vector<vector<float>> productValues;
    for (size_t line = 0; line < lines; line++)
    {
        vector<float> productValuesLines;
        for (size_t column = 0; column < factor.getColumns(); column++)
        {
            float specificValue = 0.0;
            for (size_t value = 0; value < columns; value++)
            {
                cout << this->getSpecificValue(line, value) << " * " << factor.getSpecificValue(value, column) << " + ";
                specificValue += this->getSpecificValue(line, value) * factor.getSpecificValue(value, column);
            }
            productValuesLines.push_back(specificValue);
            cout << endl;
        }
        productValues.push_back(productValuesLines);
    }
    Matrix product = Matrix(factor.getColumns(), this->lines, productValues);
    cout << "PRODUCT: \n";
    product.printMatrix();
    cout << endl;
    return product;
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

float Matrix::getSpecificValue(int _line, int _column)
{
    return this->values[_line][_column];
}

void Matrix::setSpecificValue(int _line, int _column, float _value)
{
    this->values[_line][_column] = _value;
}
