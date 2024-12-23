#include "AsianPutOption.h"

AsianPutOption::AsianPutOption() : AsianOption() {}

AsianPutOption::AsianPutOption(const std::vector<double>& time_steps, double strike)
    : AsianOption(time_steps, strike) {}

double AsianPutOption::payoff(double price) const {
    double payoff_value = getStrike() - price;
    if (payoff_value > 0.0) {
        return payoff_value;
    }
    else {
        return 0.0;
    }
}

AsianOption::optionType AsianPutOption::GetOptionType() const {
    return optionType::put;
}

AsianPutOption::~AsianPutOption() {}
