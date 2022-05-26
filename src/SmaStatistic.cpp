#include "SmaStatistic.h"

void statistics::SmaStatistic::evaluateKline(const model::KLine& kline)
{
    PLOG_DEBUG << "We got the Kline";
    PLOG_DEBUG << kline;
}

void statistics::SmaStatistic::evaluateTrade(const model::Trade& trade)
{
    PLOG_DEBUG << "We got the trade";
    PLOG_DEBUG << trade;
}

void statistics::SmaStatistic::evaluateQuote(const model::Quote& quote)
{
    PLOG_DEBUG << "We got the quote";
    PLOG_DEBUG << quote;
}