#include "AmericanCallOption.h"

AmericanCallOption::AmericanCallOption() : AmericanOption() {}

AmericanCallOption::AmericanCallOption(double expiry, double strike)
    : AmericanOption(expiry, strike) {}


double AmericanCallOption::payoff(double z) const {

    if (z >= getStrike()) { return z - getStrike(); }
    else { return 0.0; }

}

AmericanOption::optionType AmericanCallOption::GetOptionType() const {
    return optionType::call;
}


AmericanCallOption::~AmericanCallOption()
{

}