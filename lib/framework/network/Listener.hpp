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

#ifndef __LISTENER_HPP_
#define __LISTENER_HPP_

#include "network/NetworkThread.hpp"
#include <boost/asio.hpp>
#include <memory>
#include <thread>
#include <vector>

namespace MaNGOS
{
    template <typename SocketType>
    class Listener
    {
      private:
        std::unique_ptr<boost::asio::io_service> m_service;
        std::unique_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;

        std::thread m_acceptorThread;
        std::vector<std::unique_ptr<NetworkThread<SocketType>>> m_workerThreads;

        // the time in milliseconds to sleep a worker thread at the end of each tick
        const int SleepInterval = 100;

        NetworkThread<SocketType> *SelectWorker() const
        {
            int minIndex = 0;
            size_t minSize = m_workerThreads[minIndex]->Size();

            for (size_t i = 1; i < m_workerThreads.size(); ++i)
            {
                const size_t size = m_workerThreads[i]->Size();

                if (size < minSize)
                {
                    minSize = size;
                    minIndex = i;
                }
            }

            return m_workerThreads[minIndex].get();
        }

        void BeginAccept();
        void OnAccept(NetworkThread<SocketType> *worker, std::shared_ptr<SocketType> const &socket,
                      const boost::system::error_code &ec);

      public:
        Listener(std::string const &address, int port, int workerThreads);
        ~Listener();
    };

    template <typename SocketType>
    Listener<SocketType>::Listener(std::string const &address, int port, int workerThreads)
    : m_service(new boost::asio::io_service()),
      m_acceptor(new boost::asio::ip::tcp::acceptor(
          *m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port)))
    {
        m_workerThreads.reserve(workerThreads);
        for (auto i = 0; i < workerThreads; ++i)
            m_workerThreads.push_back(std::unique_ptr<NetworkThread<SocketType>>(new NetworkThread<SocketType>));

        BeginAccept();

        m_acceptorThread = std::thread([this]() { this->m_service->run(); });
    }

    // FIXME - is this needed?
    template <typename SocketType>
    Listener<SocketType>::~Listener()
    {
        m_acceptor->close();
        m_service->stop();
        m_acceptorThread.join();
        m_acceptor.reset();
        m_service.reset();
    }

    template <typename SocketType>
    void Listener<SocketType>::BeginAccept()
    {
        auto worker = SelectWorker();
        auto socket = worker->CreateSocket();

        m_acceptor->async_accept(socket->GetAsioSocket(), [this, worker, socket](const boost::system::error_code &ec) {
            this->OnAccept(worker, socket, ec);
        });
    }

    template <typename SocketType>
    void Listener<SocketType>::OnAccept(NetworkThread<SocketType> *worker, std::shared_ptr<SocketType> const &socket,
                                        const boost::system::error_code &ec)
    {
        // an error has occurred
        if (ec)
            worker->RemoveSocket(socket.get());
        else
            socket->Open();

        BeginAccept();
    }
} // namespace MaNGOS

#endif /* !__LISTENER_HPP_ */
