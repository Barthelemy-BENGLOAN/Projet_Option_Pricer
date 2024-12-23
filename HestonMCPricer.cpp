#include "HestonMCPricer.h"
#include "MT.h"
#include <cmath>
#include <stdexcept>

HestonMCPricer::HestonMCPricer(Option* option,
    double S0,double r,double kappa,double theta,double xi,double rho,double v0): option_(option),S0_(S0),r_(r),kappa_(kappa),
    theta_(theta),xi_(xi),rho_(rho),v0_(v0),nb_paths_(0),price_estimate_(0.0),sum_payoffs_(0.0),sum_payoffs_sq_(0.0)
{}

void HestonMCPricer::generate(int nb_paths, int nSteps) {
    double T = option_->getExpiry();
    double dt = T / nSteps;

    for (int p = 0; p < nb_paths; ++p) {
        double S = S0_;
        double v = v0_;

        for (int step = 0; step < nSteps; ++step) {
            double U1 = MT::rand_norm();
            double U2 = MT::rand_norm();
            double Z1 = U1;
            double Z2 = rho_ * U1 + std::sqrt(1 - rho_ * rho_) * U2;
            double vn = v + kappa_ * (theta_ - v) * dt + xi_ * std::sqrt(std::max(v, 0.0)) * std::sqrt(dt) * Z2;
            if (vn < 0) vn = 0.0;
            double Sn = S * std::exp((r_ - 0.5 * v) * dt + std::sqrt(std::max(v, 0.0) * dt) * Z1);
            // for the next step
            S = Sn;
            v = vn;
        }
        double payoff = option_->payoff(S);
        sum_payoffs_ += payoff;
        sum_payoffs_sq_ += payoff * payoff;
    }

    nb_paths_ += nb_paths;
    price_estimate_ = std::exp(-r_ * option_->getExpiry()) * (sum_payoffs_ / nb_paths_);
}

double HestonMCPricer::price() const {
    if (nb_paths_ == 0) {
        throw std::logic_error("No paths generated");
    }
    return price_estimate_;
}

std::vector<double> HestonMCPricer::confidenceInterval() const {
    if (nb_paths_ == 0) {
        throw std::logic_error("No paths for CI");
    }
    double mean = sum_payoffs_ / nb_paths_;
    double second_moment = sum_payoffs_sq_ / nb_paths_;
    double var = second_moment - mean * mean;
    double std_dev = std::sqrt(var / nb_paths_);
    double margin = 1.96 * std_dev * std::exp(-r_ * option_->getExpiry());

    double p = price();
    return { p - margin, p + margin };
}
