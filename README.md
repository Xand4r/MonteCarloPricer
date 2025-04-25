# Monte Carlo Option Pricer

A C++ project that estimates European option prices using Monte Carlo simulation. It fetches real-time data via APIs and provides a minimal GUI for user input.

## 🚀 Core Features

- Fetches real-time stock and yield curve data  
- Supports European call and put options  
- Minimal GUI for easy user input  
- Configurable accuracy for Monte Carlo pricing  
- Option to choose between pricing and evaluation  

## 🔧 Install Dependencies (C++)

Make sure the following libraries are installed:

- [libcurl](https://curl.se/libcurl/) – for API requests  
- [nlohmann/json](https://github.com/nlohmann/json) – for parsing JSON  

### Installation Tips:

- **On Windows**: Use a package manager like [vcpkg](https://vcpkg.io)  
- **On macOS**: Use Homebrew  
  ```
  brew install curl
  ```

## 🟨 Node.js Frontend

You need [Node.js](https://nodejs.org/) installed to run the frontend.

## 🛠️ How to Run the Project

### ✅ First-Time Setup

In the root directory of the project:

1. Initialize and install Node.js dependencies:  
   ```
   npm init -y  
   npm install  
   ```

2. Compile the C++ backend:  
   ```
   g++ -std=c++17 -I. -I./nlohmann main.cpp API_Acc.cpp MonteCarlo.cpp Payoff.cpp Timecalc.cpp Interpolation.cpp -lcurl -o bin/option_pricer  
   ```

3. Give execution permission to the binary (only on Unix/macOS):  
   ```
   chmod +x bin/option_pricer  
   ```

4. Launch the server:  
   ```
   node server.js  
   ```

5. Open the link provided in the terminal (typically http://localhost:3000)

### 🔁 Every Time Before Using

1. Compile the backend:  
   ```
   g++ -std=c++17 -I. -I./nlohmann main.cpp API_Acc.cpp MonteCarlo.cpp Payoff.cpp Timecalc.cpp Interpolation.cpp -lcurl -o bin/option_pricer  
   ```

2. Launch the server:  
   ```
   node server.js  
   ```

3. Open the link provided in the terminal

## 🔑 API Keys

You'll need valid API keys for:

- **Stock data** – [Alpha Vantage](https://www.alphavantage.co/support/#api-key)  
- **Yield curve data** – [FRED](https://fred.stlouisfed.org/docs/api/api_key.html)  

> ⚠️ After exceeding your free Alpha Vantage usage limit, the frontend will warn you about invalid inputs.

## 🙏 Acknowledgments

The GUI was built in collaboration with my friend — big thanks for the clean and minimal design!
