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

#ifndef TSS_H
#define TSS_H

#include <boost/thread/tss.hpp>
#include <functional>

namespace MaNGOS
{
    template <typename T>
    class thread_local_ptr : public boost::thread_specific_ptr<T>
    {
      private:
        typedef std::function<T *()> Generate;
        typedef std::function<void(T *)> Cleanup;

        Generate m_generator;

      public:
        thread_local_ptr() : m_generator([]() { return new T; }) {}
        thread_local_ptr(Generate generator) : m_generator(generator) {}
        thread_local_ptr(Generate generator, Cleanup cleanup)
        : m_generator(generator), boost::thread_specific_ptr<T>(cleanup)
        {
        }

        // this get allows for a nullptr return value
        T *get_value()
        {
            return boost::thread_specific_ptr<T>::get();
        }

        T *get()
        {
            T *ret = get_value();
            if (!ret)
            {
                ret = m_generator();
                boost::thread_specific_ptr<T>::reset(ret);
            }
            return ret;
        }

        T *operator->()
        {
            return get();
        }

        typename boost::detail::sp_dereference<T>::type operator*() const
        {
            return *get();
        }
    };
} // namespace MaNGOS

#endif /*TSS_H*/
