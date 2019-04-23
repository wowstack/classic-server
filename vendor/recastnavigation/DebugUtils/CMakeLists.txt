project(DebugUtils VERSION 1.5.1 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Define the DebugUtils library
CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
	# Exclude
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(DebugUtils STATIC
	${PRIVATE_SOURCES}
	)

add_library(RecastNavigation::DebugUtils ALIAS DebugUtils)

target_compile_definitions(DebugUtils
	PUBLIC
		"DT_POLYREF64=1"
)

target_compile_options(DebugUtils PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/fp:fast>)

CollectIncludeDirectories(
	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC_INCLUDES
)

target_include_directories(DebugUtils
	PUBLIC
	# Provide the binary dir for all child targets
	${CMAKE_BINARY_DIR}
	${PUBLIC_INCLUDES}
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	)

target_link_libraries(DebugUtils
	PUBLIC
		Detour
		DetourTileCache
)

set_property(TARGET DebugUtils PROPERTY FOLDER "vendor")
set_property(TARGET DebugUtils PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET DebugUtils PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET DebugUtils PROPERTY DEBUG_POSTFIX d)

# install(TARGETS DebugUtils
#     RUNTIME  DESTINATION ${INSTALL_BINDIR}
#     LIBRARY  DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE  DESTINATION ${INSTALL_LIBDIR}
#     INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(DebugUtils DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
