#include <numeric>      
#include <stdexcept>  
#include "AsianOption.h"

AsianOption::AsianOption() : _strike(0.0) {}

AsianOption::AsianOption(const std::vector<double>& time_steps, double strike)
    :Time_steps(time_steps), _strike(strike)
{
    if (_strike < 0.0) { throw std::invalid_argument("Strike must be non negative"); }
}



double AsianOption::getStrike() const {
    return _strike;
}

const std::vector<double>& AsianOption::getTimeSteps() const {
    return Time_steps;
}

double AsianOption::payoffPath(std::vector<double>& prices) const {
    if (prices.empty()) {
        throw std::invalid_argument("Empty list");
    }
    double sum = 0.0;
    for (double price : prices) {
        sum += price;

    }
    double average_price = sum / prices.size();
    return payoff(average_price);
}
bool AsianOption::isAsianOption() const {
    return true;
}
AsianOption::~AsianOption() {}
