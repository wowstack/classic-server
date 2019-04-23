project(Recast VERSION 1.5.1 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Define the Recast library
CollectSourceFiles(
	${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE_SOURCES
	# Exclude
	${CMAKE_CURRENT_SOURCE_DIR}/Source/RecastAssert.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Include/RecastAssert.cpp
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
	list(APPEND PRIVATE_SOURCES
		${CMAKE_CURRENT_SOURCE_DIR}/Source/RecastAssert.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Include/RecastAssert.h
		)
endif ()

add_library(Recast STATIC
	${PRIVATE_SOURCES}
	)

	add_library(RecastNavigation::Recast ALIAS Recast)

target_compile_definitions(Recast PUBLIC DT_POLYREF64)
target_compile_options(Recast PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/fp:fast>)

CollectIncludeDirectories(
	${CMAKE_CURRENT_SOURCE_DIR}
	PUBLIC_INCLUDES
)

target_include_directories(Recast
	PUBLIC
	# Provide the binary dir for all child targets
	${CMAKE_BINARY_DIR}
	${PUBLIC_INCLUDES}
	PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	)

set_property(TARGET Recast PROPERTY FOLDER "vendor")
set_property(TARGET Recast PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET Recast PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET Recast PROPERTY DEBUG_POSTFIX d)

# install(TARGETS Recast
#     RUNTIME  DESTINATION ${INSTALL_BINDIR}
#     LIBRARY  DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE  DESTINATION ${INSTALL_LIBDIR}
#     INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(Recast DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
