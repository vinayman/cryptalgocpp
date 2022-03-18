#include "InputParser.h"

template <typename TParam>
void InputParser<TParam>::parseInputString(const std::string& inputString)
{
    std::string chunk;
    std::istringstream iss(inputString);
    while (getline(iss, chunk, ' '))
    {
        size_t pos = chunk.find("=");
        if (pos == std::string::npos)
            continue;
        std::string key = chunk.substr(0, pos);
        TParam value = chunk.substr(pos+1);
        params[key] = value;
    }
}

template <typename TParam>
InputParser<TParam>::Type InputParser<TParam>::getType()
{
    if (paramExists("TYPE"))
    {
        switch (params.at("TYPE"))
        {
            case "QUOTE":
                return Type::Quote;
            case "TRADE":
                return Type::Trade;
            case "KLINE":
                return Type::Kline;
            default:
                return Type::Unknown;
        }
    }
    return Type::Unknown;
}

template <typename TParam>
bool InputParser<TParam>::paramExists(const std::string &key) {
    if (params.find(key) != params.end()) {
        return true;
    }
    return false;
}

template <typename TParam>
TParam& InputParser<TParam>::at(const std::string& key)
{
    try 
    {
        params.at(key);
    }
    catch (std::exception& e)
    {
        std::stringstream message;
        message << "Mandatory param missing: " << LOG_VAR(key) << " " << LOG_VAR(inputString);
        BOOST_THROW_EXCEPTION<TParam>(std::runtime_error(message.str()));
    }
}