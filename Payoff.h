#ifndef PAYOFF_H
#define PAYOFF_H
#include <vector>


using namespace std;
using std::vector;
class Payoff {
    public:
        virtual double payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double riskfree_rate) = 0;
    virtual ~Payoff() {}
};

class CallOption : public Payoff {
    public:
    double strike;
    double riskfree_rate;
    CallOption(double strike, double riskfree_rate) {
        this->strike = strike;
        this->riskfree_rate = riskfree_rate;
    }
    double payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double riskfree_rate) override;
};

class PutOption : public Payoff {
public:
    double strike;
    double riskfree_rate;
    PutOption(double strike,double riskfree_rate) {
        this->strike = strike;
        this->riskfree_rate = riskfree_rate;
    }
    double payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double riskfree_rate) override;
};



#endif //PAYOFF_H
