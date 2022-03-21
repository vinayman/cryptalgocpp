#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include "Utils.h"

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
    std::map<std::string, std::string> params;
    std::string inputString;
public:
    explicit InputParser(const std::string& inputString_) : params(), inputString(std::move(inputString_)) {};

    Type type;
    void parseInputString();
    std::map<std::string, std::string>& getParams() { return params; };
    Type getType();
    bool paramExists(const std::string& key);
    const std::string& at(const std::string& key) const;
};