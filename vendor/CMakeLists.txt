#------------------------------------------------------------------------------
# Silence 3rd party builds
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    string(REGEX REPLACE "/W[0-4] " "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/W[0-4] " "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    add_definitions(/W0)
else ()
    add_definitions(-w)
endif ()

#------------------------------------------------------------------------------
# Include g3d project
add_subdirectory(g3d)

#------------------------------------------------------------------------------
# Include gtest project
add_subdirectory(gtest)

#------------------------------------------------------------------------------
# Include mpq project
add_subdirectory(mpq)

#------------------------------------------------------------------------------
# Include recastnavigation project
add_subdirectory(recastnavigation)

#------------------------------------------------------------------------------
# Include stormlib project
add_subdirectory(stormlib)

#------------------------------------------------------------------------------
# Include utf8cpp project
add_subdirectory(utf8cpp)
