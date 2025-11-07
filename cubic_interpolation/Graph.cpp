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

    cout<< "Here it is: \n";
    Matrix aSolution = Matrix(columns, columns, a);
    aSolution.printMatrix();
    cout << " C: \n";
    Matrix cSolution = Matrix(1, columns, c);
    cSolution.printMatrix();
    return vector<Matrix>();
}

// adds first 2n coefficient matrix lines to values vector of a and solutions to values of vector c 
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

        vector<float> aRow = addSplineEquationToMatrixColumn(indexSpline, coefficients);
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

        vector<float> aRow = addSplineEquationToMatrixColumn(indexSpline, coefficients);
        _a.push_back(aRow);
        _c.push_back({yI});
    }
}

void Graph::evaluationFirstDerivativeAtDataPoints(vector<vector<float>> &_a, vector<vector<float>> &_c)
{
}

void Graph::evaluationSecondDerivativeAtDataPoints(vector<vector<float>> &_a, vector<vector<float>> &_c)
{
}

void Graph::evaluationEndPointsAssumption(vector<vector<float>> &_a, vector<vector<float>> &_c)
{
}

// inserts coefficients into matrix at the specified point and fills the line up with zeroes
vector<float> Graph::addSplineEquationToMatrixColumn(int _indexSpline, vector<float> _coefficients)
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