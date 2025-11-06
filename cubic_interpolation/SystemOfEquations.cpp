#pragma once 
#include "SystemOfEquations.h"

SystemOfEquations::SystemOfEquations(Matrix &_a, Matrix &_c)
    :a(_a), c(_c), b(solveSystemOfEquations())
{
}

SystemOfEquations::~SystemOfEquations()
{
}

void SystemOfEquations::printSystemOfEquations()
{
    a.printMatrix();
    cout << "\n * \n\n";
    b.printMatrix();
    cout << "\n = \n\n";
    c.printMatrix();
}

// first under determinant = normal determinant but the first column switched with the solution vector (m x 1)
float SystemOfEquations::underDeterminant(int columnNr)
{ 
    a.printMatrix();
    c.printMatrix();
    columnNr--;
    Matrix switchedColumns = Matrix(a.getColumns(), a.getLines(), a.getValues());
    for (size_t line = 0; line < a.getLines(); line++)
    {
        switchedColumns.setSpecificValue(line, columnNr, c.getSpecificValue(line, 0)); 
    }

    float determinant = switchedColumns.determinant();
    return determinant;
}

// solves system of equations in a x b = c form with a beeing a (m x m) Matrix and b, c beeing (m x 1) vectors
// called on Matrix a
// returns empty (2 x 2) Matrix on mainDeterminant = 0 --> not solvable or infinite solutions 
Matrix SystemOfEquations::solveSystemOfEquations()
{
    float mainDeterminant = a.determinant();
    if(mainDeterminant == 0) {
        vector<vector<float>> errorValues = {
            {0, 0},
            {0, 0}
        };
        Matrix error = Matrix(2, 2, errorValues);
        return error;
    }

    vector<vector<float>> bValues;
    for (size_t line = 0; line < a.getLines(); line++)
    {
        float lineSolution = (underDeterminant(line + 1)/mainDeterminant);
        bValues.push_back({lineSolution});
    }
    Matrix b = Matrix(1, c.getLines(), bValues);

    return b;
}
