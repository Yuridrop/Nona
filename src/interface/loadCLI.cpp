// Standard library imports.

#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <future>
#include <functional>
#include <unordered_map>

// External library imports.

#include "dpp/dpp.h"
#include "nlohmann/json.hpp"

// Custom module imports.

#include "../index.h"
#include "../misc/colours.h"
#include "../misc/time.h"
#include "../misc/help.h"
#include "../misc/strToLower.h"
#include "../misc/validate_command.h"
#include "../events/on_ready.h"
#include "command_worker.h"

using json = nlohmann::json;

void loadCLI() {

    /*
    Load the Command Line Interface.
    */

    std::string bannerASCII = R"(
 ███▄    █  ▒█████   ███▄    █  ▄▄▄      
 ██ ▀█   █ ▒██▒  ██▒ ██ ▀█   █ ▒████▄    
▓██  ▀█ ██▒▒██░  ██▒▓██  ▀█ ██▒▒██  ▀█▄  
▓██▒  ▐▌██▒▒██   ██░▓██▒  ▐▌██▒░██▄▄▄▄██ 
▒██░   ▓██░░ ████▓▒░▒██░   ▓██░ ▓█   ▓██▒
░ ▒░   ▒ ▒ ░ ▒░▒░▒░ ░ ▒░   ▒ ▒  ▒▒   ▓▒█░
░ ░░   ░ ▒░  ░ ▒ ▒░ ░ ░░   ░ ▒░  ▒   ▒▒ ░
   ░   ░ ░ ░ ░ ░ ▒     ░   ░ ░   ░   ▒   
         ░     ░ ░           ░       ░  ░
)";

    std::cout << MAG << bannerASCII;

    while (true) {

        #ifdef _WIN64
            #include <windows.h>
            sleep(1);
        #elif __linux__
            #include <unistd.h>
            sleep(1);
        #endif

        std::cout << MAG << "\n[ " << getCurrentTime() << " ]" << WHT << " Please enter a command: ";

        std::string line;
        std::getline(std::cin , line);

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        command = lowerString(command);

        std::vector<std::string> args;
        std::string word;
        while (iss >> word) {
            args.push_back(word);
        }

        // Command maps

        std::unordered_map<std::string, std::function<void(std::string)>> basic_functions = {
            {"help", [](const std::string &arg) { help(arg); }}
        };

        std::unordered_map<std::string, std::function<void(dpp::snowflake)>> discord_functions = {
            {"createchannel", push_create_channel_job}
        };

        if (!validate(command)) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ loadCLI.cpp ] " << command << " is not a valid command. To see a list of commands please use \"help\"." << std::endl;
            continue;
        }

        try {
            auto discord_fn = discord_functions.find(command);
            auto basic_fn = basic_functions.find(command);

            if (discord_fn != discord_functions.end()) {
                discord_fn -> second(guild_id);
            } else if (basic_fn != basic_functions.end()) {
                std::string arg = args.empty() ? "default" : args[0];
                basic_fn -> second(arg);
            } else {
                std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ loadCLI.cpp ] No handler found for command: " << command << std::endl;
            }

        } catch (const std::exception& error) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ loadCLI.cpp ] Unable to run the command " << command << ": " << error.what() << std::endl;
        }
    }

}