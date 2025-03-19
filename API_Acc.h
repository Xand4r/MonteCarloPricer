//
// Created by Alexander Klasen on 05.03.25.
//

#ifndef API_ACC_H
#define API_ACC_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#include <windows.h>
#endif

#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


class API_Acc {
    public:
    static size_t callback(char *content, size_t size, size_t nmemb, string data);
    vector<double> getstockdata(string& symbol);
    vector<vector<double>> gettreasuryyielddata();





};



#endif //API_ACC_H
