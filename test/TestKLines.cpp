//
// Created by Vinay Manektalla on 20/07/2021.
//
#include <gtest/gtest.h>
#include <json/json.h>
#include <binance.h>

#include <model/KLines.h>

GTEST_TEST(KLine, create_kline)
{
    Json::Value result;

    binance::Server server;

    binance::Market market(server);

    // Klines / CandleStick
    BINANCE_ERR_CHECK(market.getKlines(result, "BTCUSDT", "1h", 0, 0, 10));
    ASSERT_NE(Json::nullValue, result.type());

    auto klines = model::KLines(result);

    ASSERT_NE(klines.getKLines().empty(), true);

    for (const auto& i : klines.getKLines())
    {
        ASSERT_NE(NULL, i.getOpenTime());
        ASSERT_GT(i.getOpenPrice(), 0);
    }
    LOGINFO(klines.getKLines().front());
}