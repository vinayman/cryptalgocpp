//
// Created by Vinay Manektalla on 06/08/2021.
//

#pragma once
#include "Symbol.h"

namespace model {

enum class Side {
    Buy, Sell
};

enum class OrderAction {
    New, Amend, Cancel
};

class Allocation {
private:
    double _size;
    double _price;
    model::Symbol _symbol;
    Side _side;
    OrderAction _orderAction;

public:
    template <typename TSymbolStr>
    explicit Allocation(const TSymbolStr& symbolStr_, const double& price_, 
                        const double& size_, const Side& side_, const OrderAction& orderAction_) :
            _symbol(symbolStr_)
            , _price(price_)
            , _size(size_) 
            , _side(side_)
            , _orderAction(orderAction_) {}
    
    model::Symbol& getSymbol() { return _symbol ; };
    double& getPrice() { return _price; };
    double& getSize() { return _size; };
    Side& getSide() { return _side; };
    OrderAction& getOrderAction() { return _orderAction; };
};

}