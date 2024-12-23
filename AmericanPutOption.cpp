#include "AmericanPutOption.h"

AmericanPutOption::AmericanPutOption() : AmericanOption() {}

AmericanPutOption::AmericanPutOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}


double AmericanPutOption::payoff(double z) const {

    if (z <= getStrike()) { return getStrike() - z; }
    else { return 0.0; }

}

AmericanOption::optionType AmericanPutOption::GetOptionType() const {
    return optionType::put;
}


AmericanPutOption::~AmericanPutOption()
{

}