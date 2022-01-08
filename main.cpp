#include <iostream>
#include <memory>

#include <boost/program_options.hpp>
#include <boost/exception/exception.hpp>

#include "Utils.h"
#include "Config.h"
#include "Factory.h"
#include "MarketData.h"


int ws_klines_onData(Json::Value& json_result)
{
    LOGINFO(json_result);
    if (json_result["e"].asString() == "kline")
    {
        auto kline = model::KLine(json_result, true);
        LOGINFO(kline);
    }
    return 0;
}

int main(int argc, char* argv [])
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
    ("help", "print usage message")
    ("config", boost::program_options::value<std::string>(), "config file");
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc,
                                  argv, desc), vm);
    boost::program_options::notify(vm);

    if (!vm.contains("config"))
    {
        LOGDEBUG("Config file not provided");
        BOOST_THROW_EXCEPTION(std::out_of_range("No config file provided"));
        return 1;
    }

    std::shared_ptr<Config> config = std::make_shared<Config>
                                     (vm.at("config").as<std::string>());

    LOGINFO(config->get("name"));

    LOGINFO("Hello, World!");

    auto factory = std::make_unique<Factory<MarketData>>(config);
    while (factory->getStrategy().shouldEvaluate())
    {
        factory->getStrategy().evaluate();
    }

    return 0;
}
