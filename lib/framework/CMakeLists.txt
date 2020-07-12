project("wowstack-framework" VERSION 0.1.0 LANGUAGES C CXX)

#------------------------------------------------------------------------------
# We require C++17 standard support by default.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#------------------------------------------------------------------------------
# Define the framework dependencies
find_package(Boost 1.60 REQUIRED COMPONENTS filesystem program_options regex system thread)
find_package(OpenSSL 1.0 REQUIRED)
find_package(Threads QUIET)

# Database dependencies are not enforced, either one is fine
find_package(MySQL REQUIRED)

#------------------------------------------------------------------------------
# Define the wowstack-framework library
CollectSourceFiles(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(wowstack-framework
    ${PRIVATE_SOURCES}
)

CollectIncludeDirectories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_INCLUDES
)

target_include_directories(wowstack-framework
    PUBLIC
        # Provide the binary dir for all child targets
        ${CMAKE_BINARY_DIR}
        ${PUBLIC_INCLUDES}
        ${MYSQL_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(wowstack-framework
    PUBLIC
        Boost::boost
        Boost::system
        Boost::thread
        ${MYSQL_LIBRARIES}
        OpenSSL::Crypto
        Threads::Threads
        utf8cpp
)

if (BUILD_SHARED_LIBS)
    set_property(TARGET wowstack-framework PROPERTY CXX_VISIBILITY_PRESET hidden)
    set_property(TARGET wowstack-framework PROPERTY VISIBILITY_INLINES_HIDDEN ON)
endif ()

set_property(TARGET wowstack-framework PROPERTY FOLDER "libraries")
set_property(TARGET wowstack-framework PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET wowstack-framework PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET wowstack-framework PROPERTY DEBUG_POSTFIX d)

install(TARGETS wowstack-framework
    RUNTIME DESTINATION ${INSTALL_BINDIR}
    LIBRARY DESTINATION ${INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${INSTALL_LIBDIR}
    INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
)

if (MSVC)
    INSTALL_DEBUG_TARGET(wowstack-framework DESTINATION ${INSTALL_BINDIR}/Debug)
endif ()
