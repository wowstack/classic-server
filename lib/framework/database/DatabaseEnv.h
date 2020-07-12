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

#if !defined(DATABASEENV_H)
#    define DATABASEENV_H

#    include "Common.h"
#    include "database/Database.h"
#    include "database/DatabaseMysql.h"
#    include "database/Field.h"
#    include "database/QueryResult.h"
#    include "database/QueryResultMysql.h"
#    include "debugging/Errors.h"
#    include "log/Log.h"
typedef DatabaseMysql DatabaseType;
#    define _LIKE_ "LIKE"
#    define _TABLE_SIM_ '`'
#    define _CONCAT3_(A, B, C) "CONCAT( " A " , " B " , " C " )"
#    define _OFFSET_ "LIMIT %d,1"

extern DatabaseType WorldDatabase;
extern DatabaseType CharacterDatabase;
extern DatabaseType LoginDatabase;

#endif
