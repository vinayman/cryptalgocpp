//
// Created by Vinay Manektalla on 30/9/21.
//

#pragma once

#include <iostream>

#include <boost/exception/exception.hpp>

#include "MarketData.h"
#include "Event.h"
#include "Utils.h"
#include "model/KLines.h"
#include "model/Quote.h"
#include "model/Allocation.h"
#include "model/Allocations.h"

template <typename TOrdApi>
class Strategy {
public:
    Strategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_);
    void evaluate();
    bool shouldEvaluate();
    void createAllocation(const model::Side& side_, const model::OrderAction& orderAction_);
    virtual void onKline(const std::shared_ptr<Event>& event) = 0;
    virtual void onQuote(const std::shared_ptr<Event>& event) = 0;
    void setQuote(const std::shared_ptr<model::Quote>& quotePtr_) {  _currentQuotePtr = quotePtr_ ; };
    model::Quote& getQuote() {return *_currentQuotePtr.get(); };
private:
    std::shared_ptr<MarketData> _marketData;
    std::shared_ptr<TOrdApi> _orderInterface;
    std::shared_ptr<model::Quote> _currentQuotePtr;
    model::Allocations _allocations;
};


template<typename TOrdApi>
Strategy<TOrdApi>::Strategy(const std::shared_ptr<MarketData> marketData_, const std::shared_ptr<TOrdApi>& orderInterface_) :
_marketData(marketData_)
, _orderInterface(orderInterface_)
, _currentQuotePtr(nullptr)
{}

template<typename TOrdApi>
void Strategy<TOrdApi>::evaluate() {
    auto event = _marketData->read();
    if (event.get() == nullptr)
        return;
    switch (event->eventType())
    {
        case EventType::KLine:
            onKline(event);
            break;
        case EventType::Quote:
            onQuote(event);
            break;
        default:
            LOGINFO("Unrecognized event");
            break;
    }
    if (_allocations.hasChanged())
    {
        LOGINFO("Allocations have changed");
        // handleAllocations();
        _allocations.setUnchanged();
    }
}

template<typename TOrdApi>
bool Strategy<TOrdApi>::shouldEvaluate() {
    return true;
}

template<typename TOrdApi>
void Strategy<TOrdApi>::createAllocation(const model::Side& side_, const model::OrderAction& orderAction_) {
    auto currentQuote = *_currentQuotePtr.get();
    if (_currentQuotePtr == nullptr)
    {
        BOOST_THROW_EXCEPTION(std::out_of_range("_currentQuotePtr is null -> cannot make allocation"));
        return;
    }
    auto price_ = (side_ == model::Side::Buy) ? currentQuote.getBidPrice() : currentQuote.getAskPrice();
    auto size_ = (side_ == model::Side::Buy) ? currentQuote.getBidQty() : currentQuote.getAskQty();
    _allocations.addAllocation(std::make_shared<model::Allocation>(model::Allocation(currentQuote.getSymbol(), price_, size_, side_, orderAction_)));
}
