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
    Strategy(const std::shared_ptr<MarketData> marketData_);
    void evaluate();
    bool shouldEvaluate();
    void createAllocation();
    void onKline(const std::shared_ptr<Event>& event);
private:
    std::shared_ptr<MarketData> _marketData;
};


template<typename TOrdApi>
Strategy<TOrdApi>::Strategy(const std::shared_ptr<MarketData> marketData_) :
_marketData(marketData_)
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

template <typename TOrdApi>
void Strategy<TOrdApi>::onKline(const std::shared_ptr<Event>& event)
{
    std::shared_ptr<model::KLine> klinePtr = event->getKlinePtr();
    model::KLine kline = *klinePtr.get();
    LOGINFO(kline);
}
