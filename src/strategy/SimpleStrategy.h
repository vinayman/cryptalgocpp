#pragma once

#include "Strategy.h"
#include "Event.h"
#include "SmaStatistic.h"
#include "DampedMeanReversionStatistic.h"

template <typename TOrdApi>
class SimpleStrategy : public Strategy<TOrdApi>
{
public:
    SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_);
private:
    using StrategyBase = Strategy<TOrdApi>;
    void onKline(const std::shared_ptr<Event> event_) override;
    void onQuote(const std::shared_ptr<Event> event_) override;
    void onTrade(const std::shared_ptr<Event> event_) override;
};

template <typename TOrdApi>
SimpleStrategy<TOrdApi>::SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_) :
StrategyBase(marketData_, orderInterface_)
{
    this->_statisticsChain.addStatistics(std::make_shared<statistics::SmaStatistic>(1));
    this->_statisticsChain.addStatistics(std::make_shared<statistics::DampedMeanReversionStatistic>());
}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onKline(const std::shared_ptr<Event> event_)
{
    std::shared_ptr<model::KLine> klinePtr = event_->getKlinePtr();
    if (klinePtr == nullptr)
        return;
    const model::KLine kline = *klinePtr.get();
    PLOG_DEBUG << kline;
    this->evaluateStatisticsChain(kline);
}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onQuote(const std::shared_ptr<Event> event_)
{
    std::shared_ptr<model::Quote> quotePtr = event_->getQuotePtr();
    if (quotePtr == nullptr)
        return;
    this->setQuote(std::move(quotePtr));
    PLOG_DEBUG << this->getQuote();
    this->evaluateStatisticsChain(this->getQuote());
}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onTrade(const std::shared_ptr<Event> event_)
{
    std::shared_ptr<model::Trade> tradePtr = event_->getTradePtr();
    if (tradePtr == nullptr)
        return;
    const model::Trade trade = *tradePtr.get();
    PLOG_DEBUG << trade;
    this->evaluateStatisticsChain(trade);
}
