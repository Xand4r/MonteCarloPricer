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

vector<double> API_Acc::getdata(string& symbol) {
    string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&datatype=json&apikey=57QUQNLQ3C62WQIO";

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
    json closingprices = j["Time Series (Daily)"];
    for(json item : closingprices) {
        double price = stod(item["4. close"].get<string>());
        prices.push_back(price);
    }
    return prices;
}