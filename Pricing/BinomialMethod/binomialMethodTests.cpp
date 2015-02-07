#include <iostream>
#include <cmath>
#include <assert.h>

#include "BinomialMethodEuropean.h"
#include "BinomialMethodAmerican.h"
#include "BinomialMethodStrategies/CRRBinomialStrategy.h"
#include "BinomialMethodStrategies/JRBinomialStrategy.h"
#include "BinomialMethodStrategies/ModifiedCRRBinomialStrategy.h"
#include "BinomialMethodStrategies/EQPBinomialStrategy.h"
#include "BinomialMethodStrategies/TRGBinomialStrategy.h"
#include "../../Models/FinancialModels/EuropeanOption.h"
#include "../../Models/FinancialModels/AmericanOption.h"

void testBinomialStrategies() {
    std::cout << "Running Binomial Method Strategies Tests" << std::endl;
    
    CRRBinomialStrategy<double> strat(0.1, 0.1, 0.1);
    JRBinomialStrategy<double> s2(0.1, 0.1, 0.1);
    ModifiedCRRBinomialStrategy<double> s3(0.1, 0.1, 0.1, 0.1, 0.1, 50);
    EQPBinomialStrategy<double> s4(0.1, 0.1, 0.1);
    TRGBinomialStrategy<double> s5(0.1, 0.1, 0.1);
    
    std::cout << "Binomial Method Strategies Tests Complete" << std::endl;
}

void testBinomialMethod() {
    std::cout << "Running BinomialMethod Tests" << std::endl;
    
    EuropeanOption<double> *opt = new EuropeanOption<double>;
    opt->setStrike(150.0);
    opt->setIsCall(true);

    int number_steps = 10;
    double initial_underlying = 200.0;
    double delta = opt->expiry() / double(number_steps);
    double discount_rate = exp(-1 * opt->interestRate() * delta);

    CRRBinomialStrategy<double> *strategy = new CRRBinomialStrategy<double>(opt->interestRate(), opt->volatility(), delta);
    BinomialMethodEuropean<double> solver(discount_rate, strategy);
    solver.buildLattice(number_steps, initial_underlying);

    std::cout << "Price: " << solver.price(opt) << std::endl;
    
    delete opt;
    delete strategy;

    AmericanOption<double> *aOpt = new AmericanOption<double>;
    aOpt->setStrike(150.0);
    aOpt->setIsCall(true);

    CRRBinomialStrategy<double> *aStrategy = new CRRBinomialStrategy<double>(aOpt->interestRate(), aOpt->volatility(), delta);
    
    BinomialMethodAmerican<double> aSolver(discount_rate, aStrategy);
    aSolver.buildLattice(number_steps, initial_underlying);
    std::cout << "Price American: " << aSolver.price(aOpt) << std::endl;

    delete aOpt;
    delete aStrategy;

    std::cout << "BinomialMethod Tests Complete" << std::endl;
}
