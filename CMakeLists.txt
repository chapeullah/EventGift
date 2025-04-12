cmake_minimum_required(VERSION 3.16)
project(EventGift)

set(CMAKE_CXX_STANDARD 20)


add_executable(EventGift
    src/EventGift.cpp
)
target_include_directories(EventGift PRIVATE include)
set_target_properties(EventGift PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_library(sqlite3 STATIC Server/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC Server/sqlite)

add_executable(Server
    Server/src/Server.cpp
    Server/src/DatabaseManager.cpp
    Server/src/CommandLine.cpp
    Server/src/Logger.cpp
    Server/src/Time.cpp
)

target_include_directories(Server PRIVATE include Server/sqlite)
target_link_libraries(Server PRIVATE sqlite3)
set_target_properties(Server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Server)
