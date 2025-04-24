#ifndef TIMECALC_H
#define TIMECALC_H
#include <ctime>
#include <string>

using std::tm;
using std::string;


class Timecalc {
public:

    int DaysInbetween(int d, int m, int y); //calculates amount of days inbetween two dates
    int DaysUntilExpiration(int d, int m, int y, int& day); //removes weekends in DaysInbetween calculation (just workdays)
};



#endif //TIMECALC_H
