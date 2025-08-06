#ifndef CREATE_H
#define CREATE_H

#include <string>
#include <dpp/dpp.h>

void create_channel(dpp::cluster &Nona , const dpp::snowflake guild_id , const std::string channelName);

#endif