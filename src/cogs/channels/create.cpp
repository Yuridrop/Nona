// Standard library imports.

#include <iostream>
#include <string>
#include <chrono>

// External library imports.

#include <dpp/dpp.h>

// Custom module imports.

#include "../../misc/colours.h"
#include "../../misc/time.h"

void create_channel(dpp::cluster &Nona , const dpp::snowflake guild_id , const std::string channelName) {

    /*
    Create a channel in the server.
    */

    dpp::channel new_channel;
    new_channel.guild_id = guild_id;
    new_channel.name = channelName;
    new_channel.set_type(dpp::channel_type::CHANNEL_TEXT);

    auto start = std::chrono::high_resolution_clock::now();
    Nona.channel_create(new_channel , [channelName , start](const dpp::confirmation_callback_t &callback) {
        auto end = std::chrono::high_resolution_clock::now();
        if (callback.is_error()) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred creating the channel " << channelName << ": " << callback.get_error().message << std::endl;
        }
        else {
            std::chrono::duration<double> elapsed = end - start;
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << GRN << "Created the channel " << channelName << " in " << elapsed.count() << " seconds." << std::endl;
        }
    });
}