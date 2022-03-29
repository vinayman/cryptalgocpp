#pragma once

#include "Strategy.h"
#include "Event.h"
#include "statistics/SmaStatistic.h"

template <typename TOrdApi, typename TStatisticsMarketDataObject>
class SimpleStrategy : public Strategy<TOrdApi, TStatisticsMarketDataObject>
{
public:
    SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_);
private:
    using StrategyBase = Strategy<TOrdApi, TStatisticsMarketDataObject>;
    void onKline(const std::shared_ptr<Event>& event_) override;
    void onQuote(const std::shared_ptr<Event>& event_) override;
    void onTrade(const std::shared_ptr<Event>& event_) override;
    statistics::SmaStatistic<model::KLine> smaStatistic;
};

template <typename TOrdApi, typename TStatisticsMarketDataObject>
SimpleStrategy<TOrdApi, TStatisticsMarketDataObject>::SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_) :
StrategyBase(marketData_, orderInterface_)
, smaStatistic()
{}

template <typename TOrdApi, typename TStatisticsMarketDataObject>
void SimpleStrategy<TOrdApi, TStatisticsMarketDataObject>::onKline(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::KLine> klinePtr = event_->getKlinePtr();
    model::KLine kline = *klinePtr.get();
    PLOG_DEBUG << kline;
    smaStatistic.evaluate(kline);
}

template <typename TOrdApi, typename TStatisticsMarketDataObject>
void SimpleStrategy<TOrdApi, TStatisticsMarketDataObject>::onQuote(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::Quote> quotePtr = event_->getQuotePtr();
    this->setQuote(quotePtr);
    PLOG_DEBUG << this->getQuote();
}

template <typename TOrdApi, typename TStatisticsMarketDataObject>
void SimpleStrategy<TOrdApi, TStatisticsMarketDataObject>::onTrade(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::Trade> tradePtr = event_->getTradePtr();
    model::Trade trade = *tradePtr.get();
    PLOG_DEBUG << trade;
}
