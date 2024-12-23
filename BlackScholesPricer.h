#ifndef BLACKSCHOLESPRICER_H
#define BLACKSCHOLESPRICER_H
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"
#pragma once

class BlackScholesPricer
{
public:
    BlackScholesPricer(Option*, double, double, double);

    double operator()();
    double delta();
    ~BlackScholesPricer();

protected:
    Option* Option_;
    double Asset_price_;
    double Interest_rate_;
    double Volatility_;



};

#endif