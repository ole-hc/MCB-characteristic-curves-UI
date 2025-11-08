#pragma once
#include "libs.h"
#include "Matrix.cpp"

// builds a system of equations in the form
// a * b = c , with:
// a = (m x m) matrix
// b = (1 x m) variable vector <- actual solution of SOE after algorithm 
// c = (1 x m) solution vector 
class SystemOfEquations
{
private:
    Matrix a;
    Matrix c;
    Matrix b;
public:
    SystemOfEquations(Matrix& _a, Matrix& _c);
    ~SystemOfEquations();
    void printSystemOfEquations();
    float underDeterminant(int columnNr); 
    Matrix solveSystemOfEquations();
    Matrix solveSystemOfEquationsCramersRule();
};