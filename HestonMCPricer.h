#ifndef HESTONMCPRICER_H
#define HESTONMCPRICER_H

#include "Option.h"
#include <vector>

class HestonMCPricer {
private:
    Option* option_;
    double S0_;
    double r_;
    int nb_paths_;
    double price_estimate_;
    double sum_payoffs_, sum_payoffs_sq_;
    // Heston parameters
    double kappa_; // mean reversion speed
    double theta_;// long term variance
    double xi_;  // vol of vol
    double rho_; // correlation
    double v0_; //initial variance

public:
    
    HestonMCPricer(Option* option,double S0,double r,double kappa, double theta,double xi,double rho,double v0);
    void generate(int nb_paths, int nSteps);
    double price() const;
    std::vector<double> confidenceInterval() const;
};

#endif
