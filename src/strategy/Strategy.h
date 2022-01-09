//
// Created by Vinay Manektalla on 30/9/21.
//

#pragma once

#include <iostream>

#include "MarketData.h"
#include "Event.h"
#include "../Utils.h"
#include "model/KLines.h"

template <typename TOrdApi>
class Strategy {
public:
    Strategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_);
    void evaluate();
    bool shouldEvaluate();
    void createAllocation();
    virtual void onKline(const std::shared_ptr<Event>& event) = 0;
private:
    std::shared_ptr<MarketData> _marketData;
    std::shared_ptr<TOrdApi> _orderInterface;
};


template<typename TOrdApi>
Strategy<TOrdApi>::Strategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_) :
_marketData(marketData_)
, _orderInterface(orderInterface_)
{}

template<typename TOrdApi>
void Strategy<TOrdApi>::evaluate() {
    auto event = _marketData->read();
    if (event)
    {
        onKline(event);
    }
}

template<typename TOrdApi>
bool Strategy<TOrdApi>::shouldEvaluate() {
    return true;
}

template<typename TOrdApi>
void Strategy<TOrdApi>::createAllocation() {

}
