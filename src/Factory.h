//
// Created by Vinay Manektalla on 11/08/2021.
//

#pragma once

#include "Config.h"

template <typename TMarketData>
class Factory {
public:
    explicit Factory(const std::shared_ptr<Config>& config);

private:
    std::shared_ptr<TMarketData> _marketData;
};

template<typename TMarketData>
Factory<TMarketData>::Factory(const std::shared_ptr<Config> &config) {
    _marketData = std::make_shared<TMarketData>(config);
    _marketData->subscribe();
}
