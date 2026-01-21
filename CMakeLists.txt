cmake_minimum_required(VERSION 3.16)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add logger library
add_subdirectory(Logger)

# Main executable
add_executable(file_search
    main.cpp
    fileoperations.cpp)

# Include headers from root (operations.h, constants.h)
target_include_directories(file_search
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link logger library
target_link_libraries(file_search
    PRIVATE logger)
