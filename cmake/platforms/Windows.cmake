# This file includes Windows specific hacks, mostly around compiler flags.

#-----------------------------------------------------------------------------
# Platform specific dependencies

#-----------------------------------------------------------------------------
# Platform specific definitions
add_definitions(-DWIN32)

# Enable multi-threaded compiling
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

# Ignore warnings about older, less secure functions
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Ignore warnings about POSIX deprecation
add_definitions(-D_CRT_NONSTDC_NO_WARNINGS)

#-----------------------------------------------------------------------------
message(STATUS "Windows: platform configuration finished.")
