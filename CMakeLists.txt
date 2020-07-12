#------------------------------------------------------------------------------
# We require CMake version 3.5 or newer.
cmake_minimum_required(VERSION 3.5...3.16)

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
project("wowstack" VERSION 0.1.0 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Extend the search path used for CMake modules. This will allow us to include
# custom macros, functions and find_package modules.
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/macros")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/packages")

#------------------------------------------------------------------------------
# We require C++17 standard support by default.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#------------------------------------------------------------------------------
# We don't allow in-source builds. This causes no end of troubles.
include(PreventInSourceBuilds)

#------------------------------------------------------------------------------
# Include [Cotire](https://github.com/sakra/cotire) early on
include(Cotire OPTIONAL RESULT_VARIABLE HAS_COTIRE)

#------------------------------------------------------------------------------
# We do build in Release mode by default to provide the fastest build
# experience.
set(CMAKE_BUILD_TYPE_INIT "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE_INIT}' as none was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release MinSizeRel RelWithDebInfo"
        FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

#------------------------------------------------------------------------------
# Ensure we print configuration summary only on the initial CMake run
if (NOT EXECUTABLE_OUTPUT_PATH)
    set(PROJECT_FIRST_RUN "TRUE")
endif ()

#------------------------------------------------------------------------------
# Redirect output files
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "" FORCE)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "" FORCE)

#------------------------------------------------------------------------------
# Configure application information and version
include(ProjectSetup)

#------------------------------------------------------------------------------
# Enable tests
include(CTest)
enable_testing(true)

#------------------------------------------------------------------------------
# Configure build architecture and platform
include(CheckArchitecture)
target_architecture(PROJECT_ARCHITECTURE)

include(CheckPlatform)
target_platform(PROJECT_PLATFORM)

#------------------------------------------------------------------------------
# Include the platform-specific file. To allow exceptions, this code looks for
# files in order of how specific they are. If there is, for example, a generic
# Linux.cmake and a version-specific Linux-2.6.28-11-generic, it will pick
# Linux-2.6.28-11-generic and include it. It is then up to the file writer to
# include the generic version if necessary.
message(STATUS "")
foreach (_base
    ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR}
    ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION}
    ${CMAKE_SYSTEM_NAME})
    set(_file ${CMAKE_CURRENT_SOURCE_DIR}/cmake/platforms/${_base}.cmake)
    if (EXISTS ${_file})
        include(${_file})
        break()
    endif ()
endforeach ()

#------------------------------------------------------------------------------
# Include the compiler-specific file. To allow exceptions, this code looks for
# files in order of how specific they are. If there is, for example, a generic
# GNU.cmake and a version-specific GNU-4.8.2.cmake, it will pick GNU-4.8.2.cmake
# and include it. It is then up to the file writer to include the generic
# version if necessary.
message(STATUS "")
foreach (_base
    ${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}
    ${CMAKE_CXX_COMPILER_ID})
    set(_file ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compilers/${_base}.cmake)
    if (EXISTS ${_file})
        include(${_file})
        break()
    endif ()
endforeach ()

#-----------------------------------------------------------------------------
# Prepare the installation layout for the current build. Layout is selected
# based on PROJECT_PLATFORM, but can be overridden by the user.
message(STATUS "")
include(AutoCollectSources)
include(GroupSources)
include(InstallLayout)

# Set commonly used variables
if (WIN32)
    set(DEFAULT_WOWSTACK_HOME "C:/Program Files/WowStack/Server-${PROJECT_VERSION}")
    set(SHAREDIR share)
    set(DATADIR data)
else ()
    set(DEFAULT_WOWSTACK_HOME ${CMAKE_INSTALL_PREFIX})
    set(SHAREDIR ${DEFAULT_WOWSTACK_HOME}/${INSTALL_SHAREDIR})
    set(DATADIR ${DEFAULT_WOWSTACK_HOME}/${INSTALL_DATADIR})
endif ()

set(DEFAULT_BASEDIR "${DEFAULT_WOWSTACK_HOME}")
set(DEFAULT_CHARSET_HOME "${DEFAULT_WOWSTACK_HOME}")
if (SYSCONFDIR)
    set(DEFAULT_SYSCONFDIR "${SYSCONFDIR}")
elseif (NOT SYSCONFDIR)
    set(SYSCONFDIR "${DEFAULT_WOWSTACK_HOME}/etc")
endif ()

#------------------------------------------------------------------------------
# ... and finally start working, and build dependencies.
add_subdirectory(vendor)

#------------------------------------------------------------------------------
# Install global documentation
if (UNIX)
    install(FILES Docs/mysql.info DESTINATION ${INSTALL_INFODIR} OPTIONAL COMPONENT Info)
endif ()

#
# RPM installs documentation directly from the source tree
#
if (NOT INSTALL_LAYOUT MATCHES "RPM")
    install(FILES CODE_OF_CONDUCT.md DESTINATION ${INSTALL_DOCREADMEDIR} COMPONENT Readme)
    install(FILES CONTRIBUTING.md DESTINATION ${INSTALL_DOCREADMEDIR} COMPONENT Readme)
    install(FILES LICENSE.md DESTINATION ${INSTALL_DOCREADMEDIR} COMPONENT Readme)
    install(FILES README.md DESTINATION ${INSTALL_DOCREADMEDIR} COMPONENT Readme)
endif ()

#------------------------------------------------------------------------------
# Packaging
#------------------------------------------------------------------------------
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else ()
    set(CPACK_GENERATOR "TGZ")
endif ()

include(CPack)

#-----------------------------------------------------------------------------
# Dump generated headers and add custom target for version and configuration
# information.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/wowstack-config.h)

add_custom_target("wowstack-config" ALL
    SOURCES "${CMAKE_BINARY_DIR}/wowstack-config.h"
    )

#------------------------------------------------------------------------------
# ... and be nice and summarize what we will build for the user.
include(ProjectInfo)

#------------------------------------------------------------------------------
# ... and finally after so much preparation our own stuff. Yay!
add_subdirectory(lib)
