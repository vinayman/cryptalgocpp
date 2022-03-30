#include "StatisticsChain.h"

void statistics::StatisticsChain::addStatistics(const std::shared_ptr<StatisticsInterface>& _statisticsInterfacePtr)
{
    _statisticsChain.push_back(std::move(_statisticsInterfacePtr));
}

void statistics::StatisticsChain::runChain(const std::variant<model::KLine, model::Quote, model::Trade>& marketDataVariant)
{
    for(auto & statistics : _statisticsChain)
    {
        if (statistics != nullptr)
        {
            std::visit(GenericVisitor{
                [&](const model::KLine& kline)
                {
                    statistics->evaluateKline(kline);
                },
                [&](const model::Trade& trade)
                {
                    statistics->evaluateTrade(trade);
                },
                [&](const model::Quote& quote)
                {
                    statistics->evaluateQuote(quote);
                }
            }, marketDataVariant);
        }
    }
}