//
// Created by Vinay Manektalla on 21/07/2021.
//

#include <gtest/gtest.h>

#include <Symbol.h>

GTEST_TEST(Symbol, test_symbol)
{
    auto poeBtc = model::Symbol(std::string_view {"POEBTC"});
    ASSERT_TRUE(poeBtc.isCryptoPair());
    ASSERT_FALSE(poeBtc.isStablePair());

    auto btcUsdt = model::Symbol(std::string_view {"BTCUSDT"});
    ASSERT_TRUE(btcUsdt.isStablePair());
    ASSERT_FALSE(btcUsdt.isCryptoPair());
}