#include "EuropeanDigitalCallOption.h"

EuropeanDigitalCallOption::EuropeanDigitalCallOption() {}

EuropeanDigitalCallOption::EuropeanDigitalCallOption(double expiry, double strike)
    : EuropeanDigitalOption(expiry, strike) {}

double EuropeanDigitalCallOption::payoff(double z) const {
    if (z >= getStrike()) {
        return 1.0;
    }
    else {
        return 0.0;
    }
}

EuropeanDigitalOption::optionType EuropeanDigitalCallOption::GetOptionType() {
    return optionType::call;
}

EuropeanDigitalCallOption::~EuropeanDigitalCallOption() {}
