#include <iostream>
#include <vector>
#include "MonteCarlo.h"
#include "Payoff.h"
#include "Timecalc.h"

using namespace std;
using std::vector;

int main() {
    int day, month, year;
    char openParen, comma1, comma2, closeParen;
    bool corrdate = true;

    while(corrdate) {
        cout << "Enter a date in the format (dd, mm, yyyy): ";
        if (cin >> openParen >> day >> comma1 >> month >> comma2 >> year >> closeParen &&
            openParen == '(' && comma1 == ',' && comma2 == ',' && closeParen == ')') {
            cout << "You entered: " << day << "-" << month << "-" << year << endl;
            corrdate = false;
            } else {
                cout << "Invalid date format!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
    }

    Timecalc timecalc;

    double price = 100;
    double mu = 0.05;
    double sigma = 0.2;
    int days = timecalc.daysuntilexpiration(day, month, year);
    double dt = 1.0/252.0;


    MonteCarlo monteCarlo;

    vector<vector<double>> stock_paths;
    for (int i = 0; i < 100000; i++) {
        vector<double> path = monteCarlo.simulated_stock_prices(price,mu,sigma,days,dt);
        stock_paths.push_back(path);
    }


    CallOption call_option(120);

    double expected_payoff = call_option.payoff_calc(stock_paths,call_option.strike);
    cout << "Expected optionvalue: " << expected_payoff << endl;

}
