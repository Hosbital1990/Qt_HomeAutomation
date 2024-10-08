# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "RelWithDebInfo")
  file(REMOVE_RECURSE
  "CMakeFiles/HomeAutomation_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/HomeAutomation_autogen.dir/ParseCache.txt"
  "HomeAutomation_autogen"
  )
endif()
