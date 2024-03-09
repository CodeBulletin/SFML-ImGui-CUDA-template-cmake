add_library(external INTERFACE)

set_target_properties(external PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

#SFML
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)

add_subdirectory(SFML)
set(SFML_DIR ${PROJECT_BINARY_DIR}/external/SFML)

#ImGui
set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ImGui)
file(GLOB IMGUI_SOURCES ${IMGUI_SOURCE_DIR}/*.cpp)
add_library(ImGui STATIC ${IMGUI_SOURCES})

#ImGui-SFML
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ImGui)
set(IMGUI_SFML_FIND_SFML OFF)
message(STATUS "SFML_DIR: ${SFML_DIR}")

add_subdirectory(ImGui-SFML)

target_include_directories(external INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui-SFML
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGui
)

target_link_libraries(external INTERFACE
    sfml-graphics
    sfml-window
    sfml-system
    ImGui
    ImGui-SFML::ImGui-SFML
)