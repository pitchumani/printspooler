cmake_minimum_required(VERSION 3.10)
project(printspooler)

find_package(SQLite3 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

# Add source files
set(SOURCES
    main.cpp
    database.cpp
    spooler.cpp
    options.cpp
)

add_executable(printspooler ${SOURCES})
target_link_libraries(printspooler PRIVATE SQLite::SQLite3)
target_include_directories(printspooler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# install the binary
install(TARGETS printspooler DESTINATION bin)
