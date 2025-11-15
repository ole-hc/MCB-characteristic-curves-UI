#pragma once
#include "libs.h"
#include "Graph.h"

Graph::Graph(vector<Point> _points)
    :points(_points), amountPoints(_points.size())
{
}

Graph::~Graph()
{
}

vector<Matrix> Graph::createMatrixes()
{
    int equations = amountPoints - 1; 
    int columns = equations * 4; // 4 = variables in ax^3 + bx^2 + cx + d
    vector<vector<float>> a;
    vector<vector<float>> c;

    evaluationAtKnownDataPoints(a, c);
    evaluationFirstDerivativeAtDataPoints(a, c);
    evaluationSecondDerivativeAtDataPoints(a, c);
    evaluationEndPointsAssumption(a, c);

    cout<< "Here it is: \n";
    Matrix aSolution = Matrix(columns, columns, a);
    aSolution.printMatrix();
    cout << " C: \n";
    Matrix cSolution = Matrix(1, columns, c);
    cSolution.printMatrix();

    vector<Matrix> soe;
    soe.push_back(aSolution);
    soe.push_back(cSolution);
    return soe;
}

// adds first 2n coefficient matrix lines to values vector of a and solutions to values of vector c 
// Pn(x) = Pn + 1(x)
// ax^3 + bx^2 + cx + d 
void Graph::evaluationAtKnownDataPoints(vector<vector<float>>& _a, vector<vector<float>>& _c)
{
    for (size_t indexSpline = 0; indexSpline < (points.size() - 1); indexSpline++)
    {
        float xI = points.at(indexSpline).getX();
        float yI = points.at(indexSpline).getY();
        vector<float> coefficients;

        coefficients.push_back(pow(xI, 3.0));
        coefficients.push_back(pow(xI, 2.0));
        coefficients.push_back(xI);
        coefficients.push_back(1);

        vector<float> aRow = addSplineEquationToMatrixColumnOneEquation(indexSpline, coefficients);
        _a.push_back(aRow);
        _c.push_back({yI});
    }

    for (size_t indexSpline = 0; indexSpline < (points.size() - 1); indexSpline++)
    {
        float xI = points.at(indexSpline + 1).getX();
        float yI = points.at(indexSpline + 1).getY();
        vector<float> coefficients;

        coefficients.push_back(pow(xI, 3.0));
        coefficients.push_back(pow(xI, 2.0));
        coefficients.push_back(xI);
        coefficients.push_back(1);

        vector<float> aRow = addSplineEquationToMatrixColumnOneEquation(indexSpline, coefficients);
        _a.push_back(aRow);
        _c.push_back({yI});
    }
}

// adds next (n - 1) equations
// P'n(x (n + 1)) = P'(x (n + 1))
// 3a(n)x^2 + 2b(n)x + c(n) - 3a(n + 1)x^2 - 2b(n + 1)x - c(n + 1) = 0
void Graph::evaluationFirstDerivativeAtDataPoints(vector<vector<float>> &_a, vector<vector<float>> &_c)
{
    for (size_t indexSpline = 0; indexSpline < (points.size() - 2); indexSpline++)
    {
        float xI = points.at(indexSpline + 1).getX();
        float yI = points.at(indexSpline + 1).getY();
        vector<float> coefficients;

        coefficients.push_back(3 * (pow(xI, 2.0)));
        coefficients.push_back(2 * xI);
        coefficients.push_back(1);
        coefficients.push_back(0);

        coefficients.push_back(-(3 * (pow(xI, 2.0))));
        coefficients.push_back(-(2 * xI));
        coefficients.push_back(-1);
        coefficients.push_back(0);

        vector<float> aRow = addSplineEquationToMatrixColumnTwoEquations(indexSpline, (indexSpline + 1),coefficients);
        _a.push_back(aRow);
        _c.push_back({0});
    }
}

