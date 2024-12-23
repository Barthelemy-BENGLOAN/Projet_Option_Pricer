#include "AmericanOption.h"
#include <iostream>
#include <string>

AmericanOption::AmericanOption() : _strike(0) {}

AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry), _strike(strike) {
    if (expiry < 0) {
        throw std::invalid_argument("ERROR : Expiry " + std::to_string(expiry) + " is negative.");
    }
    if (strike < 0) {
        throw std::invalid_argument("ERROR : Strike " + std::to_string(strike) + " is negative.");
    }
}

double AmericanOption::getStrike() const {
    return _strike;
}
bool AmericanOption::isAmericanOption() const {
    return true;
}

AmericanOption::~AmericanOption()
{

}