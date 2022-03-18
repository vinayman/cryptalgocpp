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

Json::Value model::Trade::toJson()
{
    Json::Value tradeJson;
    tradeJson["e"] = "trade";
    tradeJson["E"] = getEventTime();
    tradeJson["s"] = getSymbol().toString();
    tradeJson["t"] = getTradeId();
    tradeJson["p"] = getPrice();
    tradeJson["q"] = getQuantity();
    tradeJson["b"] = getBuyerOrderId();
    tradeJson["a"] = getSellerOrderId();
    tradeJson["T"] = getTradeTime();
    return tradeJson;
}