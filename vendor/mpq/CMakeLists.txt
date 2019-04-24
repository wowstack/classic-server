project(mpq4 VERSION 0.4.2 LANGUAGES C)

#------------------------------------------------------------------------------
# Define the mpq4 dependencies
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)

#------------------------------------------------------------------------------
# Define the mpq4 library
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(mpq4 STATIC
    ${PRIVATE_SOURCES}
)

CollectIncludeDirectories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_INCLUDES
    # Exclude
    ${CMAKE_CURRENT_SOURCE_DIR}/win
)


include(CheckIncludeFiles)
include(CheckFunctionExists)

check_include_files(dlfcn.h HAVE_DLFCN_H)
check_function_exists(fseeko HAVE_FSEEKO)
check_include_files(inttypes.h HAVE_INTTYPES_H)
set(HAVE_LIBBZ2 1)
set(HAVE_LIBZ 1)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)

#Taken from https://github.com/jonathanslenders/fluidsynth/blob/master/cmake_admin/CheckSTDC.cmake
check_include_files("dlfcn.h;stdint.h;stddef.h;inttypes.h;stdlib.h;strings.h;string.h;float.h" StandardHeadersExist)
if (StandardHeadersExist)
  set(STDC_HEADERS 1)
else()
  set(STDC_HEADERS 0)
endif()

set(LIBMPQ_PACKAGE_VERSION "0.4.2")
set(LIBMPQ_PACKAGE_NAME "libmpq")

#------------------------------------------------------------------------------
# Generate config.h
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h)

target_include_directories(mpq4
    PUBLIC
        # Provide the binary dir for all child targets
        ${CMAKE_BINARY_DIR}
        ${PUBLIC_INCLUDES}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        $<$<BOOL:${WIN32}>:${CMAKE_CURRENT_SOURCE_DIR}/win>
    )

target_link_libraries(mpq4
    PRIVATE
        BZip2::BZip2
        ZLIB::ZLIB
    )

set_property(TARGET mpq4 PROPERTY FOLDER "vendor")
set_property(TARGET mpq4 PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET mpq4 PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET mpq4 PROPERTY DEBUG_POSTFIX d)

# install(TARGETS mpq4
#     RUNTIME       DESTINATION ${INSTALL_BINDIR}
#     LIBRARY       DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE       DESTINATION ${INSTALL_LIBDIR}
#     FRAMEWORK     DESTINATION /Library/Frameworks
#     PUBLIC_HEADER DESTINATION include
#     INCLUDES      DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(mpq DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
