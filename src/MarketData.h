//
// Created by Vinay Manektalla on 11/08/2021.
//

#pragma once
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <iostream>
#include <condition_variable>

#include <boost/exception/exception.hpp>
#include "binance_websocket.h"
#include <plog/Log.h>

#include "Utils.h"
#include "MDQueue.h"
#include "Config.h"
#include "Event.h"
#include "model/Symbol.h"
#include "model/Quote.h"
#include "model/KLines.h"
#include "model/Trade.h"

using namespace binance;

class MarketData {
protected:
    std::shared_ptr<Config> _config = nullptr;
    model::Symbol _symbol;
    std::string _mdSubscriptionPeriod{};
    PriorityQueue _eventBuffer;
    model::Symbol getSymbol() const { return _symbol ; };
    
    template<typename T>
    void update(const std::shared_ptr<T>& data_);

    static int handleKlines(Json::Value& json_result);
    static int handlePrice(const Json::Value& json_result);
    static int handleQuotes(Json::Value& json_result);
    static int handleTrades(Json::Value& json_result);

    explicit MarketData() :
            _symbol(model::Symbol(std::string{"BNBUSDT"}))
            , _mdSubscriptionPeriod("1m")
            , _eventBuffer(PriorityQueue()) {}

public:
    inline static std::shared_ptr<MarketData> _marketDataInstance = nullptr;

    static std::shared_ptr<MarketData> getInstance(const std::shared_ptr<Config> &config);
    void init(const std::shared_ptr<Config> &config);

    std::shared_ptr<Event> read();

    MarketData(MarketData const&) = delete;
    void operator=(MarketData const&)  = delete;
};
