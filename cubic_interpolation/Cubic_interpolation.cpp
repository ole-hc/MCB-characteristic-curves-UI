#include "libs.h"
#include "Matrix.cpp"

int main(void) {
    vector<vector<float>> aValues = {
        {1.0f, 2.0f, 3.0f},
        {4.0f, 5.0f, 6.0f},
        {7.0f, 8.0f, 9.0f}
    };
    Matrix a = Matrix(3, 3, aValues);

    vector<vector<float>> cValues = {
        {1.0f},
        {2.0f},
        {3.0f}
    };
    Matrix c = Matrix(3, 1, cValues);

    c.printMatrix();
    cout << "\n";
    a.printMatrix();


    return 0;
}