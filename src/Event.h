//
// Created by Vinay Manektalla on 1/10/21.
//

#pragma once
#include "model/KLines.h"
#include "model/Quote.h"
#include "model/Trade.h"


enum class EventType {
    KLine, Quote, Trade
};

class Event {
private:
    std::shared_ptr<model::KLine> _kline;
    std::shared_ptr<model::Quote> _quote;
    std::shared_ptr<model::Trade> _trade;
    EventType _eventType;
    std::chrono::system_clock::time_point _timeStamp;
public:
    explicit Event(std::shared_ptr<model::KLine> kline_) :
            _kline(std::move(kline_))
            , _quote(nullptr)
            , _trade(nullptr)
            , _eventType(EventType::KLine)
            , _timeStamp(std::chrono::system_clock::now()) {}

    explicit Event(std::shared_ptr<model::Quote> quote_) :
            _kline(nullptr)
            , _quote(std::move(quote_))
            , _trade(nullptr)
            , _eventType(EventType::Quote) 
            , _timeStamp(std::chrono::system_clock::now()) {}

    explicit Event(std::shared_ptr<model::Trade> trade_) :
            _kline(nullptr)
            , _quote(nullptr)
            , _trade(std::move(trade_))
            , _eventType(EventType::Trade) 
            , _timeStamp(std::chrono::system_clock::now()) {}

    EventType eventType() const { return _eventType; }
    const std::shared_ptr<model::KLine>& getKlinePtr() const { return _kline; }
    const std::shared_ptr<model::Quote>& getQuotePtr() const { return _quote; }
    const std::shared_ptr<model::Trade>& getTradePtr() const { return _trade; }
    std::chrono::system_clock::time_point timeStamp() { return _timeStamp; }
};
