#pragma once

#include <variant>

#include "Utils.h"
#include "model/KLines.h"
#include "model/Trade.h"
#include "model/Quote.h"
#include "StatisticsInterface.h"
#include "SmaStatistic.h"

namespace statistics
{

class StatisticsChain
{
private:
    std::vector<std::shared_ptr<statistics::StatisticsInterface>> _statisticsChain;
public:
    explicit StatisticsChain() : _statisticsChain() {}
    void addStatistics(const std::shared_ptr<statistics::StatisticsInterface>& _statisticsInterfacePtr);
    void runChain(const std::variant<model::KLine, model::Quote, model::Trade>& marketDataVariant);
};

}