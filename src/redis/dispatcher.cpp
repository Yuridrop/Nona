// Standard library imports.

#include <iostream>
#include <string>

// External library imports.

#include <nlohmann/json.hpp>
#include <dpp/dpp.h>

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"

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

        
        
    }
    catch (const std::exception &error) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred within Redis: " << error.what() << std::endl;
    }
}