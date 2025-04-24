#include "Timecalc.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <cmath>
using namespace std;


int Timecalc::DaysUntilExpiration(int d, int m, int y, int& day) {
    int days = DaysInbetween(d, m, y); // amount of days inbetween current and input date

    //converts today's weekday as string to a number
        if (day == 0){ day = 1; days -= 1;} //

    int whole_weeks = floor(days/7); // amount of whole weeks in the time difference
    int rest = days%7; // amount of days in the last not whole week

    // removes weekends of whole weeks and the possible weekend in the last not whole week
    return days- whole_weeks*2 - floor((day+rest)/7)*2;

}

int Timecalc::DaysInbetween(int d, int m, int y) {
    std::chrono::time_point<std::chrono::system_clock> today = std::chrono::system_clock::now();
    time_t today_time = std::chrono::system_clock::to_time_t(today); // today's date

    tm now = *std::localtime(&today_time);

    // removes exact hours, minutes and seconds of today's date
    now.tm_hour = 0;
    now.tm_min = 0;
    now.tm_sec = 0;

    // sets future date's year, month and day amount
    tm future_date = {};
    future_date.tm_year = y-1900;
    future_date.tm_mon = m-1;
    future_date.tm_mday = d;

    // converts future and today's date to time_t objects
    time_t future_days = mktime(&future_date);
    today_time = mktime(&now);

    double duration = difftime(future_days ,today_time); // calculates time difference in seconds
    int days = (int)duration/(60*60*24); // converts difference to days
    return days;
}

