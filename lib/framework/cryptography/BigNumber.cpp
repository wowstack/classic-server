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

#include "cryptography/BigNumber.h"
#include <openssl/bn.h>
#include <algorithm>

BigNumber::BigNumber()
{
    _bn = BN_new();
    _array = nullptr;
}

BigNumber::BigNumber(const BigNumber &bn)
{
    _bn = BN_dup(bn._bn);
    _array = nullptr;
}

BigNumber::BigNumber(uint32_t val)
{
    _bn = BN_new();
    BN_set_word(_bn, val);
    _array = nullptr;
}

BigNumber::~BigNumber()
{
    BN_free(_bn);
    if (_array)
        delete[] _array;
}

void BigNumber::SetDword(uint32_t val)
{
    BN_set_word(_bn, val);
}

void BigNumber::SetQword(uint64_t val)
{
    BN_add_word(_bn, (uint32_t)(val >> 32));
    BN_lshift(_bn, _bn, 32);
    BN_add_word(_bn, (uint32_t)(val & 0xFFFFFFFF));
}

void BigNumber::SetBinary(const uint8_t *bytes, int len)
{
    uint8_t t[1000];
    for (int i = 0; i < len; ++i)
        t[i] = bytes[len - 1 - i];
    BN_bin2bn(t, len, _bn);
}

void BigNumber::SetHexStr(const char *str)
{
    BN_hex2bn(&_bn, str);
}

void BigNumber::SetRand(int numbits)
{
    BN_rand(_bn, numbits, 0, 1);
}

BigNumber BigNumber::operator=(const BigNumber &bn)
{
    BN_copy(_bn, bn._bn);
    return *this;
}

BigNumber BigNumber::operator+=(const BigNumber &bn)
{
    BN_add(_bn, _bn, bn._bn);
    return *this;
}

BigNumber BigNumber::operator-=(const BigNumber &bn)
{
    BN_sub(_bn, _bn, bn._bn);
    return *this;
}

BigNumber BigNumber::operator*=(const BigNumber &bn)
{
    BN_CTX *bnctx = BN_CTX_new();
    BN_mul(_bn, _bn, bn._bn, bnctx);
    BN_CTX_free(bnctx);

    return *this;
}

BigNumber BigNumber::operator/=(const BigNumber &bn)
{
    BN_CTX *bnctx = BN_CTX_new();
    BN_div(_bn, nullptr, _bn, bn._bn, bnctx);
    BN_CTX_free(bnctx);

    return *this;
}

BigNumber BigNumber::operator%=(const BigNumber &bn)
{
    BN_CTX *bnctx = BN_CTX_new();
    BN_mod(_bn, _bn, bn._bn, bnctx);
    BN_CTX_free(bnctx);

    return *this;
}

BigNumber BigNumber::Exp(const BigNumber &bn)
{
    BigNumber ret;

    BN_CTX *bnctx = BN_CTX_new();
    BN_exp(ret._bn, _bn, bn._bn, bnctx);
    BN_CTX_free(bnctx);

    return ret;
}

BigNumber BigNumber::ModExp(const BigNumber &bn1, const BigNumber &bn2)
{
    BigNumber ret;

    BN_CTX *bnctx = BN_CTX_new();
    BN_mod_exp(ret._bn, _bn, bn1._bn, bn2._bn, bnctx);
    BN_CTX_free(bnctx);

    return ret;
}

int BigNumber::GetNumBytes(void) const
{
    return BN_num_bytes(_bn);
}

uint32_t BigNumber::AsDword() const
{
    return (uint32_t)BN_get_word(_bn);
}

bool BigNumber::isZero() const
{
    return BN_is_zero(_bn) != 0;
}

uint8_t *BigNumber::AsByteArray(int minSize, bool reverse)
{
    int length = (minSize >= GetNumBytes()) ? minSize : GetNumBytes();

    delete[] _array;
    _array = new uint8_t[length];

    // If we need more bytes than length of BigNumber set the rest to 0
    if (length > GetNumBytes())
        memset((void *)_array, 0, length);

    BN_bn2bin(_bn, (unsigned char *)_array);

    if (reverse)
        std::reverse(_array, _array + length);

    return _array;
}

const char *BigNumber::AsHexStr() const
{
    return BN_bn2hex(_bn);
}

const char *BigNumber::AsDecStr() const
{
    return BN_bn2dec(_bn);
}