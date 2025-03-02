//
// Created by Alexander on 02.03.2025.
//
#include "Timecalc.h"
#include <ctime>
#include <chrono>
using namespace std;


int Timecalc::daysuntilexpiration(int d, int m, int y) {
    std::chrono::time_point<std::chrono::system_clock> today = std::chrono::system_clock::now();
    time_t today_time = std::chrono::system_clock::to_time_t(today);

    tm future_date = {};
    future_date.tm_year = y-1900;
    future_date.tm_mon = m-1;
    future_date.tm_mday = d;

    time_t future_days = mktime(&future_date);

    double duration = difftime(future_days ,today_time);
    int days = (int)duration/(60*60*24);
    return days;

}
