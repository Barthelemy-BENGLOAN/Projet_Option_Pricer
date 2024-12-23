#include "Option.h"
#include <stdexcept>

Option::Option() : _expiry(0) {}

Option::Option(double _Expiry) : _expiry(_Expiry) {}

double Option::getExpiry() const {
    return _expiry;
}



double Option::payoffPath(std::vector<double>& prices) const {
    if (prices.empty()) {
        throw std::invalid_argument("empty list");
    }
    return payoff(prices.back());
}

Option::~Option() {}