#include "SimpleStrategy.h"
#include "OrderInterface.h"
#include "model/MarketDataObject.h"

#define REGISTER(strategy_) \
extern "C" std::shared_ptr<strategy_<OrderInterface, model::MarketDataObject>> RegisterSimpleStrategy(std::shared_ptr<MarketData> mdPtr_,  std::shared_ptr<OrderInterface> od_) { \
    auto sharedPtr = std::make_shared<strategy_<OrderInterface, model::MarketDataObject>>(mdPtr_, od_); \
    return sharedPtr; \
}

REGISTER(SimpleStrategy)