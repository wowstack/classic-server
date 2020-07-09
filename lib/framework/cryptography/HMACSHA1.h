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

#ifndef WOWSTACK_H_AUTH_HMACSHA1
#define WOWSTACK_H_AUTH_HMACSHA1

#include "Common.h"
#include <openssl/hmac.h>
#include <openssl/sha.h>

class BigNumber;

#define SEED_KEY_SIZE 16

class HMACSHA1
{
  public:
    HMACSHA1(uint32_t len, uint8_t *seed);
    HMACSHA1(uint32_t len, uint8_t *seed, bool);
    ~HMACSHA1();
    void UpdateBigNumber(BigNumber *bn);
    void UpdateData(const uint8_t *data, int length);
    void UpdateData(const std::string &str);
    void Initialize();
    void Finalize();
    uint8_t *GetDigest()
    {
        return m_digest;
    };
    static int GetLength()
    {
        return SHA_DIGEST_LENGTH;
    };

  private:
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
    HMAC_CTX *m_ctx;
#else
    HMAC_CTX m_ctx;
#endif
    uint8_t m_key[SEED_KEY_SIZE];
    uint8_t m_digest[SHA_DIGEST_LENGTH];
};

#endif // WOWSTACK_H_AUTH_HMACSHA1
