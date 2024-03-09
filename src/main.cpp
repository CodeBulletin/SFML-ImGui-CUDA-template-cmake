#include <config.h>
#include "AppExample.hpp"
#include <kernal/vector_add.hpp>

#if defined(LOG_LEVEL) && LOG_LEVEL > 0

#include <iostream>

#endif

int main()
{

#if defined(DEBUG_MODE)

    float a[5] = {1, 2, 3, 4, 5};
    float b[5] = {1, 2, 3, 4, 5};
    float c[5] = {0, 0, 0, 0, 0};

    kernal::vector_add(a, b, c, 5);

#if defined(LOG_LEVEL) && LOG_LEVEL == LOG_INFO

    std::cout << "Vector Add: ";
    for (int i = 0; i < 5; i++)
    {
        std::cout << c[i] << " ";
    }

#endif

    std::cout << "\n";

#endif

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
