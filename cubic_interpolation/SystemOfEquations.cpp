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
// uses LR decomposition with pivoting
// p * a * b = p * c
// a = l * r
// ---
// p * l * y = p * c
// returns empty (2 x 2) Matrix on mainDeterminant = 0 --> not solvable or infinite solutions 
Matrix SystemOfEquations::solveSystemOfEquations()
{
    Matrix p = Matrix(a.getColumns(), a.getLines());
    Matrix l = Matrix(a.getColumns(), a.getLines());

    for (size_t workingLine = 0; workingLine < a.getLines(); workingLine++)
    {
        // find pivot and switch lines accordingly in matrix a and p 
        int indexBiggestAbsolute = a.findLineBiggestAbsoluteValue((workingLine + 1), (workingLine + 1));
        a.switchLines((workingLine + 1), indexBiggestAbsolute);
        p.switchLines((workingLine + 1), indexBiggestAbsolute);

        for (size_t line = (workingLine + 1); line < a.getLines(); line++)
        {
            float coefficient = a.findCoefficientForLineBminusXA((workingLine + 1), (line + 1), (workingLine + 1));
            a.subtractTwoLinesWithCoefficient(line, workingLine, coefficient);
            l.setSpecificValue(line, workingLine, coefficient);
        }
        cout << "R: " << endl;
        a.printMatrix();
        cout << "P: " << endl;
        p.printMatrix();
        cout << "L: " << endl;
        l.printMatrix();
        cout << endl;
    }

    a = l;
    p = p.multiplyMatrix(c);
    Matrix solution = solveLowerTriangularMatrix(l, p);
    return solution;
}

// solves triangular matrix l = p and return solution vector
// example:
// ( 1 0 0 )       ( p1 )       ( 2 )
// ( 2 1 0 )   *   ( p2 )   =   ( 4 )
// ( 7 3 1 )       ( p3 )       ( 1 )
Matrix SystemOfEquations::solveLowerTriangularMatrix(Matrix l, Matrix p)
{
    vector<vector<float>> solutionValues;
    for (size_t line = 0; line < l.getLines(); line++)
    {
        float lineSolution = 0.0;
        for (size_t column = 0; column < line; column++)
        {
            lineSolution += (l.getSpecificValue(line, column) * solutionValues[column][0]);
        }
        lineSolution = p.getSpecificValue(line, 0) - lineSolution;
        solutionValues.push_back({lineSolution});
    }
    Matrix solution = Matrix(p.getColumns(), l.getLines(), solutionValues);
    return solution;
}

// solves system of equations in a x b = c form with a beeing a (m x m) Matrix and b, c beeing (m x 1) vectors
// returns empty (2 x 2) Matrix on mainDeterminant = 0 --> not solvable or infinite solutions 
Matrix SystemOfEquations::solveSystemOfEquationsCramersRule()
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
