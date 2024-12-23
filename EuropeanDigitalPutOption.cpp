#include "EuropeanDigitalPutOption.h"

EuropeanDigitalPutOption::EuropeanDigitalPutOption() {}

EuropeanDigitalPutOption::EuropeanDigitalPutOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalPutOption::payoff(double z) const {
    if (z <= getStrike()) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

EuropeanDigitalOption::optionType EuropeanDigitalPutOption::GetOptionType() {
    return optionType::put;
}

EuropeanDigitalPutOption::~EuropeanDigitalPutOption() {}
