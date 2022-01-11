//
// Created by Vinay Manektalla on 1/10/21.
//

#pragma once
#include "model/KLines.h"
#include "model/Quote.h"


enum class EventType {
    KLine, Quote
};

class Event {
private:
    std::shared_ptr<model::KLine> _kline;
    std::shared_ptr<model::Quote> _quote;
    EventType _eventType;
    std::chrono::system_clock::time_point _timeStamp;
public:
    explicit Event(std::shared_ptr<model::KLine> kline_) :
            _kline(std::move(kline_))
            , _quote(nullptr)
            , _eventType(EventType::KLine) {}
    explicit Event(std::shared_ptr<model::Quote> quote_) :
            _kline(nullptr)
            , _quote(std::move(quote_))
            , _eventType(EventType::Quote) {}

    EventType eventType() const { return _eventType; }
    const std::shared_ptr<model::KLine>& getKlinePtr() const { return _kline; }
    const std::shared_ptr<model::Quote>& getQuotePtr() const { return _quote; }
    std::chrono::system_clock::time_point timeStamp() { return _timeStamp; }
};
