#ifndef TIMECALC_H
#define TIMECALC_H
#include <ctime>
#include <string>

using std::tm;
using std::string;


class Timecalc {
public:

    int daysuntilexpiration(int d, int m, int y, string day);
};



#endif //TIMECALC_H
