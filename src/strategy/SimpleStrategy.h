#pragma once

#include "Strategy.h"
#include "Event.h"
#include "SmaStatistic.h"

template <typename TOrdApi>
class SimpleStrategy : public Strategy<TOrdApi>
{
public:
    SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_);
private:
    using StrategyBase = Strategy<TOrdApi>;
    void onKline(const std::shared_ptr<Event>& event_) override;
    void onQuote(const std::shared_ptr<Event>& event_) override;
    void onTrade(const std::shared_ptr<Event>& event_) override;
};

template <typename TOrdApi>
SimpleStrategy<TOrdApi>::SimpleStrategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_) :
StrategyBase(marketData_, orderInterface_)
{
    this->_statisticsChain.addStatistics(std::make_shared<statistics::SmaStatistic>(1));
}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onKline(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::KLine> klinePtr = event_->getKlinePtr();
    model::KLine kline = *klinePtr.get();
    PLOG_DEBUG << kline;
    //std::variant<model::KLine, model::Quote, model::Trade> kline_variant(kline);
    this->evaluateStatisticsChain(kline);
}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onQuote(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::Quote> quotePtr = event_->getQuotePtr();
    this->setQuote(quotePtr);
    PLOG_DEBUG << this->getQuote();
}

template <typename TOrdApi>
void SimpleStrategy<TOrdApi>::onTrade(const std::shared_ptr<Event>& event_)
{
    std::shared_ptr<model::Trade> tradePtr = event_->getTradePtr();
    model::Trade trade = *tradePtr.get();
    PLOG_DEBUG << trade;
}
