#pragma once
#include "libs.h"
#include "Point.h"
#include "Matrix.h"

class Graph
{
private:
    vector<Point> points;
    int amountPoints;
public:
    Graph(vector<Point> _points);
    ~Graph();
    vector<Matrix> createMatrixes();
    void evaluationAtKnownDataPoints(vector<vector<float>>& _a, vector<vector<float>>& _c);
    void evaluationFirstDerivativeAtDataPoints(vector<vector<float>>& _a, vector<vector<float>>& _c);
    void evaluationSecondDerivativeAtDataPoints(vector<vector<float>>& _a, vector<vector<float>>& _c);
    void evaluationEndPointsAssumption(vector<vector<float>>& _a, vector<vector<float>>& _c);
    vector<float> addSplineEquationToMatrixColumnOneEquation(int _indexSpline, vector<float> _coefficient);
    vector<float> addSplineEquationToMatrixColumnTwoEquations(int _indexSpline,  int _indexSplineTwo, vector<float> _coefficient);
};
