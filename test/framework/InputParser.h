#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <boost/exception/exception.hpp>

#include "Utils.h"

template <typename TParam>
class InputParser
{
public:
    enum class Type
    {
        Quote,
        Kline,
        Price,
        Trade,
        Unknown
    };
private:
    std::unordered_map<std::string, TParam> params;
    std::string inputString;
public:
    explicit InputParser(const std::string& inputString_) :
        inputString(std::move(inputString_)) {}

    Type type;
    void parseInputString(const std::string& inputString);
    std::unordered_map<std::string, TParam>& getParams() { return params; };
    Type getType();
    bool paramExists(const std::string &key);
    TParam& at(const std::string& key);
};