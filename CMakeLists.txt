cmake_minimum_required(VERSION 3.29)
project(MonteCarloPricer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${CERES_INCLUDE_DIRS})

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)


add_executable(MonteCarloPricer main.cpp
        MonteCarlo.cpp
        MonteCarlo.h
        Payoff.cpp
        Payoff.h
        Timecalc.cpp
        Timecalc.h
        API_Acc.cpp
        API_Acc.h
        Interpolation.cpp
        Interpolation.h)

target_link_libraries(MonteCarloPricer PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
        ${CERES_LIBRARIES})

