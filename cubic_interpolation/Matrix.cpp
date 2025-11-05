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
    for (size_t line = 0; line < lines; line++)
    {
        cout << "| ";
        for (size_t column = 0; column < columns; column++)
        {
            cout << values[line][column] << " | "; 
        }
        cout << "\n";
    }
}

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

// first under determinant = normal determinant but the first column switched with the solution vector
float Matrix::underDeterminant(const Matrix &_undMatrix)
{
    return 0.0f;
}
