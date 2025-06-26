// Standard library imports.

#include <iostream>
#include <vector>
#include <string>

// External library imports.

#include <dpp/dpp.h>

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"

std::vector<dpp::snowflake> channels;

void precache_objects(dpp::cluster &Nona , dpp::snowflake guild_id) {

    /*
    Precache all Discord objects (channels etc).
    */

    // Get all channels:

    Nona.channels_get(guild_id , [&Nona](const dpp::confirmation_callback_t &callback) {
        if (callback.is_error()) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred caching channels: " << callback.get_error().message << std::endl;
        }
        else {
            std::unordered_map<dpp::snowflake , dpp::channel> chs = std::get<std::unordered_map<dpp::snowflake , dpp::channel>>(callback.value);
            channels.clear();
            for (const auto &[id , channel] : chs) {
                channels.push_back(id);
            }
        }
    });

}