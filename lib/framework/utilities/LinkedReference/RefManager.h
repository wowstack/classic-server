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

#ifndef _REFMANAGER_H
#define _REFMANAGER_H

//=====================================================

#include "utilities/LinkedList.h"
#include "utilities/LinkedReference/Reference.h"

template <class TO, class FROM>
class MANGOS_DLL_SPEC RefManager : public LinkedListHead
{
  public:
    typedef LinkedListHead::Iterator<Reference<TO, FROM>> iterator;
    RefManager() {}
    virtual ~RefManager()
    {
        clearReferences();
    }

    Reference<TO, FROM> *getFirst()
    {
        return ((Reference<TO, FROM> *)LinkedListHead::getFirst());
    }
    Reference<TO, FROM> const *getFirst() const
    {
        return ((Reference<TO, FROM> const *)LinkedListHead::getFirst());
    }
    Reference<TO, FROM> *getLast()
    {
        return ((Reference<TO, FROM> *)LinkedListHead::getLast());
    }
    Reference<TO, FROM> const *getLast() const
    {
        return ((Reference<TO, FROM> const *)LinkedListHead::getLast());
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

    void clearReferences()
    {
        LinkedListElement *ref;
        while ((ref = getFirst()) != nullptr)
        {
            ((Reference<TO, FROM> *)ref)->invalidate();
            ref->delink(); // the delink might be already done by invalidate(), but doing it here again does not hurt
                           // and insures an empty list
        }
    }
};

//=====================================================

#endif
