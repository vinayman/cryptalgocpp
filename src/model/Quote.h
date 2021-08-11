//
// Created by Vinay Manektalla on 21/07/2021.
//

#pragma once
#include <string>

#include "../Utils.h"
#include "Symbol.h"

namespace model {
    class Quote
    {
        Symbol symbol;
        double bidPrice;
        double bidQty;
        double askPrice;
        double askQty;

        explicit Quote(const std::string_view symbol_, const double& bidPrice_,
                       const double& bidQty_, const double& askPrice_, const double& askQty_) :
                symbol(Symbol(symbol_)), bidPrice(bidPrice_), bidQty(bidQty_),
                askPrice(askPrice_), askQty(askQty_) {};
    };
}