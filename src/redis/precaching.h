#ifndef PRECACHE_H
#define PRECACHE_H

#include <string>
#include <dpp/dpp.h>

extern std::vector<dpp::snowflake> channels;

void precache_objects(dpp::cluster &Nona , dpp::snowflake guild_id_str);

#endif