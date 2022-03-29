//
// Created by Vinay Manektalla on 11/08/2021.
//

#pragma once
#include <dlfcn.h>
#include <thread>
#include <functional>

#include "Utils.h"
#include "Config.h"
#include "strategy/Strategy.h"
#include "strategy/SimpleStrategy.h"

template <typename TMarketData, typename TOrdApi>
class Factory {
private:
    void subscribeMarketData();
    std::shared_ptr<Config> _config = nullptr;
    std::shared_ptr<TMarketData> _marketData = nullptr;
    std::shared_ptr<TOrdApi> _orderInterface = nullptr;
    std::shared_ptr<Strategy<TOrdApi>> _strategy = nullptr;
    std::thread _marketDataThread;
    using factoryMethod_t = std::shared_ptr<Strategy<TOrdApi>>(*)(std::shared_ptr<TMarketData>, std::shared_ptr<TOrdApi>);
    void* _handle;
public:
    explicit Factory(const std::shared_ptr<Config>& config);
    const std::shared_ptr<Strategy<TOrdApi>>& getStrategy() const { return _strategy; };
    const std::shared_ptr<TMarketData>& getMarketData() const { return _marketData; };
    ~Factory();
    factoryMethod_t loadFactoryMethod();
    void initStrategy();
};

template<typename TMarketData, typename TOrdApi>
Factory<TMarketData, TOrdApi>::Factory(const std::shared_ptr<Config>& config) :
_config(config)
, _marketData(std::static_pointer_cast<TMarketData>(TMarketData::getInstance(config)))
, _strategy(nullptr)
, _marketDataThread(&Factory<TMarketData, TOrdApi>::subscribeMarketData, this)
, _orderInterface(std::make_shared<TOrdApi>(std::string{""}, std::string{""}))
{}

template<typename TMarketData, typename TOrdApi>
void Factory<TMarketData, TOrdApi>::subscribeMarketData()
{
    _marketData->subscribe();
}

template<typename TMarketData, typename TOrdApi>
Factory<TMarketData, TOrdApi>::~Factory()
{
    _marketDataThread.join();
    _marketData = nullptr;
    dlclose(_handle);
}

template<typename TMarketData, typename TOrdApi>
typename Factory<TMarketData, TOrdApi>::factoryMethod_t
Factory<TMarketData, TOrdApi>::loadFactoryMethod() {
    std::string factoryMethodName = _config->get("strategy");
    std::string lib = _config->get("strategy_library");
    std::stringstream info;
    PLOG_DEBUG << "Loading strategy ... " << LOG_VAR(lib) << LOG_VAR(factoryMethodName);
    _handle = dlopen(lib.c_str(), RTLD_LAZY);
    if (!_handle) {
        std::stringstream message;
        message << "Couldn't load " << LOG_VAR(lib) << LOG_VAR(dlerror());
        PLOG_DEBUG << message.str();
        throw std::runtime_error(message.str());
    }

    // load the symbol
    factoryMethod_t factoryFunc;
    factoryFunc = (factoryMethod_t)dlsym(_handle, factoryMethodName.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        dlclose(_handle);
        std::stringstream msg;
        msg << "Couln't load symbol " << LOG_VAR(factoryMethodName) << LOG_VAR(dlsym_error);
        PLOG_DEBUG << msg.str();
        throw std::runtime_error(msg.str());
    }

    return factoryFunc;

}

template<typename TMarketData, typename TOrdApi>
void Factory<TMarketData, TOrdApi>::initStrategy() {

    Factory<TMarketData, TOrdApi>::factoryMethod_t factoryMethod = loadFactoryMethod();
    std::shared_ptr<Strategy<TOrdApi>> strategy = factoryMethod(_marketData, _orderInterface);
    _strategy = strategy;
}
