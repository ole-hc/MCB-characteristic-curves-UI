#include "libs.h"
#include "Matrix.cpp"
#include "SystemOfEquations.cpp"
#include "Point.cpp"
#include "Graph.cpp"

int main(void) {
    vector<vector<float>> aValues = {
        {4.0f, 5.0f, 2.0f},
        {3.0f, 4.0f, 1.0f},
        {3.0f, 6.0f, 3.0f}
    };
    Matrix a = Matrix(3, 3, aValues);

    vector<vector<float>> cValues = {
        {16.0f},
        {12.0f},
        {18.0f}
    };
    Matrix c = Matrix(1, 3, cValues);

    vector<Point> dataPoints = {
        {1.0f, 2.0f},
        {3.0f, 3.0f},
        {5.0f, 9.0f},
        {8.0f, 10.0f}
    };
    Graph dataGraph = Graph(dataPoints);
    vector<Matrix> soe;
    soe = dataGraph.createMatrixes();
    cout << "\n ---------------------------- \n";
     
    SystemOfEquations interpolation = SystemOfEquations(soe.at(0), soe.at(1));
    interpolation.printSystemOfEquations();

    // SystemOfEquations interpolation = SystemOfEquations(a, c);
    // interpolation.printSystemOfEquations();

    return 0;
}