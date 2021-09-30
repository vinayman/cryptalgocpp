//
// Created by Vinay Manektalla on 20/07/2021.
//

#include "KLines.h"

model::KLine::KLine(const Json::Value& value_it) :
    symbol(Symbol(std::string{"NO SYMBOL"})),
    openTime(std::time_t(NULL)),
    openPrice(0.0),
    highPrice(0.0),
    lowPrice(0.0),
    closePrice(0.0),
    volume(0.0),
    closeTime(std::time_t(NULL)),
    quoteAssetVolume(0.0),
    numOfTrades(0)
{
    openTime = value_it[0].asInt64();
    openPrice = atof(value_it[1].asString().c_str());
    highPrice = atof(value_it[2].asString().c_str());
    lowPrice = atof(value_it[3].asString().c_str());
    closePrice = atof(value_it[4].asString().c_str());
    volume = atof(value_it[5].asString().c_str());
    closeTime = atof(value_it[6].asString().c_str());
}

model::KLine::KLine(const Json::Value& jsonValue, const bool& wsData)  :
    symbol(Symbol(std::string{""})),
    openTime(std::time_t(NULL)),
    openPrice(0.0),
    highPrice(0.0),
    lowPrice(0.0),
    closePrice(0.0),
    volume(0.0),
    closeTime(std::time_t(NULL)),
    quoteAssetVolume(0.0),
    numOfTrades(0)
{
    symbol = Symbol(jsonValue["s"].asString());
    openTime = jsonValue["k"]["t"].asInt64();
    closeTime = jsonValue["k"]["T"].asInt64();
    openPrice = atof(jsonValue["k"]["o"].asString().c_str());
    highPrice = atof(jsonValue["k"]["h"].asString().c_str());
    lowPrice = atof(jsonValue["k"]["l"].asString().c_str());
    closePrice = atof(jsonValue["k"]["c"].asString().c_str());
    volume = atof(jsonValue["k"]["v"].asString().c_str());
    numOfTrades = atof(jsonValue["k"]["n"].asString().c_str());
    quoteAssetVolume = atof(jsonValue["k"]["q"].asString().c_str());
}

Json::Value model::KLine::toJson() {
    Json::Value klineRootJson;
    Json::Value klineDataJson;
    klineRootJson["e"] = "kline";
    klineRootJson["s"] = getSymbol().toString();
    klineDataJson["t"] = getOpenTime();
    klineDataJson["T"] = getCloseTime();
    klineDataJson["o"] = getOpenPrice();
    klineDataJson["h"] = getHighPrice();
    klineDataJson["l"] = getLowPrice();
    klineDataJson["c"] = getClosePrice();
    klineDataJson["v"] = getVolume();
    klineDataJson["n"] = getNumOfTrades();
    klineDataJson["q"] = getQuoteAssetVolume();
    klineRootJson["k"] = klineDataJson;
    return klineRootJson;
}

model::KLines::KLines(const Json::Value& json_result) :
    kLines()
{
    for (const Json::Value& i : json_result)
    {
        auto kline = KLine(i);
        kLines.push_back(kline);
    }
}