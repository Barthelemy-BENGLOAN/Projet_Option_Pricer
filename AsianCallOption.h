#ifndef ASIANCALLOPTION_H
#define ASIANCALLOPTION_H

#include "AsianOption.h"

#pragma once

class AsianCallOption : public AsianOption {
public:
    AsianCallOption();
    AsianCallOption(const std::vector<double>&, double);
    double payoff(double) const override;
    optionType GetOptionType() const override;
    ~AsianCallOption();
};

#endif
