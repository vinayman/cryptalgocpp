//
// Created by Vinay Manektalla on 19/07/2021.
//

#pragma once
#include <string>
#include <map>
#include <fstream>
#include <any>

#include <boost/program_options.hpp>
#include <json/json.h>
#include <plog/Log.h>

#include "Utils.h"

class Config
{
protected:
    std::map<std::string, std::string> _config;
public:
    explicit Config(const std::map<std::string, std::string>& configMap);
    explicit Config(const std::basic_string<char>& configFile);
    const std::string& get(const std::string& key);
    template <typename Val> void set(const std::string& key, const Val& value);
    [[nodiscard]] bool configParamExists(const std::string& key);
};
