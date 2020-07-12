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

#ifndef __NETWORK_THREAD_HPP_
#define __NETWORK_THREAD_HPP_

#include "network/Socket.hpp"
#include <boost/asio.hpp>
#include <mutex>
#include <thread>
#include <unordered_set>

namespace MaNGOS
{
    template <typename SocketType>
    class NetworkThread
    {
      private:
        boost::asio::io_service m_service;

        std::mutex m_socketLock;
        std::unordered_set<std::shared_ptr<SocketType>> m_sockets;

        // note that the work member *must* be declared after the service member for the work constructor to function
        // correctly
        std::unique_ptr<boost::asio::io_service::work> m_work;

        std::thread m_serviceThread;

      public:
        NetworkThread()
        : m_work(new boost::asio::io_service::work(m_service)), m_serviceThread([this] {
              boost::system::error_code ec;
              this->m_service.run(ec);
          })
        {
            m_serviceThread.detach();
        }

        ~NetworkThread()
        {
            // Allow io_service::run() to exit.
            m_work.reset();

            // attempt to gracefully close any open connections
            for (auto i = m_sockets.begin(); i != m_sockets.end();)
            {
                auto const current = i;
                ++i;

                if (!(*current)->IsClosed())
                    (*current)->Close();
            }
        }

        size_t Size() const
        {
            return m_sockets.size();
        }

        std::shared_ptr<SocketType> CreateSocket();

        void RemoveSocket(Socket *socket)
        {
            std::lock_guard<std::mutex> guard(m_socketLock);
            m_sockets.erase(socket->shared<SocketType>());
        }
    };

    template <typename SocketType>
    std::shared_ptr<SocketType> NetworkThread<SocketType>::CreateSocket()
    {
        std::lock_guard<std::mutex> guard(m_socketLock);

        auto const i = m_sockets.emplace(
            std::make_shared<SocketType>(m_service, [this](Socket *socket) { this->RemoveSocket(socket); }));

        MANGOS_ASSERT(i.second);

        return *i.first;
    }
} // namespace MaNGOS

#endif /* !__NETWORK_THREAD_HPP_ */
