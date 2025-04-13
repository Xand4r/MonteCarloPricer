#ifndef PAYOFF_H
#define PAYOFF_H
#include <vector>


using namespace std;
using std::vector;
class Payoff {
    public:
        virtual double payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double risk_free_rate) = 0;
    virtual ~Payoff() {}
};

class CallOption : public Payoff {
    public:
    double payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double risk_free_rate) override;
};

class PutOption : public Payoff {
public:
    double payoff_calc(vector<vector<double>> stock_paths, double strike, int days, double risk_free_rate) override;
};



#endif //PAYOFF_H
