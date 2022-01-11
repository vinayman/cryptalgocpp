//
// Created by Vinay Manektalla on 11/08/2021.
//

#pragma once

#include <mutex>
#include <queue>
#include <iostream>

#include <boost/exception/exception.hpp>

#include "binance_websocket.h"

#include "Utils.h"
#include "Config.h"
#include "Event.h"
#include "model/Symbol.h"
#include "model/Quote.h"
#include "model/KLines.h"

using namespace binance;

class QueueArrange {
public:
    bool operator()(const std::shared_ptr<Event> &this_, const std::shared_ptr<Event> &that_) {
        return this_->timeStamp() < that_->timeStamp();
    }
};

class MarketData {
private:
    static std::mutex _mutex;
    std::shared_ptr<Config> _config = nullptr;
    model::Symbol _symbol;
    std::string _mdSubscriptionPeriod{};
    std::priority_queue<std::shared_ptr<Event>, std::vector<std::shared_ptr<Event>>, QueueArrange> _eventBuffer;

    MarketData() :
            _symbol(model::Symbol(std::string{"BNBUSDT"}))
            , _mdSubscriptionPeriod("1m") {}

    static int handleKlines(Json::Value& json_result);
    static int handlePrice(const Json::Value& json_result);
    static int handleQuotes(Json::Value& json_result);
    model::Symbol getSymbol() const { return _symbol ; };
    
    template<typename T>
    void update(const std::shared_ptr<T>& data_);

public:
    inline static std::shared_ptr<MarketData> _marketDataInstance = nullptr;
    [[noreturn]] void subscribe();
    void init(const std::shared_ptr<Config> &config);

    static std::shared_ptr<MarketData> getInstance(const std::shared_ptr<Config> &config);

    std::shared_ptr<Event> read();

    MarketData(MarketData const&) = delete;
    void operator=(MarketData const&)  = delete;

};
