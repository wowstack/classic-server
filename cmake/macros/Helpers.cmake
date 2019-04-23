# This file provides custom macros and functions which we use to fuel our build
# process.
include(CMakeDependentOption)

# message_warn(<text>):
# Displays a given <text> variable or string with a warning note.
macro(MESSAGE_WARN _TEXT)
    message(STATUS "*** WARNING: ${_TEXT}")
endmacro()

# message_error(<text>):
# Displays a given <text> variable or string with an error note and aborts the
# build process.
macro(MESSAGE_ERROR _TEXT)
    message(FATAL_ERROR "*** ERROR: ${_TEXT}")
endmacro()

# message_bool_option(<option_name> <option_value>):
# Displays <option_name> as ON/OFF switch based on <option_value>.
macro(MESSAGE_BOOL_OPTION _NAME _VALUE)
    set(_PAD " ")
    if(${ARGC} EQUAL 3)
        set(_PAD ${ARGV2})
    endif()
    if(${_VALUE})
        message(STATUS "${_NAME}:${_PAD}ON")
    else()
        message(STATUS "${_NAME}:${_PAD}OFF")
    endif()
endmacro()

macro(MESSAGE_TESTED_OPTION _NAME)
    set(_REQVALUE ${${_NAME}})
    set(_PAD " ")
    if(${ARGC} EQUAL 2)
        set(_PAD ${ARGV1})
    endif()
    if(NOT HAVE_${_NAME})
        set(HAVE_${_NAME} OFF)
    elseif("${HAVE_${_NAME}}" MATCHES "1|TRUE|YES|Y")
        set(HAVE_${_NAME} ON)
    endif()
    message(STATUS "  ${_NAME}${_PAD}(Wanted: ${_REQVALUE}): ${HAVE_${_NAME}}")
endmacro()

# listtostr(<_list> <_output>):
# Converts a given <_list> to a string in <_output>.
macro(LISTTOSTR _LIST _OUTPUT)
    if(${ARGC} EQUAL 3)
        # prefix for each element
        set(_LPREFIX ${ARGV2})
    else()
        set(_LPREFIX "")
    endif()
    # Do not use string(REPLACE ";" " ") here to avoid messing up list
    # entries
    foreach(_ITEM ${${_LIST}})
        set(${_OUTPUT} "${_LPREFIX}${_ITEM} ${${_OUTPUT}}")
    endforeach()
endmacro()

# set_option(<_name> <_desc> <_default>):
# Set a given option <_name> with <_description> and an optional default value
# of <_default>.
macro(SET_OPTION _NAME _DESC)
    list(APPEND ALLOPTIONS ${_NAME})
    if(${ARGC} EQUAL 3)
        set(_DEFLT ${ARGV2})
    else()
        set(_DEFLT OFF)
    endif()
    option(${_NAME} ${_DESC} ${_DEFLT})
endmacro()

# dep_option(<_name> <_description> <_default> <_dependent_option> <_fail_default>):
# Set a given option <_name> with <_description> to a value of <_default>.
# If <_dependent_option> is OFF, the options value will be set to <_fail_default>.
macro(DEP_OPTION _NAME _DESC _DEFLT _DEPTEST _FAILDFLT)
  list(APPEND ALLOPTIONS ${_NAME})
  cmake_dependent_option(${_NAME} ${_DESC} ${_DEFLT} ${_DEPTEST} ${_FAILDFLT})
endmacro()

# option_string(<_name> <_description> <_value>):
# Set an option list <_name> with a given <_description> to <_value>.
macro(OPTION_STRING _NAME _DESC _VALUE)
    list(APPEND ALLOPTIONS ${_NAME})
    set(${_NAME} ${_VALUE} CACHE STRING "${_DESC}")
    set(HAVE_${_NAME} ${_VALUE})
endmacro()
