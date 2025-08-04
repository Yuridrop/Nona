#ifndef CLIENT_H
#define CLIENT_H

#include "dpp/dpp.h"

void loadEvents(dpp::cluster &Nona , int clientNum , int total_bots);
void loadCogs(dpp::cluster &Nona);
void loadCommand(dpp::cluster &Nona , int command , dpp::snowflake guild_id);

#endif