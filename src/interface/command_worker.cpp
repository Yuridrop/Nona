// Standard library imports.

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>

// External module imports.

#include <nlohmann/json.hpp>
#include <sw/redis++/redis++.h>
#include <dpp/dpp.h>

// Custom module imports.

#include "../misc/time.h"
#include "../misc/colours.h"
#include "../redis/precaching.h"

using json = nlohmann::json;

// Load all variables.

std::string returnChannelName() {

    /*
    Return a random channel name from the variables.json file.
    */

    std::ifstream variables("config/variables.json");
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

// Create Channels.

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
    auto result = redis.rpush("job_queue" , job.dump());
}

void push_create_channels_job(const dpp::snowflake &guild_id) {

    /*
    Create the maximum amount of channels that the guild allows
    */

    

    auto start = std::chrono::high_resolution_clock::now();
    int jobs_pushed = 0;

    while (true) {

        int current_count = channels.size();
        int available_slots = 500 - current_count;

        if (available_slots <= 0) {
            break;
        }

        push_create_channel_job(guild_id);
        jobs_pushed++;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << MAG << "[ " << getCurrentTime() << " ] " << GRN << "Created " << jobs_pushed << " channels in " << elapsed.count() << " seconds." << std::endl;

}

// Delete Channels.

void push_delete_channel_job(const dpp::snowflake &guild_id , dpp::snowflake &channel_to_delete_id) {

    /*
    Push the createchannel command to the job queue.
    */

    sw::redis::Redis redis("tcp://127.0.0.1:6379");
    json job = {
        {"command" , "delete_channel"},
        {"args" , {
            {"guild_id" , std::to_string(guild_id)},
            {"channel_to_delete" , std::to_string(channel_to_delete_id)}
        }}
    };
    auto result = redis.rpush("job_queue" , job.dump());
}