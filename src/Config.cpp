//
// Created by Vinay Manektalla on 19/07/2021.
//

#include "Config.h"


Config::Config(const std::basic_string<char>& configFile) :
    _config()
{
    std::ifstream cfgfile(configFile, std::ifstream::binary);
    Json::Value root;
    cfgfile >> root;
    if (!root.empty())
    {
        for (Json::ValueConstIterator itr = root.begin() ; itr != root.end() ; itr++)
        {
            switch (itr->type())
            {
            case Json::stringValue:
                set(itr.key().asString(), itr->asString());
                break;
            case Json::intValue:
                set(itr.key().asString(), itr->asInt());
                break;
            case Json::uintValue:
                set(itr.key().asString(), itr->asUInt());
                break;
            case Json::booleanValue:
                set(itr.key().asString(), itr->asBool());
                break;
            default:
                set(itr.key().asString(), itr->asString());
                break;
            }
        }
    }
}

Config::Config(const std::map<std::string, std::string>& configMap)
{
    for (const auto& it : configMap)
    {
        set(it.first, it.second);
    }
}

const std::string& Config::get(const std::string& key)
{
    return _config.at(key);
}

template<typename Val>
void Config::set(const std::string& key, const Val& value)
{
    _config[key] = value;
}

bool Config::configParamExists(const std::string &key) {
    if (_config.find(key) != _config.end()) {
        return true;
    }
    return false;
}
