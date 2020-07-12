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

#ifndef __PACKET_BUFFER_HPP_
#define __PACKET_BUFFER_HPP_

#include "platform/Define.h"
#include <functional>
#include <vector>

#define DEFAULT_BUFFER_SIZE 6144

namespace MaNGOS
{
    class PacketBuffer
    {
        friend class Socket;

      private:
        size_t m_writePosition;
        size_t m_readPosition;

        std::vector<uint8> m_buffer;

      public:
        PacketBuffer(int initialSize = DEFAULT_BUFFER_SIZE);

        uint8 Peak() const
        {
            return m_buffer[m_readPosition];
        }

        void Read(char *buffer, int length);
        int ReadLengthRemaining() const
        {
            return m_writePosition - m_readPosition;
        }

        void Write(const char *buffer, int length);
    };
} // namespace MaNGOS

#endif /* !__PACKET_BUFFER_HPP_ */
