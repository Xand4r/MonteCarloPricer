cmake_minimum_required(VERSION 3.29)
project(MonteCarloPricer)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(MonteCarloPricer main.cpp
        MonteCarlo.cpp
        MonteCarlo.h
        Payoff.cpp
        Payoff.h
        Timecalc.cpp
        Timecalc.h
        API_Acc.cpp
        API_Acc.h)

target_link_libraries(MonteCarloPricer PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json)
