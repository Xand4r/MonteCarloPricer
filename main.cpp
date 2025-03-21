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

    API_Acc acc;

    string symbol = "DIS";
    vector<double> prices = acc.getstockdata(symbol);

    vector<vector<double>> treasuryyielddata = acc.gettreasuryyielddata();
    vector<double> x_vals = treasuryyielddata[0];
    vector<double> y_vals = treasuryyielddata[1];
    CubicSpline spline(x_vals, y_vals);

    cout<< "spline interpolate: " << spline.interpolate(1095.0) << " actual value: " << y_vals[1] << endl;

/*
    int day, month, year;
    char dot1, dot2;
    bool corrdate = true;
    string weekday = "";

    while(corrdate) {
        cout << "Enter a date in the format (dd. mm. yyyy) and a Weekday (Mon/Tue/Wed/Thu/Fri/Sat/Sun): ";
        if (cin >> day >> dot1 >> month >> dot2 >> year >>  weekday  &&
        dot1 == '.' && dot2 == '.' ) {
            cout << "You entered: " << day << "-" << month << "-" << year << " weekday: "<< weekday <<endl;
            corrdate = false;
            } else {
                cout << "Invalid date format!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
    }

    Timecalc timecalc;

    double price = prices.back();
    double mu = 0.0;
    double sigma = 0.0;
    int days = timecalc.daysuntilexpiration(day, month, year, weekday);
    //int days = 126;
    double dt = 1.0/252.0;


    double meanreturn= 0.0;
    vector<double> payoffs;

    for(int i = 1; i < prices.size(); i++) {
        double logreturn = log(prices[i]/prices[i-1]);
        payoffs.push_back(logreturn);
        meanreturn += logreturn;
    }
    meanreturn = meanreturn/payoffs.size();
    double s2 = 0.0;
    for (double i: payoffs) {
        s2 += pow(i-meanreturn,2.0)/(payoffs.size()-1);
    }
    mu = (meanreturn+ 0.5*s2) * 252;
    sigma = sqrt(s2)*sqrt(252);
    cout << "sigma = " << sigma << " mu = " << mu << endl;


    MonteCarlo monteCarlo;

    vector<vector<double>> stock_paths;
    for (int i = 0; i < 100000; i++) {
        vector<double> path = monteCarlo.simulated_stock_prices(price,mu,sigma,days,dt);
        stock_paths.push_back(path);
    }


    CallOption call_option(105.0);

    double expected_payoff = call_option.payoff_calc(stock_paths, call_option.strike, days);
    cout << "Expected optionvalue: " << expected_payoff << endl;
*/
}
