#pragma once

#include <dlfcn.h>
#include <memory>

#include "Utils.h"
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
    explicit TestEnv(const std::map<std::string, std::string>& testConfig);
    ~TestEnv() {};
    void operator << (const std::string& value_);
    void operator >> (const std::string& value_);
    std::unique_ptr<Factory<TestMarketDataInterface, OrderInterface>>& getFactory() { return _factory; }
};