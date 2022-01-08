//
// Created by Vinay Manektalla on 1/10/21.
//

#pragma once
#include "model/KLines.h"


enum class EventType {
    KLine
};

class Event {
private:
    std::shared_ptr<model::KLine> _kline;
    EventType _eventType;
    std::chrono::system_clock::time_point _timeStamp;
public:
    explicit Event(std::shared_ptr<model::KLine> kline_) :
            _kline(std::move(kline_))
            , _eventType(EventType::KLine) {}

    EventType eventType() const { return _eventType; }
    const std::shared_ptr<model::KLine>& getKline() const { return _kline; }
    std::chrono::system_clock::time_point timeStamp() { return _timeStamp; }
};
