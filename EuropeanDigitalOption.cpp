#include "EuropeanDigitalOption.h"
#include <stdexcept>
#include <string>
#include <iostream>

EuropeanDigitalOption::EuropeanDigitalOption() : _strike(0) {}

EuropeanDigitalOption::EuropeanDigitalOption(double expiry, double strike) : Option(expiry), _strike(strike) {
    if (expiry < 0) {
        throw std::invalid_argument("ERROR : Expiry " + std::to_string(expiry) + " is negative.");
    }
    if (strike < 0) {
        throw std::invalid_argument("ERROR : Strike " + std::to_string(strike) + " is negative.");
    }
}

double EuropeanDigitalOption::getStrike() const {
    return _strike;
}

EuropeanDigitalOption::optionType EuropeanDigitalOption::GetOptionType() {
    throw std::logic_error("GetOptionType is not implemented for EuropeanDigitalOption");
}

EuropeanDigitalOption::~EuropeanDigitalOption() {}
