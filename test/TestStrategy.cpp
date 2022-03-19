#include "framework/TestEnv.h"

#include "gtest/gtest.h"

GTEST_TEST(Strategy, test_strategy)
{
    auto env = TestEnv(
        {
            {"name", "cryptalgocpp"},
            {"symbol", "BNBUSDT"},
            {"subscription_period", "1m"},
            {"strategy_library", "/workspaces/cryptalgocpp/build/src/strategy/libcryptalgo_strategies.so"},
            {"strategy", "RegisterSimpleStrategy"},
            {"log_directory", "/workspaces/cryptalgocpp/cryptalgocpp.log"},
        }
    );
    env << "TYPE=QUOTE symbol=BNBUSDT bidPrice=300.1 bidQty=1000.5 askPrice=301.1 askQty=1000.1";
    auto inputString = env.getFactory()->getMarketData()->inputParser.getInputString();
    ASSERT_EQ(std::string{"TYPE=QUOTE symbol=BNBUSDT bidPrice=300.1 bidQty=1000.5 askPrice=301.1 askQty=1000.1"}, inputString);
}