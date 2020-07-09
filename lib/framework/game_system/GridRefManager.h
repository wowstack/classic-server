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

#ifndef _GRIDREFMANAGER
#define _GRIDREFMANAGER

#include "utilities/LinkedReference/RefManager.h"

template <class OBJECT>
class GridReference;

template <class OBJECT>
class MANGOS_DLL_SPEC GridRefManager : public RefManager<GridRefManager<OBJECT>, OBJECT>
{
  public:
    typedef LinkedListHead::Iterator<GridReference<OBJECT>> iterator;

    GridReference<OBJECT> *getFirst()
    {
        return (GridReference<OBJECT> *)RefManager<GridRefManager<OBJECT>, OBJECT>::getFirst();
    }

    GridReference<OBJECT> *getLast()
    {
        return (GridReference<OBJECT> *)RefManager<GridRefManager<OBJECT>, OBJECT>::getLast();
    }

    iterator begin()
    {
        return iterator(getFirst());
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    iterator rbegin()
    {
        return iterator(getLast());
    }
    iterator rend()
    {
        return iterator(nullptr);
    }
};
#endif
