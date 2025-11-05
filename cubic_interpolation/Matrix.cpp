#include "libs.h"
#include "Matrix.h"

// values is addressed values[line][column] in contrast to normal (column x lines) matrix addressing 
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

// first under determinant = normal determinant but the first column switched with the solution vector (m x 1)
float Matrix::underDeterminant(const Matrix &_undMatrix, int columnNr)
{ 
    columnNr--;
    Matrix copy = Matrix(this->columns, this-> lines, this->values);
    for (size_t line = 0; line < lines; line++)
    {
        copy.values[line][columnNr] = _undMatrix.values[line][0];
    }

    float determinant = copy.determinant();
    return determinant;
}