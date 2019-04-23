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
project("utf8cpp" VERSION 2.3.4 LANGUAGES CXX)

#------------------------------------------------------------------------------
# ... and build what we have

CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(utf8cpp INTERFACE)

CollectIncludeDirectories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_INCLUDES
)

target_include_directories(utf8cpp
    INTERFACE
    ${PUBLIC_INCLUDES}
    )
