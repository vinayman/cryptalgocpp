#pragma once

#include <json/json.h>

#include "../Utils.h"
#include "Symbol.h"


namespace model {

class Trade {
    /* From Websocket:
    {
        "e": "trade",     // Event type
        "E": 123456789,   // Event time
        "s": "BNBBTC",    // Symbol
        "t": 12345,       // Trade ID
        "p": "0.001",     // Price
        "q": "100",       // Quantity
        "b": 88,          // Buyer order ID
        "a": 50,          // Seller order ID
        "T": 123456785,   // Trade time
        "m": true,        // Is the buyer the market maker?
        "M": true         // Ignore
    }
    */
private:
    std::time_t eventTime;
    Symbol symbol;
    int tradeId;
    double price;
    double quantity;
    int buyerOrderId;
    int sellerOrderId;
    std::time_t tradeTime;

public:
    explicit Trade(const Json::Value& jsonValue, const bool& wsData);
    explicit Trade(
        const std::string& symbol_,
        const std::time_t& eventTime_,
        const std::time_t& tradeTime_,
        const double& price_,
        const double& quantity_,
        const int& buyerOrderId_,
        const int& sellerOrderId_,
        const int& tradeId_
    ) : symbol(symbol_)
        , eventTime(eventTime_) 
        , tradeTime(tradeTime_)
        , price(price_)
        , quantity(quantity_)
        , buyerOrderId(buyerOrderId_)
        , sellerOrderId(sellerOrderId_)
        , tradeId(tradeId_) {}

    [[nodiscard]] Symbol getSymbol() const { return symbol; };
    [[nodiscard]] std::time_t getEventTime() const { return eventTime; };
    [[nodiscard]] std::time_t getTradeTime() const { return tradeTime; };
    [[nodiscard]] double getPrice() const { return price; };
    [[nodiscard]] double getQuantity() const { return quantity; };
    [[nodiscard]] int getBuyerOrderId() const { return buyerOrderId; };
    [[nodiscard]] int getSellerOrderId() const { return sellerOrderId; };
    [[nodiscard]] int getTradeId() const { return tradeId; };
    [[nodiscard]] Json::Value toJson();

    friend std::ostream& operator<<(std::ostream& os, const Trade& t)
    {
        os << "\n\t" << LOG_VAR(t.getSymbol()) << '\n';
        os << "\t" << LOG_VAR(t.getEventTime()) << '\n';
        os << '\t' << LOG_VAR(t.getTradeTime()) << '\n';
        os << '\t' << LOG_VAR(t.getPrice()) << '\n';
        os << '\t' << LOG_VAR(t.getQuantity()) << '\n';
        os << '\t' << LOG_VAR(t.getBuyerOrderId()) << '\n';
        os << '\t' << LOG_VAR(t.getSellerOrderId()) << '\n';
        return os;
    };
};

}
