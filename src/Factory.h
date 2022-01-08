//
// Created by Vinay Manektalla on 11/08/2021.
//

#pragma once
#include <thread>
#include <functional>

#include "Config.h"
#include "strategy/Strategy.h"
#include "OrderInterface.h"

template <typename TMarketData>
class Factory {
public:
    explicit Factory(const std::shared_ptr<Config>& config);
    Strategy<OrderInterface>& getStrategy() {return _strategy; };
    ~Factory();
private:
    void subscribeMarketData();
    std::shared_ptr<TMarketData> _marketData;
    Strategy<OrderInterface> _strategy;
    std::thread _marketDataThread;
};

template<typename TMarketData>
Factory<TMarketData>::Factory(const std::shared_ptr<Config>& config) :
_marketData(TMarketData::getInstance(config))
, _strategy(Strategy<OrderInterface>(_marketData))
, _marketDataThread(&Factory<TMarketData>::subscribeMarketData, this)
{ }

template<typename TMarketData>
void Factory<TMarketData>::subscribeMarketData()
{
    _marketData->subscribe();
}

template<typename TMarketData>
Factory<TMarketData>::~Factory()
{
    _marketDataThread.join();
    _marketData = nullptr;
}
