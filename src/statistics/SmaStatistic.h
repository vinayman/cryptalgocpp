#pragma once

#include "StatisticsInterface.h"

namespace statistics
{

template <typename TMarketDataObject>
class SmaStatistic : public StatisticsInterface<TMarketDataObject>
{
private:
    using StatisticsInterfaceBase = StatisticsInterface<TMarketDataObject>;
public:
    explicit SmaStatistic();
    void evaluate(const TMarketDataObject& marketDataObject) override;
};

}

template <typename TMarketDataObject>
statistics::SmaStatistic<TMarketDataObject>::SmaStatistic() : 
StatisticsInterfaceBase()
{}

template <typename TMarketDataObject>
void statistics::SmaStatistic<TMarketDataObject>::evaluate(const TMarketDataObject& marketDataObject)
{
    
}