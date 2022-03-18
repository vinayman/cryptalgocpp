#include "TestMarketDataInterface.h"

template <typename TParserParam>
void TestMarketDataInterface<TParserParam>::operator<<(const std::string &marketDataString) {
    inputParser.parseInputString(marketDataString);

    switch (inputParser.getType())
    {
        case InputParser<TParserParam>::Type::Quote:
            quoteHanndler(inputParser.getParams());
        case InputParser<TParserParam>::Type::Kline:
            klineHandler(inputParser.getParams());
        case InputParser<TParserParam>::Type::Trade:
            tradeHandler(inputParser.getParams());
    }
}

template <typename TParserParam>
void TestMarketDataInterface<TParserParam>::quoteHandler(const std::unordered_map<std::string, TParserParam>& params)
{
    auto quote = model::Quote(
        params.at("symbol"),
        params.at("bidPrice"),
        params.at("bidQty"),
        params.at("askPrice"),
        params.at("askQty")
    );
    auto quoteJson = quote.toJson();
    MarketData::getInstance(nullptr)->handleQuotes(quoteJson);
}

template <typename TParserParam>
void TestMarketDataInterface<TParserParam>::tradeHandler(const std::unordered_map<std::string, TParserParam>& params)
{
    auto trade = model::Trade(
        params.at("symbol"),
        std::chrono::system_clock::now(),
        std::chrono::system_clock::now(),
        params.at("price"),
        params.at("quantity"),
        buyOrderId,
        sellOrderId,
        tradeId
    );
    auto tradeJson = trade.toJson();
    MarketData::getInstance(nullptr)->handleTrades(tradeJson);
    buyOrderId++;
    sellOrderId++;
    tradeId++;
}

template <typename TParserParam>
void TestMarketDataInterface<TParserParam>::klineHandler(const std::unordered_map<std::string, TParserParam>& params)
{
    auto kline = model::KLine(
        params.at("symbol"),
        std::chrono::system_clock::now(),
        params.at("openPrice"),
        params.at("highPrice"),
        params.at("lowPrice"),
        params.at("closePrice"),
        params.at("volume"),
        std::chrono::system_clock::now(),
        params.at("quoteAssetVolume"),
        params.at("numOfTrades")
    );
    Json::Value klineJson = kline.toJson();
    MarketData::getInstance(nullptr)->handleKlines(klineJson);
}