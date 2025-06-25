// Standard library imports.

#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <future>
#include <vector>
#include <fstream>

// External library imports.

#include "dpp/dpp.h"
#include "nlohmann/json.hpp"

// Custom module imports.

#include "misc/colours.h"
#include "misc/time.h"
#include "misc/help.h"
#include "interface/loadGUI.h"
#include "interface/loadCLI.h"
#include "client.h"

using json = nlohmann::json;

int main(int argc, char* argv[]) {

    /*
    The entry function for Nona.
    */

    // Handle command-line flag arguments.

    char* mode = nullptr;

    if (argc > 1) {
        if (argc >= 2) {
            if (strcmp(argv[1] , "--help") == 0 || strcmp(argv[1] , "-h") == 0) {
                std::cout << MAG << "[ " << getCurrentTime() << " ] " << WHT << "Command selected: help" << std::endl;
                (argv[2] != nullptr) ? help(argv[2]) : help();
            }
            else if (strcmp(argv[1] , "--gui") == 0 || strcmp(argv[1] , "-g") == 0) {
                std::cout << MAG << "[ " << getCurrentTime() << " ] " << WHT << "Mode selected: GUI" << std::endl;
                mode = (char*)"g";
            }
            else if (strcmp(argv[1] , "--cli") == 0 || strcmp(argv[1] , "-c") == 0) {
                std::cout << MAG << "[ " << getCurrentTime() << " ] " << WHT << "Mode selected: CLI" << std::endl;
                mode = (char*)"c";
            }
            else {
                std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "That is not a valid mode, please try again." << std::endl;
            }
        }
    }
    else {
        mode = "c";
    }

    // Detect operating system, if Windows hard-select CLI.

    #ifdef _WIN64
        mode = (char*)"c";
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << WHT << "Windows detected: hardcoded CLI mode." << std::endl;
        std::system("cls");
        std::system("title Nona");
    #elif __linux__
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << WHT << " perating system detected: Linux." << std::endl;
        std::system("clear");
    #endif

    // Load the client.json configuration file.

    std::ifstream client("../../config/client.json");
    if (!client) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "Unable to open commands.json." << std::endl;
    }

    json config;
    client >> config;

    std::vector<std::string> tokens = config["Nona"]["Discord"]["Tokens"];
    if (tokens.size() > 1) {
        std::string userToken = config["Nona"]["Discord"]["userToken"];
        if (userToken.empty()) {
            std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "To use more than bot, a user token (with guild permissions) must be provided in client.json." << std::endl;
        }
    }
    std::cout << MAG << "[ " << getCurrentTime() << " ]" << WHT << "Nona's token has been loaded." << std::endl;

    std::vector<std::thread> botThreads;
    for (size_t i = 0; i < tokens.size(); ++i) {
        botThreads.emplace_back([i , &tokens]() {
            std::string token = tokens[i];
            dpp::cluster Nona(token);
            loadEvents(Nona , i);
            loadCogs(Nona); // Potentially redundant?
            Nona.start(dpp::st_wait);
        });
    }

    for (auto &thread : botThreads) {
        thread.detach();
    }

    // Manage mode selection.

    // c = Command Line Interface | ( CLI )
    // g = Graphical User Interface | ( GUI )

    (mode == "g") ? loadGUI() : loadCLI();

}