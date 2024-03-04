cmake_minimum_required(VERSION 3.28.0)

set(PROJECT_NAME "SFMLTemplate")

project(
    ${PROJECT_NAME}
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "A template for SFML projects"
    HOMEPAGE_URL "https://codebulletin.github.io"
)

set(${PROJECT_NAME}_AUTHOR "Code Bulletin")
set(${PROJECT_NAME}_LICENSE "MIT")
set(LOG_LEVEL 3)

# Dont Change
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG_MODE ON)
else()
    set(DEBUG_MODE OFF)
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

add_subdirectory(external)

add_subdirectory(src)

target_link_libraries(main PRIVATE external)