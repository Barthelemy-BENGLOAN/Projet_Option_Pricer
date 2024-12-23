#include "PutOption.h"

PutOption::PutOption() {}

PutOption::PutOption(double _Expiry, double _Strike) : EuropeanVanillaOption(_Expiry, _Strike) {}

double PutOption::payoff(double z) const {
    if (getStrike() >= z) {
        return getStrike() - z;
    }
    else {
        return 0;
    }
}

PutOption::optionType PutOption::GetOptionType() {
    return optionType::put;
}
PutOption::~PutOption() {}
