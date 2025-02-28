#include "Payoff.h"
#include <algorithm>

double CallOption::payoff_calc(vector<vector<double>> stock_paths, double strike) {
    if (stock_paths.empty()) {
        return 0.0;
    }
    vector<double> payoffs;
    double sum = 0.0;
    for(vector<double> path : stock_paths) {
        double last_price = path.back();
        payoffs.push_back(max(last_price-strike,0.0));
    }
    for (double payoff : payoffs) {
        sum += payoff/payoffs.size();
    }
    return sum;
};

double PutOption::payoff_calc(vector<vector<double>> stock_paths, double strike) {
    if (stock_paths.empty()) {
        return 0.0;
    }
    vector<double> payoffs;
    double sum = 0.0;
    for(vector<double> path : stock_paths) {
        double last_price = path.back();
        payoffs.push_back(max(strike-last_price,0.0));
    }
    for (double payoff : payoffs) {
        sum += payoff;
    }
    sum = sum/payoffs.size();
    return sum;
};