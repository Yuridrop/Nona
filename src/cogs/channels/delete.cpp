// Standard library imports.

#include <iostream>
#include <string>
#include <chrono>

// External library imports.

#include <dpp/dpp.h>

// Custom module imports.

#include "../../misc/colours.h"
#include "../../misc/time.h"
#include "../../redis/precaching.h"
#include "../../redis/rate_limiter.h"

void delete_channel(dpp::cluster &Nona , dpp::snowflake guild_id , dpp::snowflake channel_to_delete_id , std::shared_ptr<RateLimiter> limiter) {

    /*
    Delete a channel in the server.
    */

    limiter -> acquire();

    if (std::find(channels.begin() , channels.end() , channel_to_delete_id) != channels.end()) {
        auto start = std::chrono::high_resolution_clock::now();
        try {
            Nona.channel_delete(channel_to_delete_id , [channel_to_delete_id , start](const dpp::confirmation_callback_t &callback) {
                const dpp::channel &deleted_channel = std::get<dpp::channel>(callback.value);
                auto end = std::chrono::high_resolution_clock::now();
                if (callback.is_error()) {
                    std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred creating the channel " << deleted_channel.name<< ": " << callback.get_error().message << std::endl;
                }
                else {
                    std::chrono::duration<double> elapsed = end - start;
                    std::cout << MAG << "[ " << getCurrentTime() << " ] " << GRN << "Deleted the channel " << deleted_channel.name << " in " << elapsed.count() << " seconds." << std::endl;
                    channels.erase(std::remove(channels.begin() , channels.end() , channel_to_delete_id) , channels.end());
                }
            });
        }
        catch (std::exception error) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ channels::delete.cpp ] Unable to delete the channel with ID " << channel_to_delete_id << ": " << error.what() << std::endl;
        }
    }

}