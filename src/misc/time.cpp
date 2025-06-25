#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

string getCurrentTime() {

    /*
    Return the current time to display as prefixes for the console.
    */

    auto now = chrono::system_clock::now();                    // Get the systems current time.
    time_t currentTime = chrono::system_clock::to_time_t(now); // Convert the system time to type time_h.
    tm* localTime = localtime(&currentTime);                   // Convert the given time to the struct tm format.
    ostringstream oss;                                         // Use stringstream to format to a string type.
    oss << put_time(localTime, "%H:%M:%S");
    return oss.str();

}