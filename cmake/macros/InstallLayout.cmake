# The purpose of this file is to set the default installation layout.
#
# The current choices of installation layout are:
#
#  STANDALONE
#    Build with prefix=/usr/local/wowstack, create tarball with install prefix="."
#    and relative links.  Windows zip uses the same tarball layout but without
#    the build prefix.
#
#  RPM, SLES
#    Build as per default RPM layout, with prefix=/usr
#    Note: The layout for ULN RPMs differs, see the "RPM" section.
#
#  DEB
#    Build as per STANDALONE, prefix=/opt/wowstack/server-$major.$minor
#
#  FREEBSD, GLIBC, OSX, TARGZ
#    Build with prefix=/usr/local/wowstack, create tarball with install prefix="."
#    and relative links.
#
#  WIN
#     Windows zip : same as tarball layout but without the build prefix
#
# To force a directory layout, use -DINSTALL_LAYOUT=<layout>.
#
# The default is STANDALONE.
#
# Note : At present, RPM and SLES layouts are similar. This is also true
#        for layouts like FREEBSD, GLIBC, OSX, TARGZ. However, they provide
#        opportunity to fine-tune deployment for each platform without
#        affecting all other types of deployment.
#
# There is the possibility to further fine-tune installation directories.
# Several variables can be overwritten:
#
# - INSTALL_BINDIR          (directory with client executables and scripts)
# - INSTALL_SBINDIR         (directory with realmd,worldd,etc)
#
# - INSTALL_LIBDIR          (directory with client)
#
# - INSTALL_INCLUDEDIR      (directory for WowStack headers)
#
# - INSTALL_DOCDIR          (documentation)
# - INSTALL_DOCREADMEDIR    (readme and similar)
# - INSTALL_MANDIR          (man pages)
# - INSTALL_INFODIR         (info pages)
#
# - INSTALL_SHAREDIR        (Build helpers, etc)
# - INSTALL_DATADIR         (Game client directory)
# - INSTALL_SUPPORTFILESDIR (various extra server support files)
# - INSTALL_LOGDIR          (directory holding log files)
#

IF (NOT INSTALL_LAYOUT)
    SET(DEFAULT_INSTALL_LAYOUT "STANDALONE")
ENDIF ()

SET(INSTALL_LAYOUT "${DEFAULT_INSTALL_LAYOUT}"
        CACHE STRING "Installation directory layout. Options are: TARGZ (as in tar.gz installer), WIN (as in zip installer), STANDALONE, RPM, DEB, FREEBSD, GLIBC, OSX, SLES")

IF (UNIX)
    IF (INSTALL_LAYOUT MATCHES "RPM" OR
            INSTALL_LAYOUT MATCHES "SLES")
        SET(default_prefix "/usr")
    ELSEIF (INSTALL_LAYOUT MATCHES "DEB")
        SET(default_prefix "/opt/wowstack/server-${WOWSTACK_VERSION}")
        # This is required to avoid "cpack -GDEB" default of prefix=/usr
        SET(CPACK_SET_DESTDIR ON)
    ELSE ()
        SET(default_prefix "/usr/local/wowstack")
    ENDIF ()
    IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        SET(CMAKE_INSTALL_PREFIX ${default_prefix}
                CACHE PATH "install prefix" FORCE)
    ENDIF ()
    SET(VALID_INSTALL_LAYOUTS "RPM" "DEB" "FREEBSD" "GLIBC" "OSX" "TARGZ" "SLES" "STANDALONE")
    LIST(FIND VALID_INSTALL_LAYOUTS "${INSTALL_LAYOUT}" ind)
    IF (ind EQUAL -1)
        MESSAGE(FATAL_ERROR "Invalid INSTALL_LAYOUT parameter:${INSTALL_LAYOUT}."
                " Choose between ${VALID_INSTALL_LAYOUTS}")
    ENDIF ()

    SET(SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc"
            CACHE PATH "config directory (for my.cnf)")
    MARK_AS_ADVANCED(SYSCONFDIR)
ENDIF ()

IF (WIN32)
    SET(VALID_INSTALL_LAYOUTS "TARGZ" "STANDALONE" "WIN")
    LIST(FIND VALID_INSTALL_LAYOUTS "${INSTALL_LAYOUT}" ind)
    IF (ind EQUAL -1)
        MESSAGE(FATAL_ERROR "Invalid INSTALL_LAYOUT parameter:${INSTALL_LAYOUT}."
                " Choose between ${VALID_INSTALL_LAYOUTS}")
    ENDIF ()
ENDIF ()

