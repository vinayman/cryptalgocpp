#include <iostream>

#include <boost/program_options.hpp>

#include "binance.h"
#include "Utils.h"
#include "Config.h"


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
        return 1;
    }

    std::shared_ptr<Config> config = std::make_shared<Config>
                                     (vm.at("config").as<std::string>());

    LOGINFO(config->get("name"));

    LOGINFO("Hello, World!");
    return 0;
}
