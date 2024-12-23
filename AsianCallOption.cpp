#include "AsianCallOption.h"

AsianCallOption::AsianCallOption() : AsianOption() {}

AsianCallOption::AsianCallOption(const std::vector<double>& time_steps, double strike)
    : AsianOption(time_steps, strike) {}

double AsianCallOption::payoff(double price) const {
    double payoff_value = price - getStrike();
    if (payoff_value > 0.0) {
        return payoff_value;
    }
    else {
        return 0.0;
    }
}

AsianOption::optionType AsianCallOption::GetOptionType() const {
    return optionType::call;
}

AsianCallOption::~AsianCallOption() {}
