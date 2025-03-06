#include "MonteCarlo.h"

#include <iostream>
#include <ostream>

using namespace std;
using std::vector;

normal_distribution<double> distribution (0.0, 1.0);
random_device rd;
mt19937 gen(rd());

vector<double> MonteCarlo::simulated_stock_prices(double price, double mu, double sigma, int days, double dt) {
    vector<double> prices;
    prices.push_back(price);
    double Si = price;;
    for (int i = 1; i < days; i++) {
        //cout << "Si = " << Si << endl;
        double Z = distribution(gen);
        Si = Si * exp((mu - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z);
        prices.push_back(Si);
    }
    return prices;
};