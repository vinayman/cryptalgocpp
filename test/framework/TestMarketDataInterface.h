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
    explicit TestMarketDataInterface() : buyOrderId(0), sellOrderId(0), tradeId(0) {}
    ~TestMarketDataInterface() {}
    void subscribe() {};
    void operator << (const std::string& marketDataString);

    void quoteHandler(const InputParser& inputParser);
    void tradeHandler(const InputParser& inputParser);
    void klineHandler(const InputParser& inputParser);
};