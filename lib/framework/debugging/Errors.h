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

#ifndef MANGOSSERVER_ERRORS_H
#define MANGOSSERVER_ERRORS_H

#include "Common.h"

// Normal assert.
#define WPError(CONDITION)                                                                                          \
    if (!(CONDITION))                                                                                               \
    {                                                                                                               \
        printf("%s:%i: Error: Assertion in %s failed: %s", __FILE__, __LINE__, __FUNCTION__, STRINGIZE(CONDITION)); \
        assert(STRINGIZE(CONDITION) && 0);                                                                          \
    }

// Just warn.
#define WPWarning(CONDITION)                                                                                          \
    if (!(CONDITION))                                                                                                 \
    {                                                                                                                 \
        printf("%s:%i: Warning: Assertion in %s failed: %s", __FILE__, __LINE__, __FUNCTION__, STRINGIZE(CONDITION)); \
    }

#ifdef MANGOS_DEBUG
#    define MANGOS_ASSERT WPError
#else
#    define MANGOS_ASSERT WPError // Error even if in release mode.
#endif

#endif
