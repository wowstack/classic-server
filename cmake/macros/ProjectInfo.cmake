# This file provides a summary for the created build configuration.
# Note that the build information is only printed if the CMake cache has not
# yet been initialized.

if (PROJECT_FIRST_RUN)
    message(STATUS "")
    #--------------------------------------------------------------------------
    # Build summary
    message(STATUS "Build summary")
    message(STATUS "")

    #--------------------------------------------------------------------------
    # Version information
    message(STATUS "Version:        ${PROJECT_NAME} ${PROJECT_VERSION}")
    message(STATUS "")

    #--------------------------------------------------------------------------
    # System information
    message(STATUS "Target platform information")
    message(STATUS "Architecture:   ${PROJECT_ARCHITECTURE}")
    message(STATUS "Platform:       ${PROJECT_PLATFORM}")
    message(STATUS "")

    #--------------------------------------------------------------------------
    # Compilation and linker settings
    message(STATUS "Build information")
    message(STATUS "Compiler:       ${PROJECT_COMPILER}")
    message(STATUS "Build type:     ${CMAKE_BUILD_TYPE}")
    message(STATUS "")

    #--------------------------------------------------------------------------
    # User selected build options
    message(STATUS "Options")
    list(SORT ALLOPTIONS)
    foreach(_SUB ${ALLOPTIONS})
        string(LENGTH ${_SUB} _SUBLEN)
        math(EXPR _PADLEN "20 - ${_SUBLEN}")
        string(RANDOM LENGTH ${_PADLEN} ALPHABET " " _PADDING)
        string(TOUPPER ${_SUB} _OPT)
        message_bool_option(${_SUB} ${_OPT} ${_PADDING})
    endforeach()

    #--------------------------------------------------------------------------
    # Installation settings
    message(STATUS "Installing to:  ${DEFAULT_BASEDIR} (${INSTALL_LAYOUT} layout)")
    message(STATUS "")
endif ()
