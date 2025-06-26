#ifndef COMMAND_WORKER_H
#define COMMAND_WORKER_H

#include <string>
#include <dpp/dpp.h>

std::string returnChannelName();
void push_create_channel_job(const dpp::snowflake &guild_id);

#endif