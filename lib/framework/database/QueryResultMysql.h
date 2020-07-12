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

#if !defined(QUERYRESULTMYSQL_H)
#    define QUERYRESULTMYSQL_H

#    include "Common.h"

#    ifdef _WIN32
#        include <winsock2.h>
#    endif
#    include <mysql/mysql.h>

class QueryResultMysql : public QueryResult
{
  public:
    QueryResultMysql(MYSQL_RES *result, MYSQL_FIELD *fields, uint64 rowCount, uint32 fieldCount);

    ~QueryResultMysql();

    bool NextRow() override;

  private:
    enum Field::DataTypes ConvertNativeType(enum_field_types mysqlType) const;
    void EndQuery();

    MYSQL_RES *mResult;
};
#endif
