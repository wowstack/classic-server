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

#ifndef MANGOS_OBJECTREGISTRY_H
#define MANGOS_OBJECTREGISTRY_H

#include "Common.h"
#include "policies/Singleton.h"
#include <map>
#include <string>
#include <vector>

/** ObjectRegistry holds all registry item of the same type
 */
template <class T, class Key = std::string>
class ObjectRegistry
{
  public:
    typedef std::map<Key, T *> RegistryMapType;

    /// Returns a registry item
    const T *GetRegistryItem(Key key) const
    {
        typename RegistryMapType::const_iterator iter = i_registeredObjects.find(key);
        return (iter == i_registeredObjects.end() ? nullptr : iter->second);
    }

    /// Inserts a registry item
    bool InsertItem(T *obj, Key key, bool replace = false)
    {
        typename RegistryMapType::iterator iter = i_registeredObjects.find(key);
        if (iter != i_registeredObjects.end())
        {
            if (!replace)
                return false;
            delete iter->second;
            i_registeredObjects.erase(iter);
        }

        i_registeredObjects[key] = obj;
        return true;
    }

    /// Removes a registry item
    void RemoveItem(Key key, bool delete_object = true)
    {
        typename RegistryMapType::iterator iter = i_registeredObjects.find(key);
        if (iter != i_registeredObjects.end())
        {
            if (delete_object)
                delete iter->second;
            i_registeredObjects.erase(iter);
        }
    }

    /// Returns true if registry contains an item
    bool HasItem(Key key) const
    {
        return (i_registeredObjects.find(key) != i_registeredObjects.end());
    }

    /// Inefficiently return a vector of registered items
    unsigned int GetRegisteredItems(std::vector<Key> &l) const
    {
        unsigned int sz = l.size();
        l.resize(sz + i_registeredObjects.size());
        for (typename RegistryMapType::const_iterator iter = i_registeredObjects.begin();
             iter != i_registeredObjects.end(); ++iter)
            l[sz++] = iter->first;
        return i_registeredObjects.size();
    }

    /// Return the map of registered items
    RegistryMapType const &GetRegisteredItems() const
    {
        return i_registeredObjects;
    }

  private:
    RegistryMapType i_registeredObjects;
    friend class MaNGOS::OperatorNew<ObjectRegistry<T, Key>>;

    // protected for friend use since it should be a singleton
    ObjectRegistry() {}
    ~ObjectRegistry()
    {
        for (typename RegistryMapType::iterator iter = i_registeredObjects.begin(); iter != i_registeredObjects.end();
             ++iter)
            delete iter->second;
        i_registeredObjects.clear();
    }
};
#endif
