#include "MarketDataInterface.h"

void MarketDataInterface::subscribe()
{
    while (true)
    {
        std::string kLineSubscriptionString{
            "/ws/" + _symbol.getWebsocketSymbol() + "@kline_" + _mdSubscriptionPeriod
        };
        std::string quoteSubscriptionString{"/ws/" + _symbol.getWebsocketSymbol() + "@bookTicker"};
        std::string tradeSubscriptionString{"/ws/" + _symbol.getWebsocketSymbol() + "@trade"};
        binance::Websocket::init();
        PLOG_DEBUG << "Subscribing to:" << kLineSubscriptionString;
        binance::Websocket::connect_endpoint(this->handleKlines, kLineSubscriptionString.c_str());
        PLOG_DEBUG << "Subscribing to:" << tradeSubscriptionString;
        binance::Websocket::connect_endpoint(this->handleTrades, tradeSubscriptionString.c_str());
        PLOG_DEBUG << "Subscribing to:" << quoteSubscriptionString;
        binance::Websocket::connect_endpoint(this->handleQuotes, quoteSubscriptionString.c_str());
        PLOG_DEBUG << "Entering event loop";
        binance::Websocket::enter_event_loop();
        PLOG_DEBUG << "error exiting enter_event_loop and we will try again after 5sec";
        sleep(5);
    }
}