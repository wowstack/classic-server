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

#ifndef WOWSTACK_H_AUTHCRYPT
#define WOWSTACK_H_AUTHCRYPT

#include "Common.h"
#include <vector>

class BigNumber;

class AuthCrypt
{
  public:
    AuthCrypt();

    void Init(BigNumber *K);

    void DecryptRecv(uint8_t *, size_t);
    void EncryptSend(uint8_t *, size_t);

  private:
    const static size_t CRYPTED_SEND_LEN = 4;
    const static size_t CRYPTED_RECV_LEN = 6;

    std::vector<uint8_t> _key;
    uint8_t _send_i, _send_j, _recv_i, _recv_j;
    bool _initialized;
};

#endif // WOWSTACK_H_AUTHCRYPT
