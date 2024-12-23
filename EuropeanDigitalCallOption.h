#ifndef EUROPEANDIGITALCALLOPTION_H
#define EUROPEANDIGITALCALLOPTION_H

#include "EuropeanDigitalOption.h"
#include <stdexcept>

#pragma once

class EuropeanDigitalCallOption : public EuropeanDigitalOption {
public:
    EuropeanDigitalCallOption();
    EuropeanDigitalCallOption(double strike, double expiry);
    virtual ~EuropeanDigitalCallOption();

protected:
    optionType GetOptionType() override;

public:
    double payoff(double z) const override;
};

#endif

