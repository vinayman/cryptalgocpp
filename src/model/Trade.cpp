#include "Trade.h"

model::Trade::Trade(const Json::Value& jsonValue, const bool& wsData) :
symbol(std::string{""})
, eventTime(0.0)
, tradeTime(0.0)
, price(0.0)
, quantity(0.0)
, buyerOrderId(0.0)
, sellerOrderId(0.0)
{
    symbol = Symbol(jsonValue["s"].asString());
    eventTime = atof(jsonValue["E"].asString().c_str());
    tradeTime = atof(jsonValue["t"].asString().c_str());
    price = atof(jsonValue["p"].asString().c_str());
    quantity = atof(jsonValue["q"].asString().c_str());
    buyerOrderId = atof(jsonValue["b"].asString().c_str());
    sellerOrderId = atof(jsonValue["a"].asString().c_str());
}
