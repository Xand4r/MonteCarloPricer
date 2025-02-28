#ifndef PAYOFF_H
#define PAYOFF_H
#include <vector>


using namespace std;
using std::vector;
class Payoff {
    public:
        virtual double payoff_calc(vector<vector<double>> stock_paths, double strike) = 0;
    virtual ~Payoff() {}
};

class CallOption : public Payoff {
    public:
    double strike;
    CallOption(double strike) {
        this->strike = strike;
    }
    double payoff_calc(vector<vector<double>> stock_paths, double strike) override;
};

class PutOption : public Payoff {
public:
    double strike;
    PutOption(double strike) {
        this->strike = strike;
    }
    double payoff_calc(vector<vector<double>> stock_paths, double strike) override;
};



#endif //PAYOFF_H
