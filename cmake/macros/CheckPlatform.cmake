# This file provides platform information and will detect the currently used
# operating system for the build.

set(PROJECT_PLATFORM "unknown")

# target_platform(<output_var>):
# Determines the current target platform and returns a unique platform
# identifier.
function(target_platform output_var)
    # Get the platform
    if (WIN32)
        set(TARGET_PLATFORM "Windows")
    elseif (UNIX AND NOT APPLE)
        if (CMAKE_SYSTEM_NAME MATCHES ".*Linux")
            set(TARGET_PLATFORM "Linux")
        elseif (CMAKE_SYSTEM_NAME MATCHES "kFreeBSD.*")
            set(TARGET_PLATFORM "FreeBSD")
        elseif (CMAKE_SYSTEM_NAME MATCHES "DragonFly.*|FreeBSD")
            set(TARGET_PLATFORM "FreeBSD")
        elseif (CMAKE_SYSTEM_NAME MATCHES "kNetBSD.*|NetBSD.*")
            set(TARGET_PLATFORM "NetBSD")
        elseif (CMAKE_SYSTEM_NAME MATCHES "kOpenBSD.*|OpenBSD.*")
            set(TARGET_PLATFORM "OpenBSD")
        endif ()
    elseif (APPLE)
        if (CMAKE_SYSTEM_NAME MATCHES ".*Darwin.*")
            set(TARGET_PLATFORM "Darwin")
        elseif (CMAKE_SYSTEM_NAME MATCHES ".*MacOS.*")
            set(TARGET_PLATFORM "MacOS")
        endif ()
    elseif (CMAKE_SYSTEM_NAME MATCHES "Haiku.*")
        set(TARGET_PLATFORM "Haiku")
    else ()
        set(TARGET_PLATFORM "${CMAKE_SYSTEM_NAME}")
        message_warn("${TARGET_PLATFORM} is not officially supported.")
    endif ()

    set(${output_var} "${TARGET_PLATFORM}" PARENT_SCOPE)
endfunction()
