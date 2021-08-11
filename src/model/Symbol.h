//
// Created by Vinay Manektalla on 21/07/2021.
//

#pragma once
#include <string>
#include <utility>

#include <boost/algorithm/string.hpp>

namespace model {
    class Symbol
    {
        std::string symbol{};

    public:
        explicit Symbol(std::string  symbol_) :
                symbol(std::move(symbol_)) {};
        explicit Symbol(std::string_view  symbol_) :
                symbol(symbol_) {};
        [[nodiscard]] bool isStablePair() const
        {
            if (symbol.find(std::string{"USDT"}) != std::string::npos ||
                symbol.find(std::string{"BUSD"}) != std::string::npos)
            {
                return true;
            }
            return false;
        };
        [[nodiscard]] bool isCryptoPair() const { return !isStablePair(); };
        [[nodiscard]] std::string getSymbol() const { return symbol; };
        [[nodiscard]] std::string getWebsocketSymbol() const { return boost::algorithm::to_lower_copy(symbol); };
    };
}
