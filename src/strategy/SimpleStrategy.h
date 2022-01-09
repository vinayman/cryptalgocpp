#pragma once

#include "Strategy.h"
#include "Event.h"

template <typename TOrdApi>
class SimpleStrategy : public Strategy<TOrdApi>
{
public:
    SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_);
private:
    using StrategyBase = Strategy<TOrdApi>;
    void onKline(const std::shared_ptr<Event>& event_) override;
};

template <typename TOrdApi>
SimpleStrategy<TOrdApi>::SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_) :
StrategyBase(marketData_, orderInterface_)
{}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onKline(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::KLine> klinePtr = event_->getKlinePtr();
    model::KLine kline = *klinePtr.get();
    LOGINFO(kline);
}
