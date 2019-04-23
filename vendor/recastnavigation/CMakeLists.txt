#------------------------------------------------------------------------------
# We require CMake version 3.5 or newer.
cmake_minimum_required(VERSION 3.5...3.14)

#------------------------------------------------------------------------------
# Configure CMake policies, to ensure the system behaviour is consistent.
# See "cmake --help-policy CMP0003"
# Library linking does not produce linker search paths
cmake_policy(SET CMP0003 NEW)
# See "cmake --help-policy CMP0005"
# Preprocessor definitions are automatically quoted
cmake_policy(SET CMP0005 NEW)
# see "cmake --help-policy CMP0010"
# Bad variable references will be considered errors
cmake_policy(SET CMP0010 NEW)
# see "cmake --help-policy CMP0014"
# Input directories must have CMakeLists.txt
cmake_policy(SET CMP0014 NEW)
# see "cmake --help-policy CMP0042"
# `MACOSX_RPATH` is enabled by default.
cmake_policy(SET CMP0042 NEW)
# see "cmake --help-policy CMP0048"
# `PROJECT_VERSION` is set using project() directive.
cmake_policy(SET CMP0048 NEW)

#------------------------------------------------------------------------------
# Initialize project.
project("recastnavigation" VERSION 1.5.1 LANGUAGES CXX)

#------------------------------------------------------------------------------
# We require C++11 standard support by default.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#------------------------------------------------------------------------------
# ... and build what we have
add_subdirectory(DebugUtils)
add_subdirectory(Detour)
add_subdirectory(DetourTileCache)
add_subdirectory(DetourCrowd)
add_subdirectory(Recast)
