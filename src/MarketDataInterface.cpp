#include "MarketDataInterface.h"

void MarketDataInterface::subscribe()
{
    while (true)
    {
        std::string kLineSubscriptionString{
            "/ws/" + _symbol.getWebsocketSymbol() + "@kline_" + _mdSubscriptionPeriod
        };
        std::string quoteSubscriptionString{"/ws/" + _symbol.getWebsocketSymbol() + "@bookTicker"};
        binance::Websocket::init();
        PLOG_DEBUG << "Subscribing to:" << kLineSubscriptionString;
        binance::Websocket::connect_endpoint(handleKlines, kLineSubscriptionString.c_str());
        PLOG_DEBUG << "Subscribing to:" << quoteSubscriptionString;
        binance::Websocket::connect_endpoint(handleQuotes, quoteSubscriptionString.c_str());
        std::string tradeSubscriptionString{"/ws/" + _symbol.getWebsocketSymbol() + "@trade"};
        PLOG_DEBUG << "Subscribing to:" << tradeSubscriptionString;
        binance::Websocket::connect_endpoint(handleTrades, tradeSubscriptionString.c_str());
        PLOG_DEBUG << "Entering event loop";
        binance::Websocket::enter_event_loop();
        PLOG_DEBUG << "error exiting enter_event_loop and we will try again after 5sec";
        sleep(5);
    }
}