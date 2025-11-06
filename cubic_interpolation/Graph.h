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
    Graph(vector<Point> _points, int _amountPoints);
    ~Graph();
    vector<Matrix> createMatrixes();
};
