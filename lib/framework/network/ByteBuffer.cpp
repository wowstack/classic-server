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

#include "network/ByteBuffer.h"
#include "log/Log.h"

void ByteBufferException::PrintPosError() const
{
    sLog.outError("Attempted to %s in ByteBuffer (pos: " SIZEFMTD " size: " SIZEFMTD ") value with size: " SIZEFMTD,
                  (add ? "put" : "get"), pos, size, esize);
}

void ByteBuffer::print_storage() const
{
    if (!sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG)) // optimize disabled debug output
        return;

    std::ostringstream ss;
    ss << "STORAGE_SIZE: " << size() << "\n";

    if (sLog.IsIncludeTime())
        ss << "         ";

    for (size_t i = 0; i < size(); ++i)
        ss << uint32(read<uint8>(i)) << " - ";

    sLog.outDebug("%s", ss.str().c_str());
}

void ByteBuffer::textlike() const
{
    if (!sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG)) // optimize disabled debug output
        return;

    std::ostringstream ss;
    ss << "STORAGE_SIZE: " << size() << "\n";

    if (sLog.IsIncludeTime())
        ss << "         ";

    for (size_t i = 0; i < size(); ++i)
        ss << read<uint8>(i);

    sLog.outDebug("%s", ss.str().c_str());
}

void ByteBuffer::hexlike() const
{
    if (!sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG)) // optimize disabled debug output
        return;

    std::ostringstream ss;
    ss << "STORAGE_SIZE: " << size() << "\n";

    if (sLog.IsIncludeTime())
        ss << "         ";

    size_t j = 1, k = 1;

    for (size_t i = 0; i < size(); ++i)
    {
        if ((i == (j * 8)) && ((i != (k * 16))))
        {
            ss << "| ";
            ++j;
        }
        else if (i == (k * 16))
        {
            ss << "\n";

            if (sLog.IsIncludeTime())
                ss << "         ";

            ++k;
            ++j;
        }

        char buf[4];
        snprintf(buf, 4, "%02X", read<uint8>(i));
        ss << buf << " ";
    }

    sLog.outDebug("%s", ss.str().c_str());
}
