#ifndef ASIANPUTOPTION_H
#define ASIANPUTOPTION_H

#include "AsianOption.h"

#pragma once

class AsianPutOption : public AsianOption {
public:
    AsianPutOption();
    AsianPutOption(const std::vector<double>&, double);
    double payoff(double) const override;
    optionType GetOptionType() const override;
    ~AsianPutOption();
};

#endif

