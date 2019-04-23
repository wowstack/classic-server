project(DetourTileCache VERSION 1.5.1 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Define the DetourTileCache library
CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(DetourTileCache STATIC
	${PRIVATE_SOURCES}
)

add_library(RecastNavigation::DetourTileCache ALIAS DetourTileCache)

target_compile_definitions(DetourTileCache PUBLIC DT_POLYREF64)
target_compile_options(DetourTileCache PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/fp:fast>)

CollectIncludeDirectories(
	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC_INCLUDES
)

target_include_directories(DetourTileCache
	PUBLIC
		# Provide the binary dir for all child targets
		${CMAKE_BINARY_DIR}
		${PUBLIC_INCLUDES}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(DetourTileCache
	PUBLIC
		Detour
		Recast
)

set_property(TARGET DetourTileCache PROPERTY FOLDER "vendor")
set_property(TARGET DetourTileCache PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET DetourTileCache PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET DetourTileCache PROPERTY DEBUG_POSTFIX d)

# install(TARGETS DetourTileCache
#     RUNTIME  DESTINATION ${INSTALL_BINDIR}
#     LIBRARY  DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE  DESTINATION ${INSTALL_LIBDIR}
#     INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(DetourTileCache DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
