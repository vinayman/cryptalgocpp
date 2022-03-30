#include "TestEnv.h"

TestEnv::TestEnv(const std::unordered_map<std::string, std::string>& testConfig) :
_config(std::make_shared<Config>(testConfig))
, _factory(nullptr) 
{
    _factory = std::make_unique<Factory<TestMarketDataInterface, OrderInterface>>(_config);
    _factory->initStrategy();
}

void TestEnv::operator << (const std::string& inputString)
{
    *_factory->getMarketData() << inputString;
    _factory->getStrategy()->evaluate();
}

void TestEnv::operator >> (const std::string& inputString)
{

}