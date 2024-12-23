#ifndef AMERICANPUTOPTION_H
#define AMERICANPUTOPTION_H


#include "AmericanOption.h"
#pragma once

class AmericanPutOption : public AmericanOption {
public:
    AmericanPutOption();
    AmericanPutOption(double, double);
    double payoff(double) const override;
    optionType GetOptionType() const override;
    ~AmericanPutOption();

};

#endif