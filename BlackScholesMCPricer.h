#ifndef BLACKSCHOLESMCPRICER_H
#define BLACKSCHOLESMCPRICER_H

#include "Option.h"
#include "MT.h"
#include <vector>
#include <cmath>

class BlackScholesMCPricer {
private:
    Option* option_;
    double initial_price_;
    double interest_rate_;
    double volatility_;
    int nb_paths_ = 1;
    double price_estimate;
    double variance;
    double sum_payoffs;
    double sum_payoffs_squared;
    bool antithetic;

public:
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility, bool antithetic); // constructor for variance reduction
    void generate(int); //Génère des trajectoires aléatoires
    void set_antithetic(bool use);
    int getNbPaths() const;
    double operator()() const; // prix de l'option
    std::vector<double> confidenceInterval() const;// Retourne un intervalle de confiance à 95
};

#endif








