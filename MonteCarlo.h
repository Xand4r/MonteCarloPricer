#ifndef MONTECARLO_H
#define MONTECARLO_H
#include <vector>
#include <random>


using std::random_device;
using std::normal_distribution;
using std::mt19937;
using std::vector;

class MonteCarlo {
    public:
        // generates stock paths using geometric Brownian motion
        vector<double> simulated_stock_prices(double price, double mu, double sigma, int days, double dt);
    private:
        random_device rd;
        mt19937 gen;
        normal_distribution<double> distribution;
};




#endif //MONTECARLO_H
