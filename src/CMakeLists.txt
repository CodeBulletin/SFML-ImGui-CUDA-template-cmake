file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC
    "${PROJECT_BINARY_DIR}/"
)

set_target_properties(main PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
        main
        PUBLIC -Wall
        PUBLIC -Wextra
        PUBLIC -Wpedantic
        PUBLIC -Werror
        
    )
else(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(
        main
        PUBLIC /W4
        PUBLIC /WX
    )
endif()

target_include_directories(
    main
    PUBLIC "${PROJECT_SOURCE_DIR}/src/include"
)