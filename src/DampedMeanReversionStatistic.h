#pragma once

#include <ranges>
#include "StatisticsInterface.h"

namespace statistics
{

class DampedMeanReversionStatistic: public StatisticsInterface
{
    bool primed;
    const size_t requiredNumAnalysed{10};
    std::vector<double> prices;
public:
    explicit DampedMeanReversionStatistic() : primed(false), analysedPriceCount(0), prices() {}
    ~DampedMeanReversionStatistic() override {};
    void evaluateKline(const model::KLine& kline) override;
    void evaluateTrade(const model::Trade& trade) override;
    void evaluateQuote(const model::Quote& quote) override;
    [[nodiscard]] isPrimed() const { return primed; };
};

}