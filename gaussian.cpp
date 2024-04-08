#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>

double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

void calc_path_spot_prices(std::vector<double>& spot_prices,  // Vector of spot prices to be filled in
                           const double& r,   // Risk free interest rate (constant)
                           const double& v,   // Volatility of underlying (constant)
                           const double& T) { // Expiry
  // Since the drift and volatility of the asset are constant
  // we will precalculate as much as possible for maximum efficiency
  double dt = T/static_cast<double>(spot_prices.size());
  double drift = exp(dt*(r-0.5*v*v));
  double vol = sqrt(v*v*dt);

  for (int i=1; i<spot_prices.size(); i++) {
    double gauss_bm = gaussian_box_muller();
    spot_prices[i] = spot_prices[i-1] * drift * exp(vol*gauss_bm);
  }
}

int main(int argc, char **argv) {
  unsigned num_sims = 100000;   // Number of simulated asset paths
  unsigned num_intervals = 250;  // Number of intervals for the asset path to be sampled 
  double S = 30.0;  // Option price
  double K = 29.0;  // Strike price
  double r = 0.08;   // Risk-free rate (8%)
  double v = 0.3;    // Volatility of the underlying (30%)
  double T = 1.00;    // One year until expiry
  std::vector<double> spot_prices(num_intervals, S);  // The vector of spot prices

    auto start = std::chrono::high_resolution_clock::now();
    calc_path_spot_prices(spot_prices, r, v, T);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> float_ms = end - start;
    std::cout << "Calculations elapsed time is " << float_ms.count() << " milliseconds" << std::endl;
    return 0;
}
