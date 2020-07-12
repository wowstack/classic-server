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

#ifndef MANGOS_OBJECTLIFETIME_H
#define MANGOS_OBJECTLIFETIME_H

#include "platform/Define.h"
#include <stdexcept>

typedef void (*Destroyer)(void);

namespace MaNGOS
{
    void at_exit(void (*func)());

    template <class T>
    class ObjectLifeTime
    {
      public:
        static void ScheduleCall(void (*destroyer)())
        {
            at_exit(destroyer);
        }

        DECLSPEC_NORETURN static void OnDeadReference() ATTR_NORETURN;
    };

    template <class T>
    void ObjectLifeTime<T>::OnDeadReference() // We don't handle Dead Reference for now
    {
        throw std::runtime_error("Dead Reference");
    }
} // namespace MaNGOS

#endif
