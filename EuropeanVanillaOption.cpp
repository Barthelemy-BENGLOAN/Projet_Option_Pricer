#include "EuropeanVanillaOption.h"
#include <stdexcept>
#include <string>
#include <iostream>

EuropeanVanillaOption::EuropeanVanillaOption() : _strike(0) {}

EuropeanVanillaOption::EuropeanVanillaOption(double expiry, double strike) : Option(expiry), _strike(strike) {
    if (expiry < 0) {
        throw std::invalid_argument("ERROR : Expiry " + std::to_string(expiry) + "is negative.");
    }
    if (strike < 0) {
        throw std::invalid_argument("ERROR : Strike " + std::to_string(strike) + " is negative.");
    }
}

double EuropeanVanillaOption::getStrike() const {
    return _strike;
}

EuropeanVanillaOption::optionType EuropeanVanillaOption::GetOptionType() {
    throw std::logic_error("GetOptionType is not implemented for EuropeanVanillaOption");
}
EuropeanVanillaOption::~EuropeanVanillaOption() {}

