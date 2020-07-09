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

#ifndef WOWSTACK_H_CONFIG
#define WOWSTACK_H_CONFIG

#include "Common.h"
#include "platform/Define.h"
#include "policies/Singleton.h"
#include <mutex>
#include <string>
#include <unordered_map>

class Config
{
  private:
    std::string m_filename;
    std::unordered_map<std::string, std::string> m_entries; // keys are converted to lower case.  values cannot be.

  public:
    bool SetSource(const std::string &file);
    bool Reload();

    bool IsSet(const std::string &name) const;

    const std::string GetStringDefault(const std::string &name, const std::string &def = "") const;
    bool GetBoolDefault(const std::string &name, bool def) const;
    int32_t GetIntDefault(const std::string &name, int32_t def) const;
    float GetFloatDefault(const std::string &name, float def) const;

    const std::string &GetFilename() const
    {
        return m_filename;
    }
    std::mutex m_configLock;
};

#define sConfig MaNGOS::Singleton<Config>::Instance()

#endif // WOWSTACK_H_CONFIG
