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

    API_Acc access_data;

    string symbol = "AAPL";
    vector<double> prices = access_data.getstockdata(symbol);

    vector<vector<double>> treasuryyielddata = access_data.gettreasuryyielddata();
    vector<double> x_vals = treasuryyielddata[0];
    vector<double> y_vals = treasuryyielddata[1];
    CubicSpline spline(x_vals, y_vals);

    int day, month, year;
    char dot1, dot2;
    bool corrdate = true;
    string weekday = "";

    while(corrdate) {
        cout << "Enter a date in the format dd. mm. yyyy and the current Weekday Mon/Tue/Wed/Thu/Fri/Sat/Sun: ";
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
    double dt = 1.0/261;
    double riskfree_rate = spline.interpolate(timecalc.daysinbetween(day, month, year))/100;


    double meanreturn= 0.0;
    vector<double> payoffs;

    for(int i = 1; i < prices.size(); i++) {
        double logreturn = log(prices[i]/prices[i-1]);
        payoffs.push_back(logreturn);
        meanreturn += logreturn;
    }
    meanreturn = meanreturn/payoffs.size();
    double s2 = 0.0;
    for (double r: payoffs) {
        s2 += pow(r-meanreturn,2.0);
    }
    s2 /= payoffs.size()-1;
    mu = riskfree_rate;
    //mu = meanreturn * 261;
    sigma = sqrt(s2)*sqrt(261);


    MonteCarlo monteCarlo;

    vector<vector<double>> stock_paths;
    for (int i = 0; i < 1000000; i++) {
        vector<double> path = monteCarlo.simulated_stock_prices(price,mu,sigma,days,dt);
        stock_paths.push_back(path);
    }


    CallOption call_option(100.0, riskfree_rate);

    double expected_payoff = call_option.payoff_calc(stock_paths, call_option.strike, days, call_option.riskfree_rate);
    cout << "Expected optionvalue: " << expected_payoff << endl;
    cout << "Strike price: " << call_option.strike << endl;
    cout << "riskfree rate: " << riskfree_rate << endl;
    cout << "volatility : " << sigma << endl;
    cout << "drift : " << mu << endl;
    cout << "days: " << timecalc.daysinbetween(day, month, year) << endl;
    cout << "last price: "<< prices.back() << endl;


}
