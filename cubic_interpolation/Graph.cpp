#pragma once
#include "libs.h"
#include "Graph.h"

Graph::Graph(vector<Point> _points, int _amountPoints)
    :points(_points), amountPoints(_amountPoints)
{
}

Graph::~Graph()
{
}

vector<Matrix> Graph::createMatrixes()
{
    int equations = amountPoints - 1;
    vector<vector<float>> a;
    vector<vector<float>> c;

    for (size_t index = 0; index < equations; index++)
    {
        
    }
    


    Matrix a = Matrix(n, n, )
    return vector<Matrix>();
}
