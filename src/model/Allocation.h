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
    double _allocatedSize;
    double _targetAllocationSize;
    double _price;
    model::Symbol _symbol;
    Side _side;
    OrderAction _orderAction;

public:
    template <typename TSymbolStr>
    explicit Allocation(const TSymbolStr& symbolStr_, const double& price_, 
                        const double& targetAllocationSize_, const Side& side_, const OrderAction& orderAction_) :
            _symbol(symbolStr_)
            , _price(price_)
            , _targetAllocationSize(targetAllocationSize_)
            , _allocatedSize(0.0)
            , _side(side_)
            , _orderAction(orderAction_) {}
    
    model::Symbol& getSymbol() { return _symbol ; };
    double& getPrice() { return _price; };
    double& getAllocatedSize() { return _allocatedSize; };
    double& getTargetAllocationSize() { return _targetAllocationSize; };
    Side& getSide() { return _side; };
    OrderAction& getOrderAction() { return _orderAction; };
};

}