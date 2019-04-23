# This file provides project version and naming informations for the build
# process.

#-----------------------------------------------------------------------------
# Update the version, then:
#   WOWSTACK_MICRO_VERSION += 1;
#   WOWSTACK_INTERFACE_AGE += 1;
#   WOWSTACK_BINARY_AGE += 1;
#
# Flight rules:
# * if any functions have been added, set WOWSTACK_INTERFACE_AGE to 0.
# * if backwards compatibility has been broken,
#   set WOWSTACK_BINARY_AGE and WOWSTACK_INTERFACE_AGE to 0.
set(WOWSTACK_MAJOR_VERSION 0)
set(WOWSTACK_MINOR_VERSION 1)
set(WOWSTACK_MICRO_VERSION 0)
set(WOWSTACK_VERSION "${WOWSTACK_MAJOR_VERSION}.${WOWSTACK_MINOR_VERSION}.${WOWSTACK_MICRO_VERSION}")

#-----------------------------------------------------------------------------
# Calculate a libtool-like version number
set(WOWSTACK_INTERFACE_AGE 0)
set(WOWSTACK_BINARY_AGE 0)

math(EXPR WOWSTACK_LT_CURRENT "${WOWSTACK_MICRO_VERSION} - ${WOWSTACK_INTERFACE_AGE}")
math(EXPR WOWSTACK_LT_AGE "${WOWSTACK_BINARY_AGE} - ${WOWSTACK_INTERFACE_AGE}")
math(EXPR WOWSTACK_LT_MAJOR "${WOWSTACK_LT_CURRENT}- ${WOWSTACK_LT_AGE}")

# Set libtool-like version numbers
set(WOWSTACK_LT_REVISION "${WOWSTACK_INTERFACE_AGE}")
set(WOWSTACK_LT_RELEASE "${WOWSTACK_MAJOR_VERSION}.${WOWSTACK_MINOR_VERSION}")
set(WOWSTACK_LT_VERSION "${WOWSTACK_LT_MAJOR}.${WOWSTACK_LT_AGE}.${WOWSTACK_LT_REVISION}")

#-----------------------------------------------------------------------------
# Configure project options
option(BUILD_SHARED_LIBS "Generate dynamic instead of static libraries." OFF)

include(Helpers)

#-----------------------------------------------------------------------------
# Set up map tools options
set_option(TOOLS                           "Build map related tools" ON)
set(TOOLS_OPTIONS      MapExtract VmapExtract VmapAssemble MmapGenerate)
foreach(_SUB ${TOOLS_OPTIONS})
    string(TOUPPER "TOOLS_${_SUB}" _OPT)
    dep_option(${_OPT}          "Enable ${_SUB} support" ON "TOOLS" OFF)
endforeach()
