//
// Created by Vinay Manektalla on 11/08/2021.
//

#include "MarketData.h"

std::mutex MarketData::_mutex;

std::shared_ptr<MarketData> MarketData::getInstance(const std::shared_ptr<Config> &config)
{
    UniqueGuard lock_(_mutex);
    if (_marketDataInstance.get() == nullptr)
    {        
        static std::shared_ptr<MarketData> marketDataPtr(new MarketData());
        marketDataPtr->init(config);
        _marketDataInstance = marketDataPtr;
        return _marketDataInstance;
    }
    if (config.get() == nullptr)
    {
        if (_marketDataInstance.get() == nullptr)
            BOOST_THROW_EXCEPTION(std::out_of_range("No MD Instance"));
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

int MarketData::handleTrades(Json::Value& json_result)
{
    auto trade = model::Trade(json_result, true);
    MarketData::getInstance(nullptr)->update(std::make_shared<model::Trade>(trade));
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
