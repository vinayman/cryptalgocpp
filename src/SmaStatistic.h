#pragma once

#include "StatisticsInterface.h"

namespace statistics
{

class SmaStatistic: public StatisticsInterface
{
    int period;
public:
    explicit SmaStatistic(int _period) : period(_period) {}
    ~SmaStatistic() override {};
    void evaluateKline(const model::KLine& kline) override;
    void evaluateTrade(const model::Trade& trade) override;
    void evaluateQuote(const model::Quote& quote) override;
};

}