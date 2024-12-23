#ifndef AMERICANCALLOPTION_H
#define AMERICANCALLOPTION_H

#include "AmericanOption.h"
#pragma once

class AmericanCallOption : public AmericanOption {
public:
    AmericanCallOption();
    AmericanCallOption(double, double);
    double payoff(double) const override;
    optionType GetOptionType() const override;
    ~AmericanCallOption();

};

#endif