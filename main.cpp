#include <iostream>
#include <vector>
#include <string>
#include "MonteCarlo.h"
#include "Payoff.h"
#include "Timecalc.h"
#include "API_Acc.h"
#include "Interpolation.h"

using namespace std;
using std::vector;

int main(int argc, char* argv[]) {

    if (argc != 12) {
        cerr << "Usage: " << argv[0] << " DAY MONTH YEAR WEEKDAY STRIKE STOCK_SYMBOL PUT_OR_CALL PRICE_OR_EVALUATE STOCK_API_KEY YIELD_API_KEY" << endl;
        return 1;
    }
    
    //setting expiry date of the option
    int day = stoi(argv[1]),
        month = stoi(argv[2]),
        year = stoi(argv[3]);
    int weekday = stoi(argv[4]);


    //setting strike price of the option
    double strike_price = stod(argv[5]);
    if(strike_price <= 0 ){
        cerr << "Invalid strike price";
        exit(EXIT_FAILURE);
    }

    string symbol = argv[6]; // stock symbol
    string put_or_call = argv[7];
    string price_or_evaluate = argv[8];
    int accuracy = stoi(argv[9]);
    string stock_API_key = argv[10];
    string yield_API_key = argv[11];

    // Accessing API for stock price data and treasury yield data
    API_Acc access_data;

    Timecalc timecalc;
    int days = timecalc.DaysUntilExpiration(day, month, year, weekday); // amount of workdays
    vector<double> prices = access_data.GetStockData(symbol, 3*days, stock_API_key); // gets historic price data from 3x the amount of days in relation to the expiry date
    vector<vector<double>> treasury_yield_data = access_data.GetTreasuryYieldData(yield_API_key); // gets current treasury yield data
    const vector<double>& time_values = treasury_yield_data[0]; // vector with day amounts of US treasury securities (ascending order)
    const vector<double>& rates = treasury_yield_data[1]; // // vector with rates of corresponding US treasury securities(ascending order)


    //finding volatility, drift, risk-free rate and amount of workdays for stock path generation
    double price = prices.back(); // last closing price of chosen stock
    double mu = 0.0; // drift
    double sigma = 0.0; // volatility
    double dt = 1.0/261; // timestep one day of 261 workdays in a year

    //interpolates risk free-rate between two corresponding treasury securities with close maturity dates
    Interpolation interpolate(time_values, rates);
    double risk_free_rate = interpolate.interpolate(timecalc.DaysInbetween(day, month, year))/100;

    //calculating the volatility of given stock
    double mean_return= 0.0; //average return of given stock over given time frame
    vector<double> payoffs;

    // calculates log returns between two dates and calculates mean return
    for(int i = 1; i < prices.size(); i++) {
        double log_return = log(prices[i]/prices[i-1]);
        payoffs.push_back(log_return);
        mean_return += log_return;
    }
    mean_return = mean_return/payoffs.size();
    double s2 = 0.0;
    //calculates Variance of log returns
    for (double r: payoffs) {
        s2 += pow(r-mean_return,2.0);
    }
    s2 /= payoffs.size()-1;

    if(price_or_evaluate == "price"){
        mu = risk_free_rate; //final drift
    }
    else if(price_or_evaluate == "evaluate"){
        mu = mean_return * 261;
    }
    sigma = sqrt(s2)*sqrt(261); // final volatility

    //stock path generation using Monte-Carlo simulations
    MonteCarlo monteCarlo;
    vector<vector<double>> stock_paths;
    for (int i = 0; i < accuracy; i++) {
        vector<double> path = monteCarlo.simulated_stock_prices(price,mu,sigma,days,dt);
        stock_paths.push_back(path);
    }

    //calculates the expected payoff using the law of large numbers
    double expected_payoff = -1.0;
    if (put_or_call == "call") {
        CallOption option;
        expected_payoff = option.payoff_calc(stock_paths, strike_price, days, risk_free_rate);
    }
    else if (put_or_call == "put") {
        PutOption option;
        expected_payoff = option.payoff_calc(stock_paths, strike_price, days, risk_free_rate);
    }

    cout << expected_payoff << endl;


}

