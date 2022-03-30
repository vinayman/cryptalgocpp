#include "SmaStatistic.h"

void statistics::SmaStatistic::evaluateKline(const model::KLine& kline)
{
    PLOG_DEBUG << "We got the Kline";
}

void statistics::SmaStatistic::evaluateTrade(const model::Trade& trade)
{
    PLOG_DEBUG << "We got the quote";
}

void statistics::SmaStatistic::evaluateQuote(const model::Quote& quote)
{
    PLOG_DEBUG << "We got the trade";
}