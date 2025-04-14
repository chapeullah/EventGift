# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\EventGift_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\EventGift_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\Server_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Server_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\sqlite3_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\sqlite3_autogen.dir\\ParseCache.txt"
  "EventGift_autogen"
  "Server_autogen"
  "sqlite3_autogen"
  )
endif()
