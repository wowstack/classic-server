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

#include "network/PacketBuffer.hpp"
#include "platform/Define.h"
#include <cassert>
#include <cstring>
#include <vector>

using namespace MaNGOS;

PacketBuffer::PacketBuffer(int initialSize) : m_writePosition(0), m_readPosition(0), m_buffer(initialSize, 0) {}

void PacketBuffer::Read(char *buffer, int length)
{
    assert(ReadLengthRemaining() >= length);

    if (buffer)
        memcpy(buffer, &m_buffer[m_readPosition], length);

    m_readPosition += length;
}

void PacketBuffer::Write(const char *buffer, int length)
{
    assert(buffer != nullptr && length != 0);

    const size_t newLength = m_writePosition + length;

    if (m_buffer.size() < newLength)
        m_buffer.resize(newLength);

    memcpy(&m_buffer[m_writePosition], buffer, length);

    m_writePosition += length;
}
