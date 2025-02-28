#include <iostream>
#include <vector>
#include "MonteCarlo.h"
#include "Payoff.h"

using namespace std;
using std::vector;

int main() {

    double price = 100;
    double mu = 0.05;
    double sigma = 0.2;
    int days = 252;
    double dt = 1.0/252.0;


    MonteCarlo monteCarlo;
    vector<vector<double>> stock_paths;
    for (int i = 0; i < 100000; i++) {
        vector<double> path = monteCarlo.simulated_stock_prices(price,mu,sigma,days,dt);
        stock_paths.push_back(path);
    }


    CallOption call_option(120);

    double expected_payoff = call_option.payoff_calc(stock_paths,call_option.strike);
    cout << "Expected: " << expected_payoff << endl;

}
