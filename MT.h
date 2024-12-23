#ifndef MT_H
#define MT_H

#include <random>

class MT {
private:

    MT(const MT&) = delete;
    MT& operator=(const MT&) = delete;

    static MT& seed();
    std::mt19937 generator;

public:
    MT();
    ~MT();
    static double rand_unif();
    static double rand_norm();
};

#endif
