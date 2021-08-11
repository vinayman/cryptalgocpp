//
// Created by Vinay Manektalla on 11/08/2021.
//

#include "MarketData.h"

MarketData::MarketData(const std::shared_ptr <Config> &config)
    :
    _config(config)
{ }

void MarketData::subscribe() {
    while (true) {
        binance::Websocket::init();
        binance::Websocket::connect_endpoint(handleKlines, "/ws/bnbusdt@kline_1m");
        binance::Websocket::enter_event_loop();
        LOGINFO("error exiting enter_event_loop and we will try again after 5sec");
        sleep(5);
    }
}

int MarketData::handleKlines(Json::Value &json_result) {
    LOGINFO(json_result);
    if(json_result["e"].asString() == "kline") {
        auto kline = model::KLine(json_result, true);
        LOGINFO(kline);
    }
    return 0;
}

int MarketData::handlePrice(const Json::Value &json_result) {
    return 0;
}

int MarketData::handleQuotes(const Json::Value &json_result) {
    return 0;
}
