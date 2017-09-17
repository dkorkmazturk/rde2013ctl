#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include "rde2013.h"

Command processArgs(const std::vector<std::string> &args);

int main(int argc, char *argv[])
{
    std::vector<std::string> args(argv + 1, argv + argc);
    try {
        RDE2013::getInstance().sendCommand(processArgs(args));
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

Command processArgs(const std::vector<std::string> &args)
{
    if(args.size() == 3)
    {
        if(args[0] == "set")
        {
            if(args[1] == "wheel-light")
            {
                if(args[2] == "on")
                    return Command::TURN_WHEEL_LIGHT_ON;
                else if(args[2] == "off")
                    return Command::TURN_WHEEL_LIGHT_OFF;
            }

            else if(args[1] == "logo-light")
            {
                if(args[2] == "on")
                    return Command::TURN_LOGO_LIGHT_ON;
                else if(args[2] == "off")
                    return Command::TURN_LOGO_LIGHT_OFF;
            }

            else if(args[1] == "polling-rate")
            {
                if(args[2] == "1000")
                    return Command::POLLING_RATE_1000HZ;
                else if(args[2] == "500")
                    return Command::POLLING_RATE_500HZ;
                else if(args[2] == "125")
                    return Command::POLLING_RATE_125HZ;
            }
        }
    }

    throw std::runtime_error("Invalid command line argument");
}
