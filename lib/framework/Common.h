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

#ifndef WOWSTACK_H_COMMON
#define WOWSTACK_H_COMMON

#include "debugging/Errors.h"
#include "platform/Define.h"
#include "threading/Threading.h"
#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>

typedef std::chrono::system_clock Clock;
typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> TimePoint;

#if COMPILER == COMPILER_MICROSOFT

#    include <cfloat>

#    define I32FMT "%08I32X"
#    define I64FMT "%016I64X"

#    pragma warning(disable : 4251)
#else

#    define stricmp strcasecmp
#    define strnicmp strncasecmp

#    define I32FMT "%08X"
#    define I64FMT "%016llX"

#endif

#define __STDC_FORMAT_MACROS
#include <cinttypes>

#define UI64FMTD "%" PRIu64
#define SI64FMTD "%" PRId64

#if COMPILER == COMPILER_MICROSOFT
#    define SIZEFMTD "%Iu"
#else
#    define SIZEFMTD "%zu"
#endif

inline float finiteAlways(float f)
{
    return std::isfinite(f) ? f : 0.0f;
}

// used for creating values e.g. for respawn
#define MAKE_PAIR64(l, h) uint64_t(uint32_t(l) | (uint64_t(h) << 32))
#define PAIR64_HIPART(x) (uint32_t)((uint64_t(x) >> 32) & uint64_t(0x00000000FFFFFFFF))
#define PAIR64_LOPART(x) (uint32_t)(uint64_t(x) & uint64_t(0x00000000FFFFFFFF))

#define MAKE_PAIR32(l, h) uint32_t(uint16_t(l) | (uint32_t(h) << 16))
#define PAIR32_HIPART(x) (uint16_t)((uint32_t(x) >> 16) & 0x0000FFFF)
#define PAIR32_LOPART(x) (uint16_t)(uint32_t(x) & 0x0000FFFF)

enum TimeConstants
{
    MINUTE = 60,
    HOUR = MINUTE * 60,
    DAY = HOUR * 24,
    WEEK = DAY * 7,
    MONTH = DAY * 30,
    YEAR = MONTH * 12,
    IN_MILLISECONDS = 1000,
};

enum AccountTypes : uint8_t
{
    SEC_PLAYER = 0,
    SEC_MODERATOR = 1,
    SEC_GAMEMASTER = 2,
    SEC_ADMINISTRATOR = 3,
    // must be always last in list, accounts must have less security level always also
    SEC_CONSOLE = 4,
};

// Used in servers
enum RealmFlags : uint8_t
{
    REALM_FLAG_NONE = 0x00,
    REALM_FLAG_INVALID = 0x01,
    // realm displayed as offline
    REALM_FLAG_OFFLINE = 0x02,
    // realm displayed in form "RealmName (major.minor.revision.build)"
    REALM_FLAG_SPECIFYBUILD = 0x04,
    REALM_FLAG_UNK1 = 0x08,
    REALM_FLAG_UNK2 = 0x10,
    REALM_FLAG_NEW_PLAYERS = 0x20,
    REALM_FLAG_RECOMMENDED = 0x40,
    REALM_FLAG_FULL = 0x80
};

enum LocaleConstant : uint8_t
{
    LOCALE_enUS = 0, // also enGB
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
    TOTAL_LOCALES
};

extern char const *localeNames[TOTAL_LOCALES];

LocaleConstant GetLocaleByName(std::string const &name);
#ifndef M_PI
#    define M_PI (3.14159265358979323846)
#endif

#ifndef M_PI_F
#    define M_PI_F float(M_PI)
#endif

#ifndef countof
#    define countof(array) (sizeof(array) / sizeof((array)[0]))
#endif

namespace MaNGOS
{
    using std::make_unique;
} // namespace MaNGOS

#endif // WOWSTACK_H_COMMON
