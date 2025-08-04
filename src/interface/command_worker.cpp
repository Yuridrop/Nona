// Standard library imports.

#include <iostream>
#include <fstream>
#include <vector>
#include <random>

// External module imports.

#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include <dpp/dpp.h>

// Custom module imports.

#include "../misc/time.h"
#include "../misc/colours.h"

using json = nlohmann::json;

// Load all variables.

std::string returnChannelName() {

    /*
    Return a random channel name from the variables.json file.
    */

    std::ifstream variables("../../config/variables.json");
    if (!variables) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "Unable to open variables.json." << std::endl;
        return "YuridropOnTop";
    }

    json channelVariables;
    variables >> channelVariables;

    if (!channelVariables.contains("channel_names") || !channelVariables["channel_names"].is_array()) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "channel_names is malformed." << std::endl;
        return "YuridropOnTop";
    }

    const auto &channels = channelVariables["channel_names"];

    if (channels.empty()) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "There are no channel name entries in the list." << std::endl;
        return "YuridropOnTop";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0 , channels.size() - 1);
    std::string randomChannel = channels[dist(gen)];

    return randomChannel;
}

void push_create_channel_job(const dpp::snowflake &guild_id) {

    /*
    Push the createchannel command to the job queue.
    */

    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    std::string name = returnChannelName();
    json job = {
        {"command" , "create_channel"},
        {"args" , {
            {"guild_id" , std::to_string(guild_id)},
            {"name" , name}
        }}
    };

    redis.rpush("job_queue" , job.dump());
}