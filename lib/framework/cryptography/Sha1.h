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

#ifndef WOWSTACK_H_AUTH_SHA1
#define WOWSTACK_H_AUTH_SHA1

#include "Common.h"
#include <openssl/crypto.h>
#include <openssl/sha.h>

class BigNumber;

class Sha1Hash
{
  public:
    Sha1Hash();
    ~Sha1Hash();

    void UpdateBigNumbers(BigNumber *bn0, ...);

    void UpdateData(const uint8_t *dta, int len);
    void UpdateData(const std::string &str);

    void Initialize();
    void Finalize();

    uint8_t *GetDigest(void)
    {
        return mDigest;
    };
    static int GetLength(void)
    {
        return SHA_DIGEST_LENGTH;
    };

  private:
    SHA_CTX mC;
    uint8_t mDigest[SHA_DIGEST_LENGTH];
};

#endif // WOWSTACK_H_AUTH_SHA1
