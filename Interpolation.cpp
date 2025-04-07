#include "Interpolation.h"
#include <vector>
#include <iostream>
#include <ceres/ceres.h>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
using namespace std;
using namespace Eigen;
using namespace ceres;

CubicSpline::CubicSpline(const vector<double>& x_vals, const vector<double>& y_vals) : x(x_vals), y(y_vals), n(x_vals.size()) {
    a = y;
    b.resize(n);
    c.resize(n);
    d.resize(n);
    computeCoefficients();
}

int CubicSpline::findSegment(double x_val) const {
    if (x_val < x[0]){
        return 0;
    }
    if (x_val > x[n-1]) {
        return n-1;
    }

    for (int i = 0; i < n - 1; i++) {
        if (x_val >= x[i] && x_val <= x[i + 1]) {
            return i;
        }
    }
    return -1; // Should never reach here
};

void CubicSpline::computeCoefficients() {
    vector<double> h(n - 1), alpha(n - 1), l(n), mu(n), z(n);

    for (int i = 0; i < n - 1; i++) {
        h[i] = x[i + 1] - x[i];
        alpha[i] = (i == 0) ? 0 : (3 / h[i] * (a[i + 1] - a[i]) - 3 / h[i - 1] * (a[i] - a[i - 1]));
    }

    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;

    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n - 1] = 1;
    z[n - 1] = 0;
    c[n - 1] = 0;

    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }
};

double CubicSpline::interpolate(double x_val) {
    int i = findSegment(x_val);
    double dx = x_val - x[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
};


