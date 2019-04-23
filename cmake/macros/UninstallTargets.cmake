# This file provides a make uninstall target for UNIX and APPLE platforms.
# http://www.cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F

if (NOT EXISTS "@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt\"")
endif (NOT EXISTS "@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt")

file(READ "@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"${file}\"")
    if (EXISTS "${file}")
        exec_program(
                "@CMAKE_COMMAND@" ARGS "-E remove \"${file}\""
                OUTPUT_VARIABLE rm_out
                RETURN_VALUE rm_retval
        )
        if ("${rm_retval}" STREQUAL 0)
        else ("${rm_retval}" STREQUAL 0)
            message(FATAL_ERROR "Problem when removing \"${file}\"")
        ENDIF ("${rm_retval}" STREQUAL 0)
    else (EXISTS "${file}")
        message(STATUS "File \"${file}\" does not exist.")
    endif (EXISTS "${file}")
endforeach (file)
