#include <iostream>
#include <vector>
#include "MonteCarlo.h"
#include "Payoff.h"
#include "Timecalc.h"
#include "API_Acc.h"
#include "Interpolation.h"

using namespace std;
using std::vector;

int main() {

    //setting expiry date of the option
    int day, month, year;
    char dot1, dot2;
    bool correct_date = true;
    string weekday;

    while(correct_date) {
        cout << "Enter a date in the format dd. mm. yyyy and the current Weekday Mon/Tue/Wed/Thu/Fri/Sat/Sun: ";
        if (cin >> day >> dot1 >> month >> dot2 >> year >>  weekday  &&
        dot1 == '.' && dot2 == '.' ) {
            cout << "You entered: " << day << "-" << month << "-" << year << " weekday: "<< weekday <<endl;
            correct_date = false;
        } else {
            cout << "Invalid date format!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    //setting strike price of the option
    double strike_price = 0.0;
    cout << "what is your options strike price: " << endl;
    cin >> strike_price;

    // Accessing API for stock price data and treasury yield data
    API_Acc access_data;

    string symbol = "AAPL"; // stock symbol
    int put_or_call; // 0=Put, 1=Call

    Timecalc timecalc;
    int days = timecalc.DaysUntilExpiration(day, month, year, weekday); // amount of workdays
    vector<double> prices = access_data.GetStockData(symbol, 3*days); // gets historic price data from 3x the amount of days in relation to the expiry date
    vector<vector<double>> treasury_yield_data = access_data.GetTreasuryYieldData(); // gets current treasury yield data
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
    mu = risk_free_rate; //final drift
    //mu = mean_return * 261;
    sigma = sqrt(s2)*sqrt(261); // final volatility

    //stock path generation using Monte-Carlo simulations
    MonteCarlo monteCarlo;
    vector<vector<double>> stock_paths;
    for (int i = 0; i < 100000; i++) {
        vector<double> path = monteCarlo.simulated_stock_prices(price,mu,sigma,days,dt);
        stock_paths.push_back(path);
    }

    //calculates the expected payoff using the central limit theorem
    double expected_payoff = -1.0;
    if (put_or_call == 0) {
        CallOption option;
        expected_payoff = option.payoff_calc(stock_paths, strike_price, days, risk_free_rate);
    }
    else if (put_or_call == 1) {
        PutOption option;
        expected_payoff = option.payoff_calc(stock_paths, strike_price, days, risk_free_rate);
    }

    cout << "Expected option value: " << expected_payoff << endl;
    cout << "Strike price: " << strike_price << endl;
    cout << "risk free rate: " << risk_free_rate << endl;
    cout << "volatility : " << sigma << endl;
    cout << "drift : " << mu << endl;
    cout << "days: " << timecalc.DaysInbetween(day, month, year) << endl;
    cout << "last price: "<< prices.back() << endl;


}
