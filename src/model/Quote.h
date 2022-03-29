//
// Created by Vinay Manektalla on 21/07/2021.
//

#pragma once
#include <string>
#include <string_view>

#include <json/json.h>

#include "../Utils.h"
#include "MarketDataObject.h"
#include "Symbol.h"

namespace model {

class Quote: public MarketDataObject
{
private:
    Symbol _symbol;
    double _bidPrice;
    double _bidQty;
    double _askPrice;
    double _askQty;
public:
    explicit Quote(const std::string_view symbol_, const double& bidPrice_,
                const double& bidQty_, const double& askPrice_, const double& askQty_) :
            _symbol(Symbol(symbol_))
            , _bidPrice(bidPrice_)
            , _bidQty(bidQty_)
            , _askPrice(askPrice_)
            , _askQty(askQty_) {};

    explicit Quote(const Json::Value& jsonValue, const bool& wsData);

    Symbol getSymbol() const { return _symbol ; };
    double getBidPrice() const { return _bidPrice ; };
    double getBidQty() const { return _bidQty ; };
    double getAskPrice() const { return _askPrice ; };
    double getAskQty() const { return _askQty ; };
    Json::Value toJson();

    friend std::ostream& operator<<(std::ostream& os, const Quote& q)
    {
        os << "\n\t" << LOG_VAR(q.getSymbol()) << '\n';
        os << "\t" << LOG_VAR(q.getBidPrice()) << '\n';
        os << '\t' << LOG_VAR(q.getBidQty()) << '\n';
        os << '\t' << LOG_VAR(q.getAskPrice()) << '\n';
        os << '\t' << LOG_VAR(q.getAskQty()) << '\n';
        return os;
    };
};

}