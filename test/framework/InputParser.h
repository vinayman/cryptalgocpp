#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

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
    std::unordered_map<std::string, std::string> params;
    std::string inputString;
public:
    explicit InputParser(const std::string& inputString_) :
        inputString(std::move(inputString_)) {}
    explicit InputParser() = default;

    Type type;
    void parseInputString(const std::string& inputString_);
    std::unordered_map<std::string, std::string>& getParams() { return params; };
    Type getType();
    bool paramExists(const std::string &key);
    std::string& at(const std::string& key);
    std::string getInputString() { return inputString; };
};