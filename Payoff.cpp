#include "Payoff.h"
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;


double CallOption::payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double riskfree_rate) {
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
        sum += payoff;
    }
    return (sum/payoffs.size())*exp(-riskfree_rate*days/261.0);
};

double PutOption::payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double riskfree_rate) {
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
    return (sum/payoffs.size())*exp(-riskfree_rate*days/261.0);
};