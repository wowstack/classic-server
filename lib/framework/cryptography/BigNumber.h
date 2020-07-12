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

#ifndef WOWSTACK_H_AUTH_BIGNUMBER
#define WOWSTACK_H_AUTH_BIGNUMBER

#include "Common.h"

struct bignum_st;

class BigNumber
{
  public:
    BigNumber();
    BigNumber(const BigNumber &bn);
    BigNumber(uint32_t);
    ~BigNumber();

    void SetDword(uint32_t);
    void SetQword(uint64_t);
    void SetBinary(const uint8_t *bytes, int len);
    void SetHexStr(const char *str);

    void SetRand(int numbits);

    BigNumber operator=(const BigNumber &bn);

    BigNumber operator+=(const BigNumber &bn);
    BigNumber operator+(const BigNumber &bn)
    {
        BigNumber t(*this);
        return t += bn;
    }
    BigNumber operator-=(const BigNumber &bn);
    BigNumber operator-(const BigNumber &bn)
    {
        BigNumber t(*this);
        return t -= bn;
    }
    BigNumber operator*=(const BigNumber &bn);
    BigNumber operator*(const BigNumber &bn)
    {
        BigNumber t(*this);
        return t *= bn;
    }
    BigNumber operator/=(const BigNumber &bn);
    BigNumber operator/(const BigNumber &bn)
    {
        BigNumber t(*this);
        return t /= bn;
    }
    BigNumber operator%=(const BigNumber &bn);
    BigNumber operator%(const BigNumber &bn)
    {
        BigNumber t(*this);
        return t %= bn;
    }

    bool isZero() const;

    BigNumber ModExp(const BigNumber &bn1, const BigNumber &bn2);
    BigNumber Exp(const BigNumber &);

    int GetNumBytes(void) const;

    struct bignum_st *BN()
    {
        return _bn;
    }

    uint32_t AsDword() const;
    uint8_t *AsByteArray(int minSize = 0, bool reverse = true);

    const char *AsHexStr() const;
    const char *AsDecStr() const;

  private:
    struct bignum_st *_bn;
    uint8_t *_array;
};

#endif // WOWSTACK_H_AUTH_BIGNUMBER
