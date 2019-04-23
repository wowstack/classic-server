/**
 * Copyright (C) 2005-2014  MaNGOS project  <http://getmangos.com>
 * Copyright (C) 2013-2019  CMaNGOS project <http://cmangos.net>
 * Copyright (C) 2014-2019  WowStack        <https://wowstack.io/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WOWSTACK_CONFIG_H
#define WOWSTACK_CONFIG_H

/**
 * Version information used in all components
 */
#cmakedefine WOWSTACK_VERSION "@WOWSTACK_VERSION@"

/**
 * Path configuration
 */
#cmakedefine DEFAULT_WOWSTACK_HOME "@DEFAULT_WOWSTACK_HOME@"
#cmakedefine SHAREDIR "@SHAREDIR@"
#cmakedefine DATADIR "@DATADIR@"
#cmakedefine DEFAULT_BASEDIR "@DEFAULT_BASEDIR@"
#cmakedefine DEFAULT_SYSCONFDIR "@DEFAULT_SYSCONFDIR@"
#cmakedefine INSTALL_BINDIR "@INSTALL_BINDIR@"
#cmakedefine INSTALL_SBINDIR "@INSTALL_SBINDIR@"
#cmakedefine INSTALL_LIBDIR "@INSTALL_LIBDIR@"
#cmakedefine INSTALL_INCLUDEDIR "@INSTALL_INCLUDEDIR@"
#cmakedefine INSTALL_DOCDIR "@INSTALL_DOCDIR@"
#cmakedefine INSTALL_DOCREADMEDIR "@INSTALL_DOCREADMEDIR@"
#cmakedefine INSTALL_MANDIR "@INSTALL_MANDIR@"
#cmakedefine INSTALL_INFODIR "@INSTALL_INFODIR@"
#cmakedefine INSTALL_SHAREDIR "@INSTALL_SHAREDIR@"
#cmakedefine INSTALL_DATADIR "@INSTALL_DATADIR@"
#cmakedefine INSTALL_SUPPORTFILESDIR "@INSTALL_SUPPORTFILESDIR@"
#cmakedefine INSTALL_LOGDIR "@INSTALL_LOGDIR@"

/**
 * used for Windows file resources
 */
#define VER_COMPANYNAME_STR "WowStack Community"
#define VER_LEGALCOPYRIGHT_STR "(c) 2014-2019 WowStack.io"
#define VER_FILEVERSION ${WOWSTACK_MAJOR_VERSION}, ${WOWSTACK_MINOR_VERSION}, ${WOWSTACK_MICRO_VERSION}
#define VER_FILEVERSION_STR "${WOWSTACK_VERSION}"
#define VER_PRODUCTVERSION VER_FILEVERSION
#define VER_PRODUCTVERSION_STR VER_FILEVERSION_STR

#endif /* WOWSTACK_CONFIG_H */
