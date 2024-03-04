#include <config.h>
#include "AppExample.hpp"

#if defined(LOG_LEVEL) && LOG_LEVEL > 0

    #include <iostream>

#endif

int main() {
    #if defined(LOG_LEVEL) && LOG_LEVEL == LOG_INFO

        std::cout << "Name: " << NAME << "\n";
        std::cout << "Description: " << DESCRIPTION << "\n";
        std::cout << "Version: " << MAJOR_VERSION << "." << MINOR_VERSION << "." << PATCH_VERSION << "\n";
        std::cout << "Author: " << AUTHOR << "\n";
        std::cout << "Website: " << WEBSITE << "\n";
        std::cout << "License: " << LICENSE << "\n";

    #endif

    AppExample app = AppExample(std::string(NAME), 800, 600, sf::Style::Default, sf::State::Windowed);

    app.run();

    return 0;
}
