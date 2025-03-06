//
// Created by Alexander Klasen on 05.03.25.
//

#ifndef API_ACC_H
#define API_ACC_H
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;


class API_Acc {
    public:
    static size_t callback(char *content, size_t size, size_t nmemb, string data);
    vector<double> getdata(string& symbol);





};



#endif //API_ACC_H
