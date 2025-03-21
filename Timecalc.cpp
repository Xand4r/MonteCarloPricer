//
// Created by Alexander on 02.03.2025.
//
#include "Timecalc.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <cmath>
using namespace std;


int Timecalc::daysuntilexpiration(int d, int m, int y, string day) {
    std::chrono::time_point<std::chrono::system_clock> today = std::chrono::system_clock::now();
    time_t today_time = std::chrono::system_clock::to_time_t(today);

    tm now = *std::localtime(&today_time);

    now.tm_hour = 0;
    now.tm_min = 0;
    now.tm_sec = 0;

    tm future_date = {};
    future_date.tm_year = y-1900;
    future_date.tm_mon = m-1;
    future_date.tm_mday = d;

    time_t future_days = mktime(&future_date);
    today_time = mktime(&now);

    double duration = difftime(future_days ,today_time);
    int days = (int)duration/(60*60*24);

    int weekday = 0;
        if (day == "Mon"){ weekday = 1;}
        if (day == "Tue"){ weekday = 2;}
        if (day == "Wed"){ weekday = 3;}
        if (day == "Thu"){ weekday = 4;}
        if (day == "Fri"){ weekday = 5;}
        if (day == "Sat"){ weekday = 6;}
        if (day == "Sun"){ weekday = 1; days -= 1;}

    int wholeweeks = floor(days/7);
    int rest = days%7;

    cout << "amount of working days: " << days- wholeweeks*2 - floor((weekday+rest)/7)*2 << endl;
    cout << "days: " << days << endl;

    return days- wholeweeks*2 - floor((weekday+rest)/7)*2;

}
