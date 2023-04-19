# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\db_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\db_autogen.dir\\ParseCache.txt"
  "db_autogen"
  )
endif()
