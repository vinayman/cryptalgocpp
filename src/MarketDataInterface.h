#pragma once

#include <memory>

#include "binance_websocket.h"

#include "Utils.h"
#include "MarketData.h"
#include "Config.h"
#include "model/Symbol.h"

class MarketData;

class MarketDataInterface : public MarketData
{
public:
    void subscribe();
};