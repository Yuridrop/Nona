#ifndef COMMAND_WORKER_H
#define COMMAND_WORKER_H

#include <string>
#include <dpp/dpp.h>

std::string returnChannelName();
void push_create_channel_job(const dpp::snowflake &guild_id);
void push_create_channels_job(const dpp::snowflake &guild_id);
oid push_delete_channel_job(const dpp::snowflake &guild_id , dpp::snowflake &channel_to_delete_id);

#endif