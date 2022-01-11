//
// Created by Vinay Manektalla on 11/08/2021.
//

#include "MarketData.h"

std::mutex MarketData::_mutex;


std::shared_ptr<MarketData> MarketData::getInstance(const std::shared_ptr<Config> &config)
{
    UniqueGuard lock_(_mutex);
    if (config.get() == nullptr)
    {
        if (_marketDataInstance.get() == nullptr)
            BOOST_THROW_EXCEPTION(std::out_of_range("No MD Instance"));
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
        _mdSubscriptionPeriod = config->get("subscription_period");
    }
    _marketDataInstance = std::shared_ptr<MarketData>(this);
}

[[noreturn]] void MarketData::subscribe()
{
    while (true)
    {
        std::string kLineSubscriptionString{
            "/ws/" + _symbol.getWebsocketSymbol() + "@kline_" + _mdSubscriptionPeriod
        };
        std::string quoteSubscriptionString{"/ws/" + _symbol.getWebsocketSymbol() + "@bookTicker"};
        binance::Websocket::init();
        LOGINFO("Subscribing to:", kLineSubscriptionString);
        binance::Websocket::connect_endpoint(handleKlines, kLineSubscriptionString.c_str());
        LOGINFO("Subscribing to:", quoteSubscriptionString);
        binance::Websocket::connect_endpoint(handleQuotes, quoteSubscriptionString.c_str());
        binance::Websocket::enter_event_loop();
        LOGINFO("error exiting enter_event_loop and we will try again after 5sec");
        sleep(5);
    }
}

template<typename T>
void MarketData::update(const std::shared_ptr<T>& data_) {
    Guard lockGuard_(_mutex);
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

int MarketData::handleQuotes(Json::Value& json_result)
{
    auto quote = model::Quote(json_result, true);
    MarketData::getInstance(nullptr)->update(std::make_shared<model::Quote>(quote));
    return 0;
}

std::shared_ptr<Event> MarketData::read() {
    Guard lockGuard_(_mutex);
    auto event = _eventBuffer.empty() ? nullptr : _eventBuffer.top();
    if (event) {
        _eventBuffer.pop();
    }
    return event;
}
