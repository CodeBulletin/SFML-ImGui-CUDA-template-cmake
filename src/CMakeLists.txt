file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(main ${SOURCES})

set_target_properties(main PROPERTIES
    CXX_STANDARD 17
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
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)