#include <iostream>
#include <memory>

#include <boost/program_options.hpp>
#include <boost/exception/exception.hpp>

#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"

#include "Utils.h"
#include "Config.h"
#include "Factory.h"
#include "MarketDataInterface.h"
#include "OrderInterface.h"
#include "model/MarketDataObject.h"


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

    if (!config->configParamExists("log_directory"))
    {
        LOGDEBUG("Please specifiy log_directory in config.json");
        BOOST_THROW_EXCEPTION(std::out_of_range("No log_directory provided in config"));
    }

    std::string logDirectory = config->get("log_directory");
    plog::init(plog::debug, logDirectory.c_str());

    signal(SIGHUP, handle_sighup);

    auto factory = std::make_unique<Factory<MarketDataInterface, OrderInterface, model::MarketDataObject>>(config);
    PLOG_DEBUG << "Initializing strategy " << config->get("name");
    factory->initStrategy();
    auto strategy = factory->getStrategy();
    while (strategy->shouldEvaluate())
    {
        if (sig_caught) {
            PLOG_DEBUG << "Received SIGHUP signal - Exiting!";
            return sig_caught;
        }
        strategy->evaluate();
    }

    return 0;
}
