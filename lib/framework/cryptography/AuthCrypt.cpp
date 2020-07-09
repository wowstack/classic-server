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

#include "cryptography/AuthCrypt.h"
#include "cryptography/BigNumber.h"
#include "cryptography/HMACSHA1.h"
#include "log/Log.h"

AuthCrypt::AuthCrypt() : _initialized(false) {}

void AuthCrypt::DecryptRecv(uint8_t *data, size_t len)
{
    if (!_initialized)
        return;
    if (len < CRYPTED_RECV_LEN)
        return;

    for (size_t t = 0; t < CRYPTED_RECV_LEN; t++)
    {
        _recv_i %= _key.size();
        uint8_t x = (data[t] - _recv_j) ^ _key[_recv_i];
        ++_recv_i;
        _recv_j = data[t];
        data[t] = x;
    }
}

void AuthCrypt::EncryptSend(uint8_t *data, size_t len)
{
    if (!_initialized)
        return;
    if (len < CRYPTED_SEND_LEN)
        return;

    for (size_t t = 0; t < CRYPTED_SEND_LEN; t++)
    {
        _send_i %= _key.size();
        uint8_t x = (data[t] ^ _key[_send_i]) + _send_j;
        ++_send_i;
        data[t] = _send_j = x;
    }
}

void AuthCrypt::Init(BigNumber *bn)
{
    _send_i = _send_j = _recv_i = _recv_j = 0;

    const size_t len = 40;

    _key.resize(len);
    auto const key = bn->AsByteArray();
    std::copy(key, key + len, _key.begin());

    _initialized = true;
}
