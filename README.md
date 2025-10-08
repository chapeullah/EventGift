# Event Management Application

An application for organizing events, registering guests, and managing gift selection.

## Features
- Guest registration via invite code  
- Gift selection with locking of occupied items  
- Role system: organizer and guest  
- JWT-based authentication  

## Technologies
- **Client (Desktop):** C++17, Qt 6 (Widgets/QML depending on the project), CMake  
- **Server:** C++, raw sockets, custom HTTP/1.1 parser, router, threading model, no high-level web frameworks, nlohmann/json  
- **Storage:** SQLite via libpqxx  
