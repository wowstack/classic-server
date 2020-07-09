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

#ifndef WOWSTACK_H_ARC4
#define WOWSTACK_H_ARC4

#include "Common.h"
#include <openssl/evp.h>

class ARC4
{
  public:
    ARC4(uint8_t len);
    ARC4(uint8_t *seed, uint8_t len);
    ~ARC4();
    void Init(uint8_t *seed);
    void UpdateData(int len, uint8_t *data);

  private:
    EVP_CIPHER_CTX m_ctx;
};

#endif // WOWSTACK_H_ARC4
