/// logger

#include <iostream>
#include <string>

void log(const std::string &message) {
    // write text to the console with timestamp as prefix

    // get current time
    time_t now = time(0);
    tm *localtm = localtime(&now);

    char timeString[80];

    // format "HH:MM:SS  "
    strftime(timeString, 80, "%H:%M:%S", localtm);

    // write to console & colorize it as red
    std::cout << "\033[1;31m"
              << "[" << timeString << "]"
              << "\033[0m"
              << " ";

    // write message to console & colorize it as white
    std::cout << "\033[1;37m"
              << message
              << "\033[0m"
              << std::endl;
}
