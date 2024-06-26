#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <chrono>

double doubleRand() {
  return double(rand()) / (double(RAND_MAX) + 1.0);
}

// Standard normal probability density function
double norm_pdf(const double& x) {
    return (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x);
}

// An approximation to the cumulative distribution function
// for the standard normal distribution
// Note: This is a recursive function
double norm_cdf(const double& x) {
    double k = 1.0/(1.0 + 0.2316419*x);
    double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

    if (x >= 0.0) {
        return (1.0 - (1.0/(pow(2*M_PI,0.5)))*exp(-0.5*x*x) * k_sum);
    } else {
        return 1.0 - norm_cdf(-x);
    }
}

// This calculates d_j, for j in {1,2}. This term appears in the closed
// form solution for the European call or put price
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

// Calculate the European vanilla call price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price based on
// underlying S, strike K, risk-free rate r, volatility of
// underlying sigma and time to maturity T
double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
}

int main(int argc, char **argv) {
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {

        // First we create the parameter list
        double S = doubleRand();  // Option price
        double K = doubleRand(); // Strike price
        double r = 0.05;   // Risk-free rate (5%)
        double v = 0.2;    // Volatility of the underlying (20%)
        double T = 1.0;    // One year until expiry

        // Then we calculate the call/put values
        double call = call_price(S, K, r, v, T);
        double put = put_price(S, K, r, v, T);

        //std::cout << "S:      " << S << std::endl;
        //std::cout << "K:       " << K << std::endl;
        //std::cout << "Call Price:      " << call << std::endl;
        //std::cout << "Put Price:       " << put << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> float_ms = end - start;

    std::cout << "Calculations elapsed time is " << float_ms.count() << " milliseconds" << std::endl;

    return 0;
}