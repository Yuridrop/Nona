// Standard library imports.

#include <iostream>
#include <thread>

// External library imports.

#include "dpp/dpp.h"
#include "sw/redis++/redis++.h"

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"
#include "../redis/dispatcher.h"
#include "../redis/precache.h"

dpp::snowflake guild_id;

void on_ready_event(dpp::cluster& Nona , int clientNum) {

    /*
    Tell when one of Nona's clients is online and set a presence.
    */

    Nona.on_ready([&Nona , clientNum](const dpp::ready_t& event) {
        try {
            dpp::activity botActivity;
            botActivity.type = dpp::activity_type::at_game;
            botActivity.name = "EZ4Yuridrop...";

            Nona.set_presence(dpp::presence(dpp::ps_online , botActivity));
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << GRN << "Nona #" << clientNum << " (" << Nona.me.username << ") is online." << std::endl;

            if (clientNum == 0) {
                while (true) {
                    std::string guild_id_str;
                    std::cout << MAG << "[ " << getCurrentTime() << " ] " << WHT << "Please enter the ID of the guild you want to attack: " << std::endl;
                    std::cin >> guild_id_str;
                    //guild_id = std::stoull(guild_id_str);
                    for (const auto &guild : event.guilds) {
                        if (std::stoull(guild_id_str) == guild) {
                            guild_id = std::stoull(guild_id_str);
                            break;
                        }
                        else {
                            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "The guild ID " << guild_id << " is invalid, please try again." << std::endl;
                        }
                    }
                }

                precache_objects(Nona , guild_id);
            }

            // Redis logic:2

            std::thread worker([&Nona]() {
                try {
                    sw::redis::Redis redis("tcp://127.0.0.1:6379");
                    while (true) {
                        std::vector<std::string> result;
                        auto reply = redis.blpop("job_queue" , 0);
                        if (reply) {
                            std::string job_string = reply -> second;
                            dispatch_job(Nona , job_string);
                        }
                    }
                }
                catch (const std::exception &error) {
                    std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "An error occurred within Redis: " << error.what() << std::endl;
                }
            });

        }
        catch (const std::exception& error) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "Error in on_ready for bot #" << clientNum << ": " << error.what() << std::endl;
        }
    });
}