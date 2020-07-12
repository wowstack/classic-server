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

#include "database/SqlDelayThread.h"
#include "database/DatabaseEnv.h"
#include "database/SqlOperations.h"

SqlDelayThread::SqlDelayThread(Database *db, SqlConnection *conn)
: m_dbEngine(db), m_dbConnection(conn), m_running(true)
{
}

SqlDelayThread::~SqlDelayThread()
{
    // process all requests which might have been queued while thread was stopping
    ProcessRequests();
}

void SqlDelayThread::run()
{
    mysql_thread_init();

    const uint32 loopSleepms = 10;

    const uint32 pingEveryLoop = m_dbEngine->GetPingIntervall() / loopSleepms;

    uint32 loopCounter = 0;
    while (m_running)
    {
        // if the running state gets turned off while sleeping
        // empty the queue before exiting
        MaNGOS::Thread::Sleep(loopSleepms);

        ProcessRequests();

        if ((loopCounter++) >= pingEveryLoop)
        {
            loopCounter = 0;
            m_dbEngine->Ping();
        }
    }

    mysql_thread_end();
}

void SqlDelayThread::Stop()
{
    m_running = false;
}

void SqlDelayThread::ProcessRequests()
{
    std::queue<std::unique_ptr<SqlOperation>> sqlQueue;

    // we need to move the contents of the queue to a local copy because executing these statements with the
    // lock in place can result in a deadlock with the world thread which calls Database::ProcessResultQueue()
    {
        std::lock_guard<std::mutex> guard(m_queueMutex);
        sqlQueue = std::move(m_sqlQueue);
    }

    while (!sqlQueue.empty())
    {
        auto const s = std::move(sqlQueue.front());
        sqlQueue.pop();
        s->Execute(m_dbConnection);
    }
}
