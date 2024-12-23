#ifndef EUROPEANVANILLAOPTION_H
#define EUROPEANVANILLAOPTION_H

#include "Option.h"
#include <stdexcept>

#pragma once

class EuropeanVanillaOption : public Option {
private:
    double _strike;
protected:
    enum class optionType { call, put };
    virtual optionType GetOptionType();
    double getStrike()const;
    friend class BlackScholesPricer;

public:
    EuropeanVanillaOption();
    EuropeanVanillaOption(double, double);

    friend class BlackScholesPricer;
    virtual ~EuropeanVanillaOption();
};

#endif

