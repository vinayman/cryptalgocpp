//
// Created by Vinay Manektalla on 11/08/2021.
//

#include "MarketData.h"

std::mutex MarketData::_mutex;


std::shared_ptr<MarketData> MarketData::getInstance(const std::shared_ptr<Config> &config)
{
    if (config.get() == nullptr)
    {
        return _marketDataInstance;
    }
    if (_marketDataInstance.get() == nullptr)
    {        
        static std::shared_ptr<MarketData> marketDataPtr(new MarketData());
        marketDataPtr->init(config);
        _marketDataInstance = marketDataPtr;
        return _marketDataInstance;
    }
    return _marketDataInstance;
}

void MarketData::init(const std::shared_ptr<Config> &config)
{
    if (config->configParamExists("symbol")) {
        _symbol = model::Symbol(config->get("symbol"));
    }
    if (config->configParamExists("subscription_period")) {
        _klineSubscriptionPeriod = config->get("subscription_period");
    }
    _marketDataInstance = std::shared_ptr<MarketData>(this);
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

template<typename T>
void MarketData::update(const std::shared_ptr<T>& data_) {
    std::lock_guard<std::mutex> lockGuard_(_mutex);
    _eventBuffer.push(std::make_shared<Event>(data_));
}

int MarketData::handleKlines(Json::Value& json_result)
{
    if (json_result["e"].asString() == "kline")
    {
        auto kline = model::KLine(json_result, true);
        MarketData::getInstance(nullptr)->update(std::make_shared<model::KLine>(kline));
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

std::shared_ptr<Event> MarketData::read() {
    std::lock_guard<std::mutex> lockGuard_(_mutex);
    auto event = _eventBuffer.empty() ? nullptr : _eventBuffer.top();
    if (event) {
        _eventBuffer.pop();
    }
    return event;
}
