//
// Created by Vinay Manektalla on 19/07/2021.
//

#pragma once
#include <memory>

#include "model/KLines.h"
#include "model/Price.h"
#include "model/Quote.h"
#include "Config.h"

class MarketDataInterface {
public:
    using KlinePtr = std::shared_ptr<model::KLine>;
    using PricePtr = std::shared_ptr<model::Price>;
    using QuotePtr = std::shared_ptr<model::Quote>;

    MarketDataInterface();
};
