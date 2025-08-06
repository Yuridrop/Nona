// Standard library imports.

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>

// External library imports.

#include <nlohmann/json.hpp>
#include <dpp/dpp.h>

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"
#include "../cogs/channels/create.h"

using json = nlohmann::json;

void dispatch_job(dpp::cluster &Nona , const std::string &job_json) {

    /*
    Dispatch a job from the Redis queue to the command requested.
    */

    try {
        auto job = json::parse(job_json);
        auto args = job["args"];
        std::string command = job["command"];

        // Check commands here.
        
        if (command == "create_channel") {
            dpp::snowflake guild_id = std::stoull(args["guild_id"].get<std::string>());
            std::string name = args["name"];
            create_channel(Nona , guild_id , name);
        }
        
    }
    catch (const std::exception &error) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred within Redis: " << error.what() << std::endl;
    }
}