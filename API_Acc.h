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
    vector<double> GetStockData(string& symbol, int days); //gets stockdata on a specific company from an API
    vector<vector<double>> GetTreasuryYieldData(); //gets treasury yield rates on US government bonds
    private:
    static size_t callback(char *content, size_t size, size_t nmemb, string data); //callback function for API calls
    static json parser(const string& url); // parses received data into a json





};



#endif //API_ACC_H
