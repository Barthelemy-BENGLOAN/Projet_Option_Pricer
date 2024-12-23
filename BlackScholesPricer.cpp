#include "BlackScholesPricer.h"
using namespace std;
#include <iostream>
#include <math.h> 
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility)
    :Option_(option), Asset_price_(asset_price), Interest_rate_(interest_rate), Volatility_(volatility)
{

}

double BlackScholesPricer::operator()() {
    double S = Asset_price_;
    double r = Interest_rate_;
    double T = Option_->getExpiry();
    double sigma = Volatility_;
    double d1, d2, prix;

    // Vérification de l'option et récupération de K et du type (call/put)
    double K;
    bool isCall;
    bool isDigital = false;

    if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(Option_)) {
        K = vanillaOption->getStrike();
        isCall = (vanillaOption->GetOptionType() == EuropeanVanillaOption::optionType::call);
    }
    else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(Option_)) {
        K = digitalOption->getStrike();
        isCall = (digitalOption->GetOptionType() == EuropeanDigitalOption::optionType::call);
        isDigital = true;
    }
    else {
        throw std::logic_error("Option type does not support strike price.");
    }

    // Calcul de d1 et d2
    d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    d2 = d1 - sigma * sqrt(T);

    // Calcul du prix en fonction du type d'option (numérique ou vanille) et du type (call ou put)
    if (isDigital) {
        if (isCall) {
            prix = exp(-r * T) * 0.5 * erfc(-d2 / sqrt(2));

        }
        else {
            prix = exp(-r * T) * 0.5 * erfc(d2 / sqrt(2));
        }
    }
    else {
        if (isCall) {
            prix = S * 0.5 * erfc(-d1 / sqrt(2)) - K * exp(-r * T) * 0.5 * erfc(-d2 / sqrt(2));
        }
        else {

            prix = -S * 0.5 * erfc(d1 / sqrt(2)) + K * exp(-r * T) * 0.5 * erfc(d2 / sqrt(2));
        }
    }

    return prix;
}
double BlackScholesPricer::delta() {
    double S = Asset_price_;
    double r = Interest_rate_;
    double T = Option_->getExpiry();
    double sigma = Volatility_;
    double d, delta;

    // Vérification de l'option et récupération de K et du type (call/put)
    double K;
    bool isCall;
    bool isDigital = false;

    if (auto vanillaOption = dynamic_cast<EuropeanVanillaOption*>(Option_)) {
        K = vanillaOption->getStrike();
        isCall = (vanillaOption->GetOptionType() == EuropeanVanillaOption::optionType::call);
    }
    else if (auto digitalOption = dynamic_cast<EuropeanDigitalOption*>(Option_)) {
        K = digitalOption->getStrike();
        isCall = (digitalOption->GetOptionType() == EuropeanDigitalOption::optionType::call);
        isDigital = true;
    }
    else {
        throw std::logic_error("Option type does not support strike price.");
    }

    // Calcul de d
    d = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));

    // Calcul du delta en fonction du type d'option (numérique ou vanille) et du type (call ou put)
    if (isDigital) {
        double pdf_d = exp(-0.5 * d * d) / sqrt(2 * M_PI);  // PDF de la loi normale pour d
        if (isCall) {
            delta = pdf_d / (S * sigma * sqrt(T));
        }
        else {
            delta = -pdf_d / (S * sigma * sqrt(T));
        }
    }
    else {
        if (isCall) {
            delta = 0.5 * erfc(-d / sqrt(2));
        }
        else {
            delta = 0.5 * erfc(-d / sqrt(2)) - 1;
        }
    }

    return delta;
}

BlackScholesPricer::~BlackScholesPricer()
{}