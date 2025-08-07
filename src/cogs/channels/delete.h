#ifndef DELETE_H
#define DELETE_H

// External library imports.

#include <dpp/dpp.h>

// Custom module imports.

#include "../../redis/rate_limiter.h"

void delete_channel(dpp::cluster &Nona , dpp::snowflake guild_id , dpp::channel channel_to_delete , std::shared_ptr<RateLimiter> limiter);

#endif