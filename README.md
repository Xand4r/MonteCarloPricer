# Monte Carlo Option Pricer
A C++ project that estimates European option prices using Monte Carlo simulation. It fetches real-time data via APIs and provides a GUI for user input.

# Core features:
fetches real time stock and yield data
supports european put and call options
minimal GUI for easy user inputs
configurable accuracy of price calculation
possibility to choose between option pricing and option evaluation

## Install Dependencies (C++)
Make sure the following libraries are installed:
- [libcurl](https://curl.se/libcurl/)
- [nlohmann/json](https://github.com/nlohmann/json)

On Windows use a package manager like vcpkg
On MacOs use Homebrew for installation

## Node.js Frontend
You need [Node.js](https://nodejs.org/) installed to run the frontend.

## How to run the Project
# First time use:
run the following inside the root directory of the projects:
- npm init -y 
- npm install
compile the c++ code:
- g++ -std=c++17 -I. -I./nlohmann main.cpp API_Acc.cpp MonteCarlo.cpp Payoff.cpp Timecalc.cpp Interpolation.cpp -lcurl -o bin/option_pricer
give execution permission to the binary file:
- chmod +x bin/option_pricer
launch the server:
- node server.js
open the link provided in the terminal


# Always before using:
run the following inside the root directory:
compile the c++ code:
- g++ -std=c++17 -I. -I./nlohmann main.cpp API_Acc.cpp MonteCarlo.cpp Payoff.cpp Timecalc.cpp Interpolation.cpp -lcurl -o bin/option_pricer
launch the server:
- node server.js
open the link provided in the terminal

### 6. **API Keys**

You’ll need valid API keys for:
- Stock data (get it from Alphavantage (https://www.alphavantage.co/support/#api-key))
- Yield curve data (get it from FRED (https://fred.stlouisfed.org/docs/api/api_key.html))
(after using all of your free AlphaVantage API uses the frontend will warn you about invalid inputs)
