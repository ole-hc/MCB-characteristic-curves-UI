#include "libs.h"
#include "Matrix.h"

Matrix::Matrix(int _columns, int _lines, vector<vector<float>> &_values)
    :columns(_columns), lines(_lines), values(_values)
{
}

Matrix::~Matrix()
{
}

void Matrix::printMatrix()
{
    for (size_t column = 0; column < columns; column++)
    {
        cout << "| ";
        for (size_t line = 0; line < lines; line++)
        {
            cout << values[column][line] << " | "; 
        }
        cout << "\n";
    }
}

void Matrix::divideMatrix(const Matrix &divident, const Matrix &devisor)
{
    
}
