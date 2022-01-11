#include <signal.h>
#include <iostream>
#include <memory>

#include <boost/program_options.hpp>
#include <boost/exception/exception.hpp>

#include "Utils.h"
#include "Config.h"
#include "Factory.h"
#include "MarketData.h"
#include "OrderInterface.h"


static volatile sig_atomic_t sig_caught = 0;

void handle_sighup(int signum)
{
    if (signum == SIGHUP)
        sig_caught = 1;
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

    signal(SIGHUP, handle_sighup);

    auto factory = std::make_unique<Factory<MarketData, OrderInterface>>(config);
    LOGINFO("Initializing strategy");
    factory->initStrategy();
    auto strategy = factory->getStrategy();
    while (strategy->shouldEvaluate())
    {
        if (sig_caught) {
            LOGINFO("Received SIGHUP signal - Exiting!");
            return sig_caught;
        }
        strategy->evaluate();
    }

    return 0;
}
