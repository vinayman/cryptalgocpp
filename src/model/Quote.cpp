#include "Quote.h"

model::Quote::Quote(const Json::Value& jsonValue, const bool& wsData) :
_symbol(std::string{""})
, _bidPrice(0.0)
, _bidQty(0.0)
, _askPrice(0.0)
, _askQty(0.0)
{
    _symbol = Symbol(jsonValue["s"].asString());
    _bidPrice = atof(jsonValue["b"].asString().c_str());
    _bidQty = atof(jsonValue["B"].asString().c_str());
    _askPrice = atof(jsonValue["a"].asString().c_str());
    _askQty = atof(jsonValue["A"].asString().c_str());
}