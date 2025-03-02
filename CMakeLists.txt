cmake_minimum_required(VERSION 3.29)
project(MonteCarloPricer)

set(CMAKE_CXX_STANDARD 20)

add_executable(MonteCarloPricer main.cpp
        MonteCarlo.cpp
        MonteCarlo.h
        Payoff.cpp
        Payoff.h
        Timecalc.cpp
        Timecalc.h)
