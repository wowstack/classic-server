project(DetourCrowd VERSION 1.5.1 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Define the DetourCrowd library
CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(DetourCrowd STATIC
	${PRIVATE_SOURCES}
)

add_library(RecastNavigation::DetourCrowd ALIAS DetourCrowd)

target_compile_definitions(DetourCrowd PUBLIC DT_POLYREF64)
target_compile_options(DetourCrowd PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/fp:fast>)

CollectIncludeDirectories(
	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC_INCLUDES
)

target_include_directories(DetourCrowd
	PUBLIC
		# Provide the binary dir for all child targets
		${CMAKE_BINARY_DIR}
		${PUBLIC_INCLUDES}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(DetourCrowd
	PUBLIC
		Detour
		Recast
)

set_property(TARGET DetourCrowd PROPERTY FOLDER "vendor")
set_property(TARGET DetourCrowd PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET DetourCrowd PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET DetourCrowd PROPERTY DEBUG_POSTFIX d)

# install(TARGETS DetourCrowd
#     RUNTIME  DESTINATION ${INSTALL_BINDIR}
#     LIBRARY  DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE  DESTINATION ${INSTALL_LIBDIR}
#     INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(DetourCrowd DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
