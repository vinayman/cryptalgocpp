//
// Created by Vinay Manektalla on 4/10/21.
//

#pragma once
#include <string>
#include <memory>

#include "binance.h"

class OrderInterface {
private:
    std::string _apiKey;
    std::string _secretKey;
    binance::Server _server;
    std::shared_ptr<binance::Account> _account;

public:
    explicit OrderInterface(const std::string apiKey_, const std::string secretKey_) :
        _apiKey(apiKey_)
        , _secretKey(secretKey_)
        , _server()
        , _account(nullptr) {};
    void init();

    void sendOrder();
};
