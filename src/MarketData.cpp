//
// Created by Vinay Manektalla on 11/08/2021.
//

#include "MarketData.h"

MarketData::MarketData(const std::shared_ptr <Config>& config) :
    _config(config),
    _symbol(model::Symbol(std::string{"BNBUSDT"})),
    _klineSubscriptionPeriod("1m")
{
    if (_config->configParamExists("symbol")) {
        _symbol = model::Symbol(_config->get("symbol"));
    }
    if (_config->configParamExists("subscription_period")) {
        _klineSubscriptionPeriod = _config->get("subscription_period");
    }
}

[[noreturn]] void MarketData::subscribe()
{
    while (true)
    {
        std::string subscriptionString{
            "/ws/" + _symbol.getWebsocketSymbol() + "@kline_" + _klineSubscriptionPeriod
        };
        LOGINFO("Subscribing to:", subscriptionString);
        binance::Websocket::init();
        binance::Websocket::connect_endpoint(handleKlines, subscriptionString.c_str());
        binance::Websocket::enter_event_loop();
        LOGINFO("error exiting enter_event_loop and we will try again after 5sec");
        sleep(5);
    }
}

int MarketData::handleKlines(Json::Value& json_result)
{
    LOGINFO(json_result);
    if (json_result["e"].asString() == "kline")
    {
        auto kline = model::KLine(json_result, true);
        LOGINFO(kline);
        LOGINFO(kline.toJson());
    }
    return 0;
}

int MarketData::handlePrice(const Json::Value& json_result)
{
    return 0;
}

int MarketData::handleQuotes(const Json::Value& json_result)
{
    return 0;
}
