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

        std::string enteredCommand ;

        std::cout << MAG << "\n[ " << getCurrentTime() << " ]" << WHT << " Please enter a command: ";
        std::cin >> enteredCommand;
        std::string command = lowerString(enteredCommand);
        std::unordered_map<std::string , std::function<void()>> functions = {
            {"createchannel" , [guild_id]()},
            {"" , push_create_channel_job}
        };
        if (!validate(command)) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ loadCLI.cpp ] " << command << " is not a valid command. TO see a list of commands please use \"help\"." << std::endl;
        }
        else {
            
        }

    }

}