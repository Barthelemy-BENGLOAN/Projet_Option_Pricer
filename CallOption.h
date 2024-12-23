#ifndef CALLOPTION_H
#define CALLOPTION_H
#include "EuropeanVanillaOption.h"
#pragma once

class CallOption : public EuropeanVanillaOption {
public:
    CallOption();
    CallOption(double, double);
    double payoff(double) const override;
    optionType GetOptionType() override;
    ~CallOption();

};

#endif 
