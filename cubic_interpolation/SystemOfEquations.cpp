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
    Matrix r = a;

    for (size_t workingLine = 0; workingLine < r.getLines(); workingLine++)
    {
        // find pivot and switch lines accordingly in matrix a and p 
        int indexBiggestAbsolute = r.findLineBiggestAbsoluteValue((workingLine + 1), (workingLine + 1));
        cout << "Switch line: " << (workingLine + 1) << " with line: " << indexBiggestAbsolute << "\n";
        r.switchLines((workingLine + 1), indexBiggestAbsolute);
        p.switchLines((workingLine + 1), indexBiggestAbsolute);
        swapLRowsForPivot(l, workingLine, workingLine, (indexBiggestAbsolute - 1));

        for (size_t line = (workingLine + 1); line < r.getLines(); line++)
        {
            float coefficient = r.findCoefficientForLineBminusXA((workingLine + 1), (line + 1), (workingLine + 1));
            r.subtractTwoLinesWithCoefficient(line, workingLine, coefficient);
            l.setSpecificValue(line, workingLine, coefficient);
        }
        cout << "R: " << endl;
        r.printMatrix();
        cout << "P: " << endl;
        p.printMatrix();
        cout << "L: " << endl;
        l.printMatrix();
        cout << endl;
    }

    Matrix pc = p.multiplyMatrix(c);
    Matrix y = solveLowerTriangularMatrix(l, pc);
    y.printMatrix();
    Matrix x = solveUpperTriangularMatrix(r, y);
    return x;
}

// solves triangular matrix l * y = pc and return solution vector
// example:
// !Only with 1 diagonal
// ( 1 0 0 )       ( y1 )       ( 2 )
// ( 2 1 0 )   *   ( y2 )   =   ( 4 )
// ( 7 3 1 )       ( y3 )       ( 1 )
Matrix SystemOfEquations::solveLowerTriangularMatrix(Matrix l, Matrix pc)
{
    vector<vector<float>> solutionValues;
    for (size_t line = 0; line < l.getLines(); line++)
    {
        float lineSolution = 0.0;
        for (size_t column = 0; column < line; column++)
        {
            lineSolution += (l.getSpecificValue(line, column) * solutionValues[column][0]);
        }
        lineSolution = pc.getSpecificValue(line, 0) - lineSolution;
        solutionValues.push_back({lineSolution});
    }
    Matrix solution = Matrix(pc.getColumns(), l.getLines(), solutionValues);
    return solution;
}

// r * x = y
// example:
// ( 5 2 7 )       ( y1 )       ( 2 )
// ( 0 2 3 )   *   ( y2 )   =   ( 4 )
// ( 0 0 3 )       ( y3 )       ( 1 )
Matrix SystemOfEquations::solveUpperTriangularMatrix(Matrix r, Matrix y)
{
    vector<vector<float>> solutionValues;
    for (int line = (r.getLines() - 1); line >= 0; --line)
    {
        float lineSolution = 0.0;
        for (size_t column = (r.getColumns() - 1); column > line; column--)
        {
            int actual = ((solutionValues.size() - 1) - (r.getColumns() - 1 - column));
            lineSolution += (r.getSpecificValue(line, column) * solutionValues[((solutionValues.size() - 1) - (r.getColumns() -1 - column))][0]);
        }
        lineSolution = y.getSpecificValue(line, 0) - lineSolution;
        lineSolution = lineSolution / r.getSpecificValue(line, line);
        solutionValues.insert(solutionValues.begin(),{lineSolution});
    }
    Matrix solution = Matrix(y.getColumns(), r.getLines(), solutionValues);
    return solution;
}

// Swap values of two lines until specified column (column = pivotLine)
void SystemOfEquations::swapLRowsForPivot(Matrix &l, size_t pivotLine, size_t lineA, size_t lineB)
{    
    if(lineA == lineB) return;

    for (size_t column = 0; column < pivotLine; column++)
    {
        float temp = l.getSpecificValue(lineB, column);
        l.setSpecificValue(lineB, column, l.getSpecificValue(lineA, column));
        l.setSpecificValue(lineA, column, temp);
    }
    cout << "switched in l: " << lineA << " with: " << lineB << "\n";
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
