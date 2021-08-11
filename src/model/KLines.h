//
// Created by Vinay Manektalla on 20/07/2021.
//

#pragma once
#include <ctime>
#include <iostream>

#include <json/json.h>

#include "../Utils.h"

namespace model
{
    class KLine
    {
        /*
         * FROM Market
            1499040000000,      // Open time
            "0.01634790",       // Open
            "0.80000000",       // High
            "0.01575800",       // Low
            "0.01577100",       // Close
            "148976.11427815",  // Volume
            1499644799999,      // Close time
            "2434.19055334",    // Quote asset volume
            308,                // Number of trades
            "1756.87402397",    // Taker buy base asset volume
            "28.46694368",      // Taker buy quote asset volume
            "17928899.62484339" // Ignore.

         * From Websocket:
          {
          "e": "kline",     // Event type
          "E": 123456789,   // Event time
          "s": "BNBBTC",    // Symbol
          "k": {
            "t": 123400000, // Kline start time
            "T": 123460000, // Kline close time
            "s": "BNBBTC",  // Symbol
            "i": "1m",      // Interval
            "f": 100,       // First trade ID
            "L": 200,       // Last trade ID
            "o": "0.0010",  // Open price
            "c": "0.0020",  // Close price
            "h": "0.0025",  // High price
            "l": "0.0015",  // Low price
            "v": "1000",    // Base asset volume
            "n": 100,       // Number of trades
            "x": false,     // Is this kline closed?
            "q": "1.0000",  // Quote asset volume
            "V": "500",     // Taker buy base asset volume
            "Q": "0.500",   // Taker buy quote asset volume
            "B": "123456"   // Ignore
          }
         */
        std::time_t openTime;
        double openPrice;
        double highPrice;
        double lowPrice;
        double closePrice;
        double volume;
        std::time_t closeTime;
        double quoteAssetVolume{};
        int numOfTrades;

    public:
        explicit KLine(const Json::Value& value_it);
        explicit KLine(const Json::Value& jsonValue, const bool& wsData);
        [[nodiscard]] std::time_t getOpenTime() const { return openTime; };
        [[nodiscard]] std::time_t getCloseTime() const { return closeTime; };
        [[nodiscard]] double getOpenPrice() const { return openPrice; };
        [[nodiscard]] double getHighPrice() const { return highPrice; };
        [[nodiscard]] double getLowPrice() const { return lowPrice; };
        [[nodiscard]] double getClosePrice() const { return closePrice; };
        [[nodiscard]] double getVolume() const { return volume; };
        [[nodiscard]] double getQuoteAssetVolume() const { return quoteAssetVolume; };
        [[nodiscard]] int getNumOfTrades() const { return numOfTrades; };

        friend std::ostream& operator<<(std::ostream& os, const KLine& k)
        {
            os << "\n\t" << LOG_VAR(k.getOpenPrice()) << '\n';
            os << '\t' << LOG_VAR(k.getCloseTime()) << '\n';
            os << '\t' << LOG_VAR(k.getOpenPrice()) << '\n';
            os << '\t' << LOG_VAR(k.getHighPrice()) << '\n';
            os << '\t' << LOG_VAR(k.getLowPrice()) << '\n';
            os << '\t' << LOG_VAR(k.getLowPrice()) << '\n';
            os << '\t' << LOG_VAR(k.getClosePrice()) << '\n';
            os << '\t' << LOG_VAR(k.getVolume()) << '\n';
            os << '\t' << LOG_VAR(k.getQuoteAssetVolume()) << '\n';
            os << '\t' << LOG_VAR(k.getNumOfTrades()) << '\n';
            return os;
        };
    };


    class KLines
    {
        std::vector<KLine> kLines;

    public:
        explicit KLines(const Json::Value& json_result);
        std::vector<KLine>& getKLines() { return kLines; };
    };
}