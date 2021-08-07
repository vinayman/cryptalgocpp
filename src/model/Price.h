//
// Created by Vinay Manektalla on 20/07/2021.
//

#pragma once
#include <string>

#include "Symbol.h"
#include "Utils.h"

class Price
{
    Symbol symbol;
    double price;

public:
    explicit Price(std::string_view symbol_, const double& price_) :
        price(price_), symbol(Symbol(symbol_)) {};
    [[nodiscard]] const double& getPrice() const { return price; };
    [[nodiscard]] const Symbol& getSymbol() const { return symbol; };

    friend std::ostream& operator<<(std::ostream& os, const Price& p)
    {
        os << "\n\t" << LOG_VAR(p.getSymbol().getSymbol()) << '\n';
        os << '\t' << LOG_VAR(p.getPrice()) << '\n';
        return os;
    };
};
