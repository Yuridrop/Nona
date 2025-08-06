// Standard library imports.

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// External library imports.

#include "dpp/dpp.h"
#include "sw/redis++/redis++.h"

// Custom module imports.

#include "../misc/colours.h"
#include "../misc/time.h"
#include "../redis/dispatcher.h"
#include "../redis/precaching.h"

std::mutex ready_mutex;
std::condition_variable all_ready_cv;
int ready_bots = 0;

void on_ready_event(dpp::cluster& Nona , int client_number , int total_bots) {

    /*
    The event that is called for each iteration of Nona.
    */

    Nona.on_ready([&Nona , client_number , total_bots](const dpp::ready_t& event) {

        try {
            dpp::activity botActivity;
            botActivity.type = dpp::activity_type::at_game;
            botActivity.name = "EZ4Yuridrop...";

            Nona.set_presence(dpp::presence(dpp::ps_online , botActivity));
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << GRN << "Nona #" << client_number << " (" << Nona.me.username << ") is online." << std::endl;

            // Redis logic

            std::thread worker([&Nona]() {
                try {
                    sw::redis::Redis redis("tcp://127.0.0.1:6379/0");
                    while (true) {
                        auto reply = redis.blpop("job_queue", 0);
                        if (reply) {
                            std::string job_string = reply -> second;
                            dispatch_job(Nona , job_string);
                        }
                    }
                } catch (const std::exception &error) {
                    std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ on_ready.cpp ] Redis error: " << error.what() << std::endl;
                }
            });
            worker.detach();

            {
                std::lock_guard<std::mutex> lock(ready_mutex);
                ready_bots++;
                if (ready_bots == total_bots) {
                    all_ready_cv.notify_one();
                }
            }
        } catch (const std::exception& error) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "[ ERROR ][ on_ready.cpp ] Error in on_ready for Nona #" << client_number << ": " << error.what() << std::endl;
        }
    });
}