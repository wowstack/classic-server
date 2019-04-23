# This provides default settings for MSVC (Microsoft Visual Studio (microsoft.com)).
set(PROJECT_COMPILER "${CMAKE_CXX_COMPILER_ID}")

#-----------------------------------------------------------------------------
# Compiler specific dependencies

#-----------------------------------------------------------------------------
# Compiler specific definitions
add_definitions(/D_CRT_NONSTDC_NO_DEPRECATE /D_CRT_SECURE_NO_DEPRECATE /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_DEPRECATE /D_CONSOLE)

# ensure Unicode friendly APIs are used on Windows
add_definitions(-DUNICODE -D_UNICODE)

# minimize windows.h content
add_definitions(-DWIN32_LEAN_AND_MEAN)

#-----------------------------------------------------------------------------
# Compiler specific flags

#-----------------------------------------------------------------------------
# Architecture specific flags

if (${PROJECT_ARCHITECTURE} STREQUAL "x86_64")
    add_definitions("-D_WIN64")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
else ()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
endif ()

#-----------------------------------------------------------------------------
message(STATUS "${PROJECT_COMPILER}: compiler configuration finished.")
