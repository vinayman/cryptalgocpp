#include "SimpleStrategy.h"
#include "OrderInterface.h"

#define REGISTER(strategy_) \
extern "C" std::shared_ptr<strategy_<OrderInterface>> RegisterSimpleStrategy(std::shared_ptr<MarketData> mdPtr_,  std::shared_ptr<OrderInterface> od_) { \
    auto sharedPtr = std::make_shared<strategy_<OrderInterface>>(mdPtr_, od_); \
    return sharedPtr; \
}

REGISTER(SimpleStrategy)