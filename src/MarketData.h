//
// Created by Vinay Manektalla on 11/08/2021.
//

#pragma once

#include "binance_websocket.h"

#include "Config.h"
#include "model/Symbol.h"
#include "model/KLines.h"

class MarketData {
public:
    explicit MarketData(const std::shared_ptr<Config> &config);

    [[noreturn]] void subscribe();
    static int handleKlines(Json::Value& json_result);
    int handlePrice(const Json::Value& json_result);
    int handleQuotes(const Json::Value& json_result);

private:
    std::shared_ptr<Config> _config;
    model::Symbol _symbol;
    std::string _klineSubscriptionPeriod{};
};