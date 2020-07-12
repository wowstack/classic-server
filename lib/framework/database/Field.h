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

#ifndef FIELD_H
#define FIELD_H

#include "Common.h"

class Field
{
  public:
    enum DataTypes
    {
        DB_TYPE_UNKNOWN = 0x00,
        DB_TYPE_STRING = 0x01,
        DB_TYPE_INTEGER = 0x02,
        DB_TYPE_FLOAT = 0x03,
        DB_TYPE_BOOL = 0x04
    };

    Field() : mValue(nullptr), mType(DB_TYPE_UNKNOWN) {}
    Field(const char *value, enum DataTypes type) : mValue(value), mType(type) {}

    ~Field() {}

    enum DataTypes GetType() const
    {
        return mType;
    }
    bool IsNULL() const
    {
        return mValue == nullptr;
    }

    const char *GetString() const
    {
        return mValue ? mValue : ""; // We need this null check as we do not always null check what we get back from the
                                     // database everywhere
    }
    std::string GetCppString() const
    {
        return mValue ? mValue : ""; // std::string s = 0 have undefine result in C++
    }
    float GetFloat() const
    {
        return mValue ? static_cast<float>(atof(mValue)) : 0.0f;
    }
    bool GetBool() const
    {
        return mValue ? atoi(mValue) > 0 : false;
    }
    int32 GetInt32() const
    {
        return mValue ? static_cast<int32>(atol(mValue)) : int32(0);
    }
    uint8 GetUInt8() const
    {
        return mValue ? static_cast<uint8>(atol(mValue)) : uint8(0);
    }
    uint16 GetUInt16() const
    {
        return mValue ? static_cast<uint16>(atol(mValue)) : uint16(0);
    }
    int16 GetInt16() const
    {
        return mValue ? static_cast<int16>(atol(mValue)) : int16(0);
    }
    uint32 GetUInt32() const
    {
        return mValue ? static_cast<uint32>(atoll(mValue)) : uint32(0);
    }
    uint64 GetUInt64() const
    {
        uint64 value = 0;
        if (!mValue || sscanf(mValue, UI64FMTD, &value) == -1)
            return 0;

        return value;
    }

    void SetType(enum DataTypes type)
    {
        mType = type;
    }
    // no need for memory allocations to store resultset field strings
    // all we need is to cache pointers returned by different DBMS APIs
    void SetValue(const char *value)
    {
        mValue = value;
    }

  private:
    Field(Field const &);
    Field &operator=(Field const &);

    const char *mValue;
    enum DataTypes mType;
};
#endif
