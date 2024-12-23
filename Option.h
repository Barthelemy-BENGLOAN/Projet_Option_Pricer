#ifndef OPTION_H
#define OPTION_H
#include <vector>
#pragma once

class Option
{
private:
    double _expiry;

public:
    Option();
    Option(double);
    virtual double payoff(double) const = 0;

    double getExpiry() const;
    virtual double payoffPath(std::vector<double>& prices) const;
    virtual bool isAsianOption() const { return false; };
    virtual bool isAmericanOption() const { return false; };
    virtual ~Option();
};

#endif

