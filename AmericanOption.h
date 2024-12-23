#ifndef AMERICANOPTION_H
#define AMERICANOPTION_H
#include "Option.h"
#pragma once




class AmericanOption : public Option {
private:
    double _strike;

public:
    AmericanOption();
    enum class optionType { call, put };
    AmericanOption(double expiry, double strike);
    virtual  optionType GetOptionType() const = 0;
    double getStrike() const;
    bool isAmericanOption() const override;
    virtual ~AmericanOption();

};

#endif