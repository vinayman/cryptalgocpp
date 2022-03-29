#include "TestMarketDataInterface.h"


std::shared_ptr<TestMarketDataInterface> TestMarketDataInterface::getInstance(const std::shared_ptr<Config> &config)
{
    UniqueGuard lock_(MarketData::_mutex);
    if (_marketDataInstance.get() == nullptr)
    {
        static std::shared_ptr<TestMarketDataInterface> marketDataPtr(new TestMarketDataInterface());
        _marketDataInstance = marketDataPtr;
        return std::static_pointer_cast<TestMarketDataInterface>(_marketDataInstance);
    }
    if (config.get() == nullptr)
    {
        if (_marketDataInstance.get() == nullptr)
            BOOST_THROW_EXCEPTION(std::out_of_range("No MD Instance"));
        return std::static_pointer_cast<TestMarketDataInterface>(_marketDataInstance);
    }
    return std::static_pointer_cast<TestMarketDataInterface>(_marketDataInstance);
}

void TestMarketDataInterface::operator<<(const std::string &marketDataString) {
    auto inputParser = InputParser(marketDataString);
    inputParser.parseInputString();

    switch (inputParser.getType())
    {
        case InputParser::Type::Quote:
            quoteHandler(inputParser);
            break;
        case InputParser::Type::Kline:
            klineHandler(inputParser);
            break;
        case InputParser::Type::Trade:
            tradeHandler(inputParser);
            break;
        default:
            throw std::runtime_error("Unrecognized market data event!");
            break;
    }
}

void TestMarketDataInterface::quoteHandler(const InputParser& inputParser)
{
    auto quote = model::Quote(
        inputParser.at("symbol"),
        std::stod(inputParser.at("bidPrice")),
        std::stod(inputParser.at("bidQty")),
        std::stod(inputParser.at("askPrice")),
        std::stod(inputParser.at("askQty"))
    );
    auto quoteJson = quote.toJson();
    TestMarketDataInterface::getInstance(nullptr)->handleQuotes(quoteJson);
}

void TestMarketDataInterface::tradeHandler(const InputParser& inputParser)
{
    auto trade = model::Trade(
        inputParser.at("symbol"),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::stod(inputParser.at("price")),
        std::stod(inputParser.at("quantity")),
        buyOrderId,
        sellOrderId,
        tradeId
    );
    auto tradeJson = trade.toJson();
    TestMarketDataInterface::getInstance(nullptr)->handleTrades(tradeJson);
    buyOrderId++;
    sellOrderId++;
    tradeId++;
}

void TestMarketDataInterface::klineHandler(const InputParser& inputParser)
{
    auto kline = model::KLine(
        inputParser.at("symbol"),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::stod(inputParser.at("openPrice")),
        std::stod(inputParser.at("highPrice")),
        std::stod(inputParser.at("lowPrice")),
        std::stod(inputParser.at("closePrice")),
        std::stod(inputParser.at("volume")),
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        std::stod(inputParser.at("quoteAssetVolume")),
        std::stoi(inputParser.at("numOfTrades"))
    );
    Json::Value klineJson = kline.toJson();
    TestMarketDataInterface::getInstance(nullptr)->handleKlines(klineJson);
}