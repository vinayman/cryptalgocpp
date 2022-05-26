#include "DampedMeanReversionStatistic.h"

void statistics::DampedMeanReversionStatistic::evaluateKline(const model::KLine& kline)
{
    return;
}

void statistics::DampedMeanReversionStatistic::evaluateTrade(const model::Trade& trade)
{
    prices.emplace_back(trade.getPrice());
}

void statistics::DampedMeanReversionStatistic::evaluateQuote(const model::Quote& quote)
{
    return;
}