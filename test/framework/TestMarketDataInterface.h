#pragma once

#include "MarketData.h"
#include "InputParser.h"
#include "model/KLines.h"
#include "model/Trade.h"
#include "model/Quote.h"

class TestMarketDataInterface : public MarketData
{
protected:
    long buyOrderId;
    long sellOrderId;
    long tradeId;
public:
    InputParser inputParser;
    explicit TestMarketDataInterface() : inputParser(), buyOrderId(0), sellOrderId(0), tradeId(0) {}
    void subscribe() {};
    void operator << (const std::string& marketDataString);

    void quoteHandler(const std::unordered_map<std::string, std::string>& params);
    void tradeHandler(const std::unordered_map<std::string, std::string>& params);
    void klineHandler(const std::unordered_map<std::string, std::string>& params);
};