//
// Created by Vinay Manektalla on 20/07/2021.
//
#include <gtest/gtest.h>
#include <json/json.h>
#include <binance.h>
#include "Utils.h"
#include "model/Price.h"


GTEST_TEST(Price, create_price)
{
    Json::Value result;

    binance::Server server;

    binance::Market market(server);

    // Klines / CandleStick
    std::string symbol_{"BTCUSDT"};
    double price_;
    BINANCE_ERR_CHECK(market.getPrice(symbol_.c_str(), price_));

    auto price = Price(symbol_, price_);

    LOGINFO(price);

    ASSERT_NE(std::string {}, price.getSymbol().getSymbol());
    ASSERT_GT(price.getPrice(), 0.0);
}