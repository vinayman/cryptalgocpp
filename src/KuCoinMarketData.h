#pragma once

//#include <libwebsockets.h>

#include "Utils.h"
#include "model/KLines.h"
#include "model/Symbol.h"

#define BINANCE_WS_HOST "stream.binance.com"
#define BINANCE_WS_PORT 9443

class KuCoinMarketData {
private:
    std::string _mdSubscriptionPeriod{};
    model::Symbol _symbol;
public:
    KuCoinMarketData() :
            _symbol(model::Symbol(std::string{"BNBUSDT"}))
            , _mdSubscriptionPeriod("1m") {}

    void subscribe();
};