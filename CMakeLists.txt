cmake_minimum_required(VERSION 3.16)
project(EventGift)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.0/msvc2022_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

if (WIN32)
    enable_language(RC)
    set(APP_ICON_RESOURCE_WINDOWS resources/appicon.rc)
endif()

add_executable(EventGift
    src/EventGift.cpp
    src/App.cpp
    src/Logger.cpp
    src/Time.cpp
    src/SessionManager.cpp
    src/ClientServer.cpp
    src/ui/StartMenu.cpp
    src/ui/StartMenu.h
    src/ui/StartMenu.ui
    src/ui/Login.cpp
    src/ui/Login.h
    src/ui/Login.ui
    src/ui/Register.cpp
    src/ui/Register.h
    src/ui/Register.ui
    src/ui/InviteGateway.cpp
    src/ui/InviteGateway.h
    src/ui/InviteGateway.ui
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
    src/ui/MainWindow.ui
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_include_directories(EventGift PRIVATE include)
target_link_libraries(EventGift PRIVATE Qt6::Widgets)
set_target_properties(EventGift PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_library(sqlite3 STATIC Server/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC Server/sqlite)

add_executable(Server
    Server/src/Server.cpp
    Server/src/DatabaseManager.cpp
    Server/src/CommandLine.cpp 
    Server/src/Bootstrap.cpp
    Server/src/Logger.cpp
    Server/src/Time.cpp
)
target_include_directories(Server PRIVATE include Server/sqlite)
target_link_libraries(Server PRIVATE 
    sqlite3
)
set_target_properties(Server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Server)