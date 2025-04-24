#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include <vector>
using namespace std;

class Interpolation{
private:
    vector<double> x, y, a, b, c, d; // Vectors to store x and y data points, and spline coefficients a, b, c, d
    int n; // Number of data points

    // Finds the index of the interval [x_i, x_{i+1}] that contains x_val
    int findSegment(double x_val) const;

public:
    // Constructor: initializes the class with given x and y values and computes coefficients
    Interpolation(const vector<double>& x_vals, const vector<double>& y_vals);

    // Computes the spline coefficients b, c, and d for cubic interpolation
    void computeCoefficients();

    // Interpolates the value at a given x_val using the cubic spline
    double interpolate(double x_val);
};

#endif //INTERPOLATION_H
