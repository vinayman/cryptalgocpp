#include "InputParser.h"

void InputParser::parseInputString()
{
    std::string chunk;
    std::istringstream iss(inputString);
    while (getline(iss, chunk, ' '))
    {
        size_t pos = chunk.find("=");
        if (pos == std::string::npos)
            continue;
        std::string key = chunk.substr(0, pos);
        std::string value = chunk.substr(pos+1);
        params[key] = value;
    }
}

InputParser::Type InputParser::getType()
{
    if (paramExists("TYPE"))
    {
        if (params.at("TYPE") == "QUOTE")
            return Type::Quote;
        else if (params.at("TYPE") == "TRADE")
            return Type::Trade;
        else if (params.at("TYPE") == "KLINE")
            return Type::Kline;
    }
    return Type::Unknown;
}

bool InputParser::paramExists(const std::string& key) {
    if (params.find(key) != params.end()) {
        return true;
    }
    return false;
}

const std::string& InputParser::at(const std::string& key) const
{
    try 
    {
        return params.at(key);
    }
    catch (std::exception& e)
    {
        std::stringstream message;
        message << "Param: " << LOG_VAR(key) << " does not exist in inputString";
        throw std::runtime_error(message.str());
    }
}