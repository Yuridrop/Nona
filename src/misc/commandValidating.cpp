// Standard library imports.

#include <iostream>
#include <string>
#include <fstream>

// External library imports.

#include "nlohmann/json.hpp"

// Custom module imports.

#include "colours.h"
#include "time.h"

using json = nlohmann::json;

int validate(std::string command) {

    /*
    Validate the user inputted command for the CLI.
    */

    std::ifstream command_dictionary("../../config/commands.json");
    if (!command_dictionary) {
        std::cout << MAG << "[ " << getCurrentTime() << " ] " << RED << "Unable to open commands.json." << std::endl;
    }

    json commands;
    command_dictionary >> commands;

    if (commands["basic"].contains(command)) {
        return 0;
    }
    else if (commands["discord"].contains(command)) {
        return 0;
    }
    else {
        return 1;
    }

}