#include "MonteCarlo.h"

#include <iostream>
#include <ostream>

using namespace std;
using std::vector;

//random number generation
normal_distribution<double> distribution (0.0, 1.0);
random_device rd;
mt19937 gen(rd());

vector<double> MonteCarlo::simulated_stock_prices(double price, double mu, double sigma, int days, double dt) {
    vector<double> prices; //vector with a stock price for each day
    prices.push_back(price); // inputs last real observed price
    double Si = price;;
    for (int i = 1; i <= days; i++) {
        double Z = distribution(gen);
        Si = Si * exp((mu - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z); //GBM for generating next days price
        prices.push_back(Si);
    }
    return prices;
};