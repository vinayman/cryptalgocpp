//
// Created by Vinay Manektalla on 4/10/21.
//

#include "OrderInterface.h"


void OrderInterface::init()
{
    _account = std::make_shared<binance::Account>(_server, _apiKey, _secretKey);
}

void OrderInterface::sendOrder()
{
    //_account->sendOrder();
}