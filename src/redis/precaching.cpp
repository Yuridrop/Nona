// Standard library imports.

#include <iostream>
#include <vector>
#include <string>

// External library imports.

#include <dpp/dpp.h>

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"

std::vector<dpp::channel> channels;

void precache_objects(dpp::cluster &Nona , dpp::snowflake guild_id) {

    /*
    Precache all Discord objects (channels etc).Nona
    */

    // Get all channels:

    Nona.channels_get(guild_id , [&Nona](const dpp::confirmation_callback_t &callback) {
        if (callback.is_error()) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred caching channels: " << callback.get_error().message << std::endl;
        }
        else {
            channels = std::get<std::vector<dpp::channel>>(callback.value);
        }
    });

}