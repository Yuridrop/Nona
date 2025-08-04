#ifndef ON_READY_H
#define ON_READY_H

#include <mutex>
#include <condition_variable>

#include "dpp/dpp.h"

extern std::mutex ready_mutex;
extern std::condition_variable all_ready_cv;
extern int ready_bots;


void on_ready_event(dpp::cluster &Nona , int clientNum , int total_bots);
dpp::snowflake return_guild_id();

#endif