// adds next (n - 1) equations
// P''n(x (n + 1)) = P''(x (n + 1))
// 6a(n)x + 2b(n) - 6a(n + 1)x - 2b(n + 1) = 0
void Graph::evaluationSecondDerivativeAtDataPoints(vector<vector<float>> &_a, vector<vector<float>> &_c)
{
    for (size_t indexSpline = 0; indexSpline < (points.size() - 2); indexSpline++)
    {
        float xI = points.at(indexSpline + 1).getX();
        float yI = points.at(indexSpline + 1).getY();
        vector<float> coefficients;

        coefficients.push_back(6 * xI);
        coefficients.push_back(2);
        coefficients.push_back(0);
        coefficients.push_back(0);

        coefficients.push_back(-(6 * xI));
        coefficients.push_back(-2);
        coefficients.push_back(0);
        coefficients.push_back(0);

        vector<float> aRow = addSplineEquationToMatrixColumnTwoEquations(indexSpline, (indexSpline + 1),coefficients);
        _a.push_back(aRow);
        _c.push_back({0});
    }
}

// adds last 2 equation
// assumes that we are dealing with a natural cubic spline interpolation 
// P''1(x1) = 0, P''max(xmax) = 0 
// 6a(1)x + 2b(1) = 0, 6a(max)x + 2b(max) = 0
void Graph::evaluationEndPointsAssumption(vector<vector<float>> &_a, vector<vector<float>> &_c)
{
    int remainingEquations = 2;
    for (size_t indexSpline = 0; indexSpline < remainingEquations; indexSpline++)
    {
        float xI = 0;
        float yI = 0;
        int spline = 0;
        int currentSplineIndex = 0;
        if(indexSpline == 1) {
            spline = (points.size() - 1);
            currentSplineIndex = (points.size() - 2);
        }
        xI = points.at(spline).getX();
        yI = points.at(spline).getY();
        vector<float> coefficients;

        coefficients.push_back(6 * xI);
        coefficients.push_back(2);
        coefficients.push_back(0);
        coefficients.push_back(0);

        vector<float> aRow = addSplineEquationToMatrixColumnOneEquation(currentSplineIndex, coefficients);
        _a.push_back(aRow);
        _c.push_back({0});
    }
}

// inserts coefficients into matrix at the specified point and fills the line up with zeroes
vector<float> Graph::addSplineEquationToMatrixColumnOneEquation(int _indexSpline, vector<float> _coefficients)
{
    vector<float> aRow;
        for (size_t zeroBefore = 0; zeroBefore < (_indexSpline * 4); zeroBefore++)
        {
            aRow.push_back(0.0f);
        }
        aRow.push_back(_coefficients.at(0));
        aRow.push_back(_coefficients.at(1));
        aRow.push_back(_coefficients.at(2));
        aRow.push_back(_coefficients.at(3));
        for (size_t zeroAfter = ((_indexSpline + 1) * 4); zeroAfter < ((amountPoints - 1) * 4); zeroAfter++)
        {
            aRow.push_back(0.0f);
        }
        return aRow;
}

vector<float> Graph::addSplineEquationToMatrixColumnTwoEquations(int _indexSplineOne, int _indexSplineTwo, vector<float> _coefficients)
{
    vector<float> aRow;
    for (size_t zeroBefore = 0; zeroBefore < (_indexSplineOne * 4); zeroBefore++)
    {
        aRow.push_back(0.0f);
    }

    aRow.push_back(_coefficients.at(0));
    aRow.push_back(_coefficients.at(1));
    aRow.push_back(_coefficients.at(2));
    aRow.push_back(_coefficients.at(3));

    for (size_t zeroMiddle = ((_indexSplineOne + 1) * 4); zeroMiddle < (_indexSplineTwo * 4); zeroMiddle++)
    {
        aRow.push_back(0.0f);
    }

    aRow.push_back(_coefficients.at(4));
    aRow.push_back(_coefficients.at(5));
    aRow.push_back(_coefficients.at(6));
    aRow.push_back(_coefficients.at(7));


    for (size_t zeroAfter = ((_indexSplineOne + 1) * 4); zeroAfter < ((amountPoints - 1) * 4); zeroAfter++)
    {
        aRow.push_back(0.0f);
    }
    return aRow;

    return vector<float>();
}
