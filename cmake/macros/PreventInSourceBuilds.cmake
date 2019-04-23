# This function will check if the build should be executed in the applications
# source directory. If so, it will prevent the build and advise on proper build
# strategies.

function(AssureOutOfSourceBuilds)
    # make sure the user doesn't play dirty with symbolic links
    get_filename_component(srcdir "${PROJECT_SOURCE_DIR}" REALPATH)
    get_filename_component(bindir "${CMAKE_BINARY_DIR}" REALPATH)

    if ("${srcdir}" STREQUAL "${bindir}")
        message("In source builds are not recommended.")
        message("\n Remove generated files and try again, e.g.:")
        message("\n ")
        message("\n rm CMakeCache.txt")
        message("\n rm -r CMakeFiles")
        message("\n mkdir _build")
        message("\n cd _build")
        message("\n cmake ../")
        message(FATAL_ERROR "Quitting CMake configuration.")
    endif ()
endfunction()

AssureOutOfSourceBuilds()
