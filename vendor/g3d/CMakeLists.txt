project(g3d VERSION 9.0.0 LANGUAGES CXX)

#------------------------------------------------------------------------------
# Define the g3d dependencies
find_package(Threads QUIET REQUIRED)
find_package(ZLIB REQUIRED)
if(APPLE)
    find_package(CoreServices QUIET REQUIRED)
endif()

#------------------------------------------------------------------------------
# Define the g3d library
set(PRIVATE_SOURCES
    src/AABox.cpp
    src/Any.cpp
    src/AnyTableReader.cpp
    src/BinaryFormat.cpp
    src/BinaryInput.cpp
    src/BinaryOutput.cpp
    src/Box.cpp
    src/Capsule.cpp
    src/CollisionDetection.cpp
    src/CoordinateFrame.cpp
    src/Crypto.cpp
    src/Cylinder.cpp
    src/debugAssert.cpp
    src/FileSystem.cpp
    src/fileutils.cpp
    src/format.cpp
    src/g3dfnmatch.cpp
    src/g3dmath.cpp
    src/GThread.cpp
    src/Line.cpp
    src/LineSegment.cpp
    src/Log.cpp
    src/Matrix3.cpp
    src/Matrix4.cpp
    src/MemoryManager.cpp
    src/PhysicsFrame.cpp
    src/Plane.cpp
    src/prompt.cpp
    src/Quat.cpp
    src/Random.cpp
    src/Ray.cpp
    src/RegistryUtil.cpp
    src/Sphere.cpp
    src/stringutils.cpp
    src/System.cpp
    src/TextInput.cpp
    src/TextOutput.cpp
    src/Triangle.cpp
    src/uint128.cpp
    src/UprightFrame.cpp
    src/Vector2.cpp
    src/Vector3.cpp
    src/Vector4.cpp
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    list(APPEND PRIVATE_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/RegistryUtil.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/G3D/RegistryUtil.h
        )
endif ()

add_library(g3d STATIC
    ${PRIVATE_SOURCES}
)

CollectIncludeDirectories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC_INCLUDES
)

target_include_directories(g3d
    PUBLIC
        # Provide the binary dir for all child targets
        ${CMAKE_BINARY_DIR}
        ${PUBLIC_INCLUDES}
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(g3d
    PRIVATE
        Threads::Threads
        ZLIB::ZLIB
)

if(APPLE)
    target_link_libraries(g3d
        PRIVATE
            ${CORESERVICES_LIBRARY}
    )
endif()

set_property(TARGET g3d PROPERTY FOLDER "vendor")
set_property(TARGET g3d PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET g3d PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})
set_property(TARGET g3d PROPERTY DEBUG_POSTFIX d)

# install(TARGETS g3d
#     RUNTIME  DESTINATION ${INSTALL_BINDIR}
#     LIBRARY  DESTINATION ${INSTALL_LIBDIR}
#     ARCHIVE  DESTINATION ${INSTALL_LIBDIR}
#     INCLUDES DESTINATION ${INSTALL_INCLUDEDIR}
# )

# if(MSVC)
#     INSTALL_DEBUG_TARGET(g3d DESTINATION ${INSTALL_BINDIR}/Debug)
# endif()
