project(Detour VERSION 1.5.1 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Define the Detour library
CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
	# Exclude
	${CMAKE_CURRENT_SOURCE_DIR}/Source/DetourAssert.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Include/DetourAssert.h
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
	list(APPEND PRIVATE_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/Source/DetourAssert.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Include/DetourAssert.h
		)
endif ()

add_library(Detour STATIC
	${PRIVATE_SOURCES}
	)

add_library(RecastNavigation::Detour ALIAS Detour)

target_compile_definitions(Detour
	PUBLIC
		"DT_POLYREF64=1"
)

target_compile_options(Detour PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/fp:fast>)

CollectIncludeDirectories(
	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC_INCLUDES
)

target_include_directories(Detour
	PUBLIC
	# Provide the binary dir for all child targets
	${CMAKE_BINARY_DIR}
	${PUBLIC_INCLUDES}
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	)

set_property(TARGET Detour PROPERTY FOLDER "vendor")
set_property(TARGET Detour PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET Detour PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET Detour PROPERTY DEBUG_POSTFIX d)

# install(TARGETS Detour
#     RUNTIME       DESTINATION ${INSTALL_BINDIR}
#     LIBRARY       DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE       DESTINATION ${INSTALL_LIBDIR}
#     FRAMEWORK     DESTINATION /Library/Frameworks
#     PUBLIC_HEADER DESTINATION include
#     INCLUDES      DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(Detour DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
