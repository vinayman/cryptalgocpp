#include "TestMarketDataInterface.h"

void TestMarketDataInterface::operator<<(const std::string &marketDataString) {
    inputParser.parseInputString(marketDataString);

    switch (inputParser.getType())
    {
        case InputParser::Type::Quote:
            quoteHandler(inputParser.getParams());
        case InputParser::Type::Kline:
            klineHandler(inputParser.getParams());
        case InputParser::Type::Trade:
            tradeHandler(inputParser.getParams());
    }
}

void TestMarketDataInterface::quoteHandler(const std::unordered_map<std::string, std::string>& params)
{
    auto quote = model::Quote(
        params.at("symbol"),
        std::stod(params.at("bidPrice")),
        std::stod(params.at("bidQty")),
        std::stod(params.at("askPrice")),
        std::stod(params.at("askQty"))
    );
    auto quoteJson = quote.toJson();
    MarketData::getInstance(nullptr)->handleQuotes(quoteJson);
}

void TestMarketDataInterface::tradeHandler(const std::unordered_map<std::string, std::string>& params)
{
    auto trade = model::Trade(
        params.at("symbol"),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::stod(params.at("price")),
        std::stod(params.at("quantity")),
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

void TestMarketDataInterface::klineHandler(const std::unordered_map<std::string, std::string>& params)
{
    auto kline = model::KLine(
        params.at("symbol"),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::stod(params.at("openPrice")),
        std::stod(params.at("highPrice")),
        std::stod(params.at("lowPrice")),
        std::stod(params.at("closePrice")),
        std::stod(params.at("volume")),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::stod(params.at("quoteAssetVolume")),
        std::stoi(params.at("numOfTrades"))
    );
    Json::Value klineJson = kline.toJson();
    MarketData::getInstance(nullptr)->handleKlines(klineJson);
}