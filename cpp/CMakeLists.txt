cmake_minimum_required(VERSION 3.10)
project(printspooler)

set(CMAKE_CXX_STANDARD 14)

# Add source files
set(SOURCES
    main.cpp
    options.h
)

add_executable(printspooler ${SOURCES})

target_include_directories(printspooler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# install the binary
install(TARGETS printspooler DESTINATION bin)
