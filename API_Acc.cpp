//
// Created by Alexander Klasen on 05.03.25.
//
#include "API_Acc.h"

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

    size_t API_Acc::callback(char* content, size_t size, size_t nmemb, string data) {
    data.append(content, size * nmemb);
    return size * nmemb;
}
    json API_Acc::parser(string url) {
        CURL *curl = curl_easy_init();
        CURLcode res;
        string result;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        vector<double> prices;
        json j = json::parse(result);
        return j;
    }


vector<double> API_Acc::getstockdata(string& symbol) {
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&datatype=json&apikey=57QUQNLQ3C62WQIO";

    vector<double> prices;
    json j = parser(url);
    json closingprices = j["Time Series (Daily)"];
    for(json item : closingprices) {
        double price = stod(item["4. close"].get<string>());
        prices.push_back(price);
    }
    return prices;
}

vector<vector<double>> API_Acc::gettreasuryyielddata() {
        vector<string> timeperiods = {"DGS1MO", "DGS3MO", "DGS6MO", "DGS1", "DGS2", "DGS3", "DGS5", "DGS7", "DGS10", "DGS20", "DGS30"};
        vector<double> day_amount = {30.0, 90.0, 180.0, 360.0, 730.0, 1095.0, 1825.0, 2555.0, 3650.0, 7300.0, 10950.0};
        vector<vector<double>> all_treasury_yields;

        vector<double> values;
        for (string i : timeperiods) {
            string url = "https://api.stlouisfed.org/fred/series/observations?series_id=" + i + "&api_key=76ba0991fa6e0da31852aac2c918561e&file_type=json";
            json j = parser(url);
            double newest_yield = stod( j["observations"].back()["value"].get<string>());
            values.push_back(newest_yield);
        }
        all_treasury_yields.push_back(day_amount);
        all_treasury_yields.push_back(values);
        return all_treasury_yields;
    }