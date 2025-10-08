# Event Management Application

An application for organizing events, registering guests, and managing gift selection.

## Overview
The application is designed to simplify the organization of events and coordinate gift choices between guests.  
- An **organizer** creates an event and defines the list of available gifts.  
- An invite code is generated and can be shared with guests.  
- **Guests** can join the event using the invite code and choose one available gift.  
- Each gift can be selected by only one guest.  
- Guests can see which gifts are already taken, but not by whom.  
- The organizer can track which gifts were chosen, but cannot see the names of the guests who selected them.  

This approach removes the randomness of gift-giving and ensures that the person being celebrated receives exactly what they want, whether it’s for a birthday, holiday, or any other occasion.  

## Features
- Event creation with custom gift lists  
- Guest registration via invite code  
- Gift selection with real-time locking of occupied items  
- Roles: organizer and guest  
- JWT-based authentication  

## Technologies
- **Client (Desktop):** C++17, Qt 6 (Widgets/QML depending on the project), CMake  
- **Server:** C++, raw sockets, custom HTTP/1.1 parser, router, threading model, no high-level web frameworks, nlohmann/json  
- **Storage:** SQLite via libpqxx  
