#pragma once

#include "plog/Log.h"
#include "model/KLines.h"
#include "model/Trade.h"
#include "model/Quote.h"

namespace statistics {

class StatisticsInterface
{
public:
    virtual void evaluateKline(const model::KLine& kline) = 0;
    virtual void evaluateTrade(const model::Trade& trade) = 0;
    virtual void evaluateQuote(const model::Quote& quote) = 0;
    virtual ~StatisticsInterface() {};
protected:
    bool ready = false;
    bool isReady() { return ready; }
};

}