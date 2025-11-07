#include "libs.h"
#include "Matrix.cpp"
#include "SystemOfEquations.cpp"
#include "Point.cpp"
#include "Graph.cpp"

int main(void) {
    vector<vector<float>> aValues = {
        {32.0f, 30.0f, -20.0f},
        {30.0f, 32.0f, -20.0f},
        {-20.0f, -20.0f, 60.0f}
    };
    Matrix a = Matrix(3, 3, aValues);

    vector<vector<float>> cValues = {
        {5.0f},
        {-6.0f},
        {0.0f}
    };
    Matrix c = Matrix(1, 3, cValues);

    vector<Point> dataPoints = {
        {1.0f, 2.0f},
        {3.0f, 3.0f},
        {5.0f, 9.0f},
        {8.0f, 10.0f}
    };
    Graph dataGraph = Graph(dataPoints);
    dataGraph.createMatrixes();
    cout << "\n ---------------------------- \n";

    c.printMatrix();
    cout << "\n";
    a.printMatrix();
    float det = a.determinant();
    cout << "\n---\n  determinant of a = " << det << "\n---\n";
    SystemOfEquations interpolation = SystemOfEquations(a, c);
    interpolation.printSystemOfEquations();

    return 0;
}