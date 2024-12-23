#include "BlackScholesMCPricer.h"
#include "MT.h"  // Assuming MT has a function rand_norm() for normal distribution
#include "AsianOption.h"
#include <stdexcept>
#include <vector>
#include <cmath>
#include <memory>

BlackScholesMCPricer::BlackScholesMCPricer(Option* option,double initial_price,double interest_rate,double volatility)
    : option_(option), initial_price_(initial_price), interest_rate_(interest_rate), volatility_(volatility),
    nb_paths_(0), price_estimate(0.0),variance(0.0),sum_payoffs(0.0), sum_payoffs_squared(0.0),antithetic(false) {}

// constructor for reduction
BlackScholesMCPricer::BlackScholesMCPricer(Option* option,double initial_price,double interest_rate,double volatility,bool antithetic)
    : option_(option),initial_price_(initial_price),interest_rate_(interest_rate),volatility_(volatility),
    nb_paths_(0),price_estimate(0.0),variance(0.0),sum_payoffs(0.0),sum_payoffs_squared(0.0),antithetic(antithetic) {}

void BlackScholesMCPricer::set_antithetic(bool use) {
    antithetic = use;
}

void BlackScholesMCPricer::generate(int nb_paths) {
    double r = interest_rate_;
    double sigma = volatility_;
    double r_sigma_term = r - 0.5 * sigma * sigma;
    double discount_factor = std::exp(-r * option_->getExpiry());

    if (antithetic) {
        // we want an even number
        int n = (nb_paths % 2 == 0) ? nb_paths : nb_paths + 1;
        for (int i = 0; i < n; i += 2) {
            // Z
            double payoff1 = 0.0;
            if (option_->isAsianOption()) {
                // Asiat option : multi-step
                auto asian_option = dynamic_cast<AsianOption*>(option_);
                const auto& time_steps = asian_option->getTimeSteps();
                double last_price = initial_price_;
                std::vector<double> path_prices1;
                path_prices1.reserve(time_steps.size());

                for (size_t j = 1; j < time_steps.size(); ++j) {
                    double time_diff = time_steps[j] - time_steps[j - 1];
                    double z = MT::rand_norm(); 
                    last_price *= std::exp(r_sigma_term * time_diff
                        + sigma * std::sqrt(time_diff) * z);
                    path_prices1.push_back(last_price);
                }
                payoff1 = option_->payoffPath(path_prices1);
            }
            else {
                // Vanilla option: one step
                double z = MT::rand_norm();
                double final_price = initial_price_ * std::exp(
                    r_sigma_term * option_->getExpiry()
                    + sigma * std::sqrt(option_->getExpiry()) * z
                );
                std::vector<double> path_prices = { final_price };
                payoff1 = option_->payoffPath(path_prices);
            }
            // -Z
            double payoff2 = 0.0;
            if (option_->isAsianOption()) {
                auto asian_option = dynamic_cast<AsianOption*>(option_);
                const auto& time_steps = asian_option->getTimeSteps();

                double last_price = initial_price_;
                std::vector<double> path_prices2;
                path_prices2.reserve(time_steps.size());

                for (size_t j = 1; j < time_steps.size(); ++j) {
                    double time_diff = time_steps[j] - time_steps[j - 1];
                    double zbar = -MT::rand_norm();
                    last_price *= std::exp(r_sigma_term * time_diff
                        + sigma * std::sqrt(time_diff) * zbar);
                    path_prices2.push_back(last_price);
                }
                payoff2 = option_->payoffPath(path_prices2);
            }
            else {
                double zbar = -MT::rand_norm();
                double final_price = initial_price_ * std::exp(
                    r_sigma_term * option_->getExpiry()
                    + sigma * std::sqrt(option_->getExpiry()) * zbar
                );
                std::vector<double> path_prices = { final_price };
                payoff2 = option_->payoffPath(path_prices);
            }

            double payoff_mean = 0.5 * (payoff1 + payoff2);
            double discounted_payoff = discount_factor * payoff_mean;
            sum_payoffs += discounted_payoff;
            sum_payoffs_squared += discounted_payoff * discounted_payoff;
        }
        // we consider thaht we have added (n/2) effective samples
        nb_paths_ += (n / 2);
    }
    // antithetic = false
    else {
        std::vector<std::vector<double>> sim_prices(nb_paths);

        for (int i = 0; i < nb_paths; ++i) {
            std::vector<double>& path_prices = sim_prices[i];

            if (option_->isAsianOption()) {
                auto asian_option = dynamic_cast<AsianOption*>(option_);
                const auto& time_steps = asian_option->getTimeSteps();
                path_prices.reserve(time_steps.size());

                double last_price = initial_price_;
                for (size_t j = 1; j < time_steps.size(); ++j) {
                    double time_diff = time_steps[j] - time_steps[j - 1];
                    double z = MT::rand_norm();
                    last_price *= std::exp(
                        r_sigma_term * time_diff
                        + sigma * std::sqrt(time_diff) * z
                    );
                    path_prices.push_back(last_price);
                }
            }
            else {
                double z = MT::rand_norm();
                double final_price = initial_price_ * std::exp(
                    r_sigma_term * option_->getExpiry()
                    + sigma * std::sqrt(option_->getExpiry()) * z
                );
                path_prices.push_back(final_price);
            }

            double payoff = option_->payoffPath(path_prices);
            double discounted_payoff = discount_factor * payoff;
            sum_payoffs += discounted_payoff;
            sum_payoffs_squared += discounted_payoff * discounted_payoff;
        }
        nb_paths_ += nb_paths;
    }

    price_estimate = sum_payoffs / nb_paths_;
}


double BlackScholesMCPricer::operator()() const {
    if (nb_paths_ == 0) {
        throw std::logic_error("No paths have been generated to estimate the price.");
    }
    return price_estimate;
}

std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    if (nb_paths_ == 0) {
        throw std::invalid_argument("No paths generated");
    }
    double mean_payoff = sum_payoffs / nb_paths_;
    double variance = (sum_payoffs_squared / nb_paths_) - (mean_payoff * mean_payoff);
    double std_dev = sqrt(variance / nb_paths_);
    double margin = 1.96 * std_dev;
    return { price_estimate - margin, price_estimate + margin };
}

int BlackScholesMCPricer::getNbPaths() const {
    return nb_paths_;
}
