#include "CRRPricer.h"
#include <cmath>
#include <stdexcept>

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
    : option(option), N(depth), S_0(asset_price), U(up), D(down), R(interest_rate) {
    if (!(down < interest_rate && interest_rate < up)) {
        throw std::invalid_argument("ERROR : Arbitrage is possible");
    }
    else if (option->isAsianOption())
    {
        throw std::invalid_argument("ERROR : Asian Option don't take the CRR pricer");
    }
    else if (option->isAmericanOption())
    {
        exerciseTree.setDepth(N);
    }
}
bool CRRPricer::getExercise(int i, int j) {
    compute();
    return exerciseTree.getNode(i, j);
}

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility)
    : option(option), N(depth), S_0(asset_price)
{
    double h = option->getExpiry() / N;
    U = std::exp((r + std::pow(volatility, 2) / 2) * h + volatility * std::sqrt(h)) - 1;
    D = std::exp((r + std::pow(volatility, 2) / 2) * h - volatility * std::sqrt(h)) - 1;
    R = std::exp(r * h) - 1;

    if (!(D < R && R < U)) {
        throw std::invalid_argument("ERROR : Arbitrage is possible");
    }
    else if (option->isAsianOption())
    {
        throw std::invalid_argument("ERROR : Asian Option don't take the CRR pricer");
    }
    else if (option->isAmericanOption()) {
        exerciseTree.setDepth(N);
    }

}

void CRRPricer::compute() {
    double q = (R - D) / (U - D);
    tree.setDepth(N);
    exerciseTree.setDepth(N);
    double up = U + 1;
    double down = D + 1;
    std::vector<double> stock_prices(N + 1);
    double up_factor = 1.0;
    double down_factor = std::pow(down, N);

    for (int i = 0; i <= N; ++i) {
        stock_prices[i] = S_0 * up_factor * down_factor;
        tree.setNode(N, i, option->payoff(stock_prices[i]));
        up_factor *= up;
        down_factor /= down;
    }
    if (option->isAmericanOption()) {
        for (int i = N - 1; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                double up_factor = std::pow(U + 1, j);
                double down_factor = std::pow(D + 1, i - j);
                double stock_price = S_0 * up_factor * down_factor;
                double continuation_value = (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + R);
                double payoff_value = option->payoff(stock_price);
                double node_value = std::max(continuation_value, payoff_value);
                tree.setNode(i, j, node_value);
                exerciseTree.setNode(i, j, payoff_value >= continuation_value);

            }
        }
    }
    else {
        for (int i = N - 1; i >= 0; --i) {
            for (int j = 0; j <= i; ++j) {
                double expected_value = (q * tree.getNode(i + 1, j + 1) + (1 - q) * tree.getNode(i + 1, j)) / (1 + R);
                tree.setNode(i, j, expected_value);
            }
        }
    }
}


double CRRPricer::get(int n, int i) {
    compute();
    return tree.getNode(n, i);
}

double CRRPricer::operator()(bool closed_form) {
    if (closed_form) {
        double q = (R - D) / (U - D);
        double H0_0 = 0;

        for (int i = 0; i <= N; i++) {
            double up_factor = std::pow(U + 1, i);
            double down_factor = std::pow(D + 1, N - i);
            double stock_price = S_0 * up_factor * down_factor;
            H0_0 += tgamma(N + 1) * pow(q, i) * pow(1 - q, N - i) * option->payoff(stock_price) / (tgamma(i + 1) * tgamma(N - i + 1));
        }

        H0_0 = H0_0 * (1 / pow(1 + R, N));
        return H0_0;
    }
    else {
        compute();

        return get(0, 0);
    }
}


CRRPricer::~CRRPricer() {}