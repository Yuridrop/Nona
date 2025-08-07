#ifndef CREATE_H
#define CREATE_H

// External library imports.

#include <dpp/dpp.h>

// Custom module imports.

#include "../../redis/rate_limiter.h"

void create_channel(dpp::cluster &Nona , const dpp::snowflake guild_id , const std::string channelName , std::shared_ptr<RateLimiter> limiter);

#endif