#
# STANDALONE layout
#
SET(INSTALL_BINDIR_STANDALONE "bin")
SET(INSTALL_SBINDIR_STANDALONE "bin")
#
SET(INSTALL_LIBDIR_STANDALONE "lib")
#
SET(INSTALL_INCLUDEDIR_STANDALONE "include")
#
SET(INSTALL_DOCDIR_STANDALONE "docs")
SET(INSTALL_DOCREADMEDIR_STANDALONE ".")
SET(INSTALL_MANDIR_STANDALONE "man")
SET(INSTALL_INFODIR_STANDALONE "docs")
#
SET(INSTALL_SHAREDIR_STANDALONE "share")
SET(INSTALL_DATADIR_STANDALONE "data")
SET(INSTALL_SUPPORTFILESDIR_STANDALONE "support-files")
SET(INSTALL_LOGDIR_STANDALONE "logs")
#

#
# WIN layout
#
SET(INSTALL_BINDIR_WIN "bin")
SET(INSTALL_SBINDIR_WIN "bin")
#
SET(INSTALL_LIBDIR_WIN "lib")
#
SET(INSTALL_INCLUDEDIR_WIN "include")
#
SET(INSTALL_DOCDIR_WIN "docs")
SET(INSTALL_DOCREADMEDIR_WIN ".")
SET(INSTALL_MANDIR_WIN "man")
SET(INSTALL_INFODIR_WIN "docs")
#
SET(INSTALL_SHAREDIR_WIN "share")
SET(INSTALL_DATADIR_WIN "data")
SET(INSTALL_SUPPORTFILESDIR_WIN "support-files")
SET(INSTALL_LOGDIR_WIN "logs")
#

#
# FREEBSD layout
#
SET(INSTALL_BINDIR_FREEBSD "bin")
SET(INSTALL_SBINDIR_FREEBSD "bin")
#
SET(INSTALL_LIBDIR_FREEBSD "lib")
#
SET(INSTALL_INCLUDEDIR_FREEBSD "include")
#
SET(INSTALL_DOCDIR_FREEBSD "docs")
SET(INSTALL_DOCREADMEDIR_FREEBSD ".")
SET(INSTALL_MANDIR_FREEBSD "man")
SET(INSTALL_INFODIR_FREEBSD "docs")
#
SET(INSTALL_SHAREDIR_FREEBSD "share")
SET(INSTALL_DATADIR_FREEBSD "data")
SET(INSTALL_SUPPORTFILESDIR_FREEBSD "support-files")
SET(INSTALL_LOGDIR_FREEBSD "logs")
#

#
# GLIBC layout
#
SET(INSTALL_BINDIR_GLIBC "bin")
SET(INSTALL_SBINDIR_GLIBC "bin")
#
SET(INSTALL_LIBDIR_GLIBC "lib")
#
SET(INSTALL_INCLUDEDIR_GLIBC "include")
#
SET(INSTALL_DOCDIR_GLIBC "docs")
SET(INSTALL_DOCREADMEDIR_GLIBC ".")
SET(INSTALL_MANDIR_GLIBC "man")
SET(INSTALL_INFODIR_GLIBC "docs")
#
SET(INSTALL_SHAREDIR_GLIBC "share")
SET(INSTALL_DATADIR_GLIBC "data")
SET(INSTALL_SUPPORTFILESDIR_GLIBC "support-files")
SET(INSTALL_LOGDIR_GLIBC "logs")
#

#
# OSX layout
#
SET(INSTALL_BINDIR_OSX "bin")
SET(INSTALL_SBINDIR_OSX "bin")
#
SET(INSTALL_LIBDIR_OSX "lib")
#
SET(INSTALL_INCLUDEDIR_OSX "include")
#
SET(INSTALL_DOCDIR_OSX "docs")
SET(INSTALL_DOCREADMEDIR_OSX ".")
SET(INSTALL_MANDIR_OSX "man")
SET(INSTALL_INFODIR_OSX "docs")
#
SET(INSTALL_SHAREDIR_OSX "share")
SET(INSTALL_DATADIR_OSX "data")
SET(INSTALL_SUPPORTFILESDIR_OSX "support-files")
SET(INSTALL_LOGDIR_OSX "logs")
#

