//MAIN 1,2,3 JIANG PU

// MAIN VARIANCE REDUCTION ANTITHETIC VARIABLES

//MAIN STOCHASTIC MODEL (HESTON)

#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "CRRPricer.h"
#include "HestonMCPricer.h"

int main() {
    
    //MAIN 1
    /*
    double S0(100.), K(101.), T(5), r(0.01), sigma(0.1);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 10000; i++) { // time increment=5
        fixing_dates.push_back(0.1 * i);
    }
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

    std::vector<double> ci;
    BlackScholesMCPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
        do {
            //int NbPaths=10000; //ajouter la fonction qui genere un N aleatoire ; 1000 -> 50000 ; 10000 
            pricer->generate(10);//Nb Paths in gthe MC method is not deterministic
            ci = pricer->confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);
        std::cout << "nb samples: " << pricer->getNbPaths() << std::endl;
        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;
    }
    */


 
    std::cout<<"---------------------------------------------------------------------------------------------------------"<<std::endl;

    //MAIN 2
    
    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 5; i++) {
        fixing_dates.push_back(0.1 * i);
    }
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

    std::vector<double> ci;
    BlackScholesMCPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma); 
        do {
            pricer->generate(10);
            ci = pricer->confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);
        std::cout << "nb samples: " << pricer->getNbPaths() << std::endl;
        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;
    }
    

    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;

    //MAIN 3
    /*
    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));
    opt_ptrs.push_back(new AmericanCallOption(T, K));
    opt_ptrs.push_back(new AmericanPutOption(T, K));

    CRRPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new CRRPricer(opt_ptr, 150, S0, r, sigma);

        pricer->compute();

        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;

    }
    */

    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;

    //MAIN VARIANCE REDUCTION (ANTITHETIC VARIABLES)
    /*
    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    std::vector<Option*> myOptions;
    myOptions.push_back(new CallOption(T, K));
    myOptions.push_back(new PutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 5; i++) {
        fixing_dates.push_back(0.1 * i); 
    }
    myOptions.push_back(new AsianCallOption(fixing_dates, K));

    for (auto& opt : myOptions) {
        std::cout << "=========================================\n";
        std::cout << "Option: " << typeid(*opt).name() << std::endl;

        //no antithetic
        BlackScholesMCPricer pricer_no_anti(opt, S0, r, sigma);
        std::vector<double> ci;
        do {
            pricer_no_anti.generate(10);     
            ci = pricer_no_anti.confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);     

        double price_no_anti = pricer_no_anti();
        std::cout << "[Sans antithetique]\n";
        std::cout << "  Nb samples   : " << pricer_no_anti.getNbPaths() << "\n";
        std::cout << "  Price        : " << price_no_anti << "\n";
        std::cout << "  IC 95%       : [" << ci[0] << ", " << ci[1] << "]\n\n";

        //with antithetic
        BlackScholesMCPricer pricer_anti(opt, S0, r, sigma, true);
        do {
            pricer_anti.generate(10);
            ci = pricer_anti.confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);

        double price_anti = pricer_anti();
        std::cout << "[Avec antithetique]\n";
        std::cout << "  Nb samples   : " << pricer_anti.getNbPaths() << "\n";
        std::cout << "  Price        : " << price_anti << "\n";
        std::cout << "  IC 95%       : [" << ci[0] << ", " << ci[1] << "]\n";
        std::cout << "=========================================\n\n";

        delete opt;
    }
    */
    std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl;

    //MAIN STOCHASTIC MODEL (HESTON)
    /*
    double T(1.0), K(100.0), S0(100.0), r(0.02), kappa(2.0), theta(0.04), xi(0.3), rho(-0.7), v0(0.04), sigma(0.02);
    Option* myOption = new CallOption(T, K);

    {
        HestonMCPricer pricerH(myOption, S0, r, kappa, theta, xi, rho, v0);
        int nb_paths = 100000;
        int nSteps = 100;
        pricerH.generate(nb_paths, nSteps);

        double priceH = pricerH.price();
        std::vector<double> ciH = pricerH.confidenceInterval();

        std::cout << "===== Heston Model Simulation =====" << std::endl;
        std::cout << "Heston price       = " << priceH << std::endl;
        std::cout << "Heston 95% CI      = [" << ciH[0] << ", " << ciH[1] << "]" << std::endl;
        std::cout << std::endl;
    }

     //comparaison with constant volatility
    {
        BlackScholesMCPricer pricerBS(myOption, S0, r, sigma );
        std::vector<double> ciBS;
        do {
            pricerBS.generate(10000); 
            ciBS = pricerBS.confidenceInterval();
        } while ((ciBS[1] - ciBS[0]) > 0.01); 
        double priceBS = pricerBS(); 
        std::vector<double> finalCI = pricerBS.confidenceInterval();

        std::cout << "===== Black–Scholes MC =====" << std::endl;
        std::cout << "Black–Scholes price = " << priceBS << std::endl;
        std::cout << "BS 95% CI           = [" << finalCI[0] << ", " << finalCI[1] << "]" << std::endl;
        std::cout << std::endl;
    }
    delete myOption;
    */

}

















