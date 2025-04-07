//
// Created by Alexander on 21.03.2025.
//

#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include <vector>
using namespace std;

class Interpolation {
public:
    virtual double interpolate(double x_val) = 0;
    virtual ~Interpolation(){};
};

class CubicSpline : public Interpolation {
private:
    vector<double> x, y, a, b, c, d;
    int n;
    int findSegment(double x_val) const;

public:
    CubicSpline(const vector<double>& x_vals, const vector<double>& y_vals);

    void computeCoefficients();
    double interpolate(double x_val) override;

};








#endif //INTERPOLATION_H
