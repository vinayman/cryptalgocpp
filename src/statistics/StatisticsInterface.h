#pragma once

namespace statistics {

template <typename TMarketDataObject>
class StatisticsInterface
{
    virtual void evaluate(const TMarketDataObject& marketDataEvent) = 0;
protected:
    bool ready = false;
    bool isReady() { return ready; }
};

}