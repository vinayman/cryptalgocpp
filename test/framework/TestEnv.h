#pragma once

#include <memory>

#include "Factory.h"
#include "OrderInterface.h"
#include "Config.h"

#include "TestMarketDataInterface.h"

class TestEnv
{
private:
    std::shared_ptr<Config> _config;
    std::unique_ptr<Factory<TestMarketDataInterface, OrderInterface>> _factory;
public:
    explicit TestEnv(const std::unordered_map<std::string, std::string>& testConfig);
    void operator << (const std::string& value_);
    void operator >> (const std::string& value_);
    std::unique_ptr<Factory<TestMarketDataInterface, OrderInterface>>& getFactory() { return _factory; }
};