#
# TARGZ layout
#
SET(INSTALL_BINDIR_TARGZ "bin")
SET(INSTALL_SBINDIR_TARGZ "bin")
#
SET(INSTALL_LIBDIR_TARGZ "lib")
#
SET(INSTALL_INCLUDEDIR_TARGZ "include")
#
SET(INSTALL_DOCDIR_TARGZ "docs")
SET(INSTALL_DOCREADMEDIR_TARGZ ".")
SET(INSTALL_MANDIR_TARGZ "man")
SET(INSTALL_INFODIR_TARGZ "docs")
#
SET(INSTALL_SHAREDIR_TARGZ "share")
SET(INSTALL_DATADIR_TARGZ "data")
SET(INSTALL_SUPPORTFILESDIR_TARGZ "support-files")
SET(INSTALL_LOGDIR_TARGZ "logs")
#

#
# RPM layout
#
SET(INSTALL_BINDIR_RPM "bin")
SET(INSTALL_SBINDIR_RPM "sbin")
#
IF (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    SET(INSTALL_LIBDIR_RPM "lib64")
ELSE ()
    SET(INSTALL_LIBDIR_RPM "lib")
ENDIF ()
#
SET(INSTALL_INCLUDEDIR_RPM "include/wowstack")
#
#SET(INSTALL_DOCDIR_RPM                 unset - installed directly by RPM)
#SET(INSTALL_DOCREADMEDIR_RPM           unset - installed directly by RPM)
SET(INSTALL_INFODIR_RPM "share/info")
SET(INSTALL_MANDIR_RPM "share/man")
#
SET(INSTALL_SHAREDIR_RPM "share")
SET(INSTALL_DATADIR_RPM "data")
SET(INSTALL_SUPPORTFILESDIR_RPM "share/wowstack")
SET(INSTALL_LOGDIR_RPM "logs/wowstack")
#

#
# SLES layout
#
SET(INSTALL_BINDIR_SLES "bin")
SET(INSTALL_SBINDIR_SLES "sbin")
#
IF (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    SET(INSTALL_LIBDIR_SLES "lib64")
ELSE ()
    SET(INSTALL_LIBDIR_SLES "lib")
ENDIF ()
#
SET(INSTALL_INCLUDEDIR_SLES "include/wowstack")
#
#SET(INSTALL_DOCDIR_SLES                 unset - installed directly by SLES)
#SET(INSTALL_DOCREADMEDIR_SLES           unset - installed directly by SLES)
SET(INSTALL_INFODIR_SLES "share/info")
SET(INSTALL_MANDIR_SLES "share/man")
#
SET(INSTALL_SHAREDIR_SLES "share")
SET(INSTALL_DATADIR_SLES "data")
SET(INSTALL_SUPPORTFILESDIR_SLES "share/wowstack")
SET(INSTALL_LOGDIR_SLES "logs/wowstack")
#

#
# DEB layout
#
SET(INSTALL_BINDIR_DEB "bin")
SET(INSTALL_SBINDIR_DEB "bin")
#
SET(INSTALL_LIBDIR_DEB "lib")
#
SET(INSTALL_INCLUDEDIR_DEB "include")
#
SET(INSTALL_DOCDIR_DEB "docs")
SET(INSTALL_DOCREADMEDIR_DEB ".")
SET(INSTALL_MANDIR_DEB "man")
SET(INSTALL_INFODIR_DEB "docs")
#
SET(INSTALL_SHAREDIR_DEB "share")
SET(INSTALL_DATADIR_DEB "data")
SET(INSTALL_SUPPORTFILESDIR_DEB "support-files")
SET(INSTALL_LOGDIR_DEB "logs/wowstack")
#

# Clear cached variables if install layout was changed
IF (OLD_INSTALL_LAYOUT)
    IF (NOT OLD_INSTALL_LAYOUT STREQUAL INSTALL_LAYOUT)
        SET(FORCE FORCE)
    ENDIF ()
ENDIF ()
SET(OLD_INSTALL_LAYOUT ${INSTALL_LAYOUT} CACHE INTERNAL "")

# Set INSTALL_FOODIR variables for chosen layout (for example, INSTALL_BINDIR
# will be defined  as ${INSTALL_BINDIR_STANDALONE} by default if STANDALONE
# layout is chosen)
FOREACH (var BIN SBIN LIB SHARE DATA INCLUDE DOC MAN
        INFO DOCREADME SUPPORTFILES LOG)
    SET(INSTALL_${var}DIR ${INSTALL_${var}DIR_${INSTALL_LAYOUT}}
            CACHE STRING "${var} installation directory" ${FORCE})
    MARK_AS_ADVANCED(INSTALL_${var}DIR)
    # message(STATUS "INSTALL_${var}DIR: ${INSTALL_${var}DIR}")
    # message(STATUS "")
ENDFOREACH ()

#------------------------------------------------------------------------------
message(STATUS "Installation: layout configuration finished.")
