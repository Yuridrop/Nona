// Standard library imports.

#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <future>

// External library imports.

#include "dpp/dpp.h"
#include "nlohmann/json.hpp"

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"
#include "../misc/help.h"
#include "../misc/strToLower.h"
#include "../misc/commandValidating.h"
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
        dpp::snowflake guild_id = return_guild_id();
        if (command == "createchannel") {
            push_create_channel_job(guild_id);
        }

    }

}