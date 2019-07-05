/*
    This file is distributed under MIT License.

    Copyright (c) 2019 draghan

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#pragma once

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <bitset>
#include <string>
#include <limits>
#include <cstdint>

using byte_t = uint8_t;
using byte_exposed_t = std::bitset<std::numeric_limits<byte_t>::digits>;

/// Class representing basically a byte of memory with handy interface for indexing bits,
/// slicing, conversions from and to different types.
class FrameEntity
{
public:

    /// Number of bits in the entity.
    constexpr static size_t bits = std::numeric_limits<byte_t>::digits;

    /// Iterator-like class for providing begin() and end() - you can foreach by bits
    class Iterator
    {
    public:
        explicit Iterator(FrameEntity *parentFrame = nullptr, size_t bitNumber = 0);

        bool operator==(const Iterator &other);

        bool operator!=(const Iterator &other);

        Iterator &operator=(const Iterator &other);

        Iterator &operator++();

        byte_exposed_t::reference operator*() const;

    private:
        FrameEntity *parent;
        size_t bitIndex;
    };

    // rule of five:

    /// Default constructor, initialize bits.
    /// \param defaultSet If set to \p true, every bit in a byte will be set to 1. If \p false - bits are set to 0. Default is \p false.
    explicit FrameEntity(bool defaultSet = false);

    /// Default copy constructor.
    /// \param other Object to copy data from.
    FrameEntity(const FrameEntity &other) = default;

    /// Default move constructor.
    /// \param other Object to move data from.
    FrameEntity(FrameEntity &&other) noexcept = default;

    /// Default destructor.
    ~FrameEntity() = default;

    /// Default assignment operator.
    /// \param other Object to copy data from.
    /// \return Reference to this.
    FrameEntity &operator=(const FrameEntity &other) = default;

    // custom c-tors:
    /// Construct \p FrameEntity (explicitly or implicitly) from \p byte_t.
    /// \param value Value to construct \p FrameEntity from.
    FrameEntity(byte_t value);

    /// Construct \p FrameEntity (explicitly or implicitly) from \p byte_exposed_t (std::bitset).
    /// \param value Value to construct \p FrameEntity from.
    FrameEntity(const byte_exposed_t &value);

    /// Construct \p FrameEntity (explicitly or implicitly) by moving data from \p std::bitset.
    /// \param value Value to construct \p FrameEntity from.
    FrameEntity(byte_exposed_t &&value);

    // conversions to:

    /// Conversion operator to \p byte_t.
    operator byte_t() const;

    /// Conversion operator to \p byte_exposed_t (\p std::bitset).
    operator byte_exposed_t() const;

    // comparisons:

    /// Check if numeric value of this \p FrameEntity is less than numeric value of the \p other.
    bool operator<(const FrameEntity &other);

    /// Universal comparison operator, check equality.
    template <typename T>
    bool operator==(T other) const
    {
        return this->storage.to_ulong() == static_cast<byte_t>(other);
    }

    /// Universal comparison operator, check inequality.
    template <typename T>
    bool operator!=(T other) const
    {
        return this->storage.to_ulong() != other;
    }

    // selections:
    /// Indexing operator. Selects specific bit from the representing byte. Read only version.
    bool operator[](size_t bitNumber) const;

    /// Indexing operator. Selects specific bit from the representing byte. Read-write version.
    byte_exposed_t::reference operator[](size_t bitNumber);

    /// Slice range of bits from current byte. Range indexes are inclusive.
    /// Place that range in the least significant part, fill most significant rest of the bits with default value.
    /// \example Range 2-4 will result in select 3 bits: 2, 3, 4 and place it like this: 2->0, 3->1, 4->2, rest of
    /// bits will be set to default (0) value.
    /// \example FrameEntity f{0b11100110}; f(2, 4) == 0b00000001
    /// \param beginIndex Starting bit index to cut, must be in the range of [0 - \p bits - 1].
    /// \param endIndex Ending bit index to cut, must be in the range of [0 - \p bits - 1] and be not less than \p beginIndex.
    /// \param defaultSet Default false. If true, set all of not cut bits to 1. If false, set all of not cut bits to 0.
    /// \return New \p FrameEntity instance.
    FrameEntity operator()(size_t beginIndex, size_t endIndex, bool defaultSet = false) const;

    /// Returns iterator to the first bit in the byte.
    Iterator begin();

    /// Returns iterator to the one element after last bit in the byte.
    Iterator end();

    /// Reverse bit order.
    FrameEntity &reverse();

    // bitwise operators:
    FrameEntity operator~() const;

    FrameEntity operator&(const FrameEntity &other) const;

    FrameEntity operator|(const FrameEntity &other) const;

    FrameEntity operator^(const FrameEntity &other) const;

    FrameEntity operator>>(byte_t i) const;

    FrameEntity operator<<(byte_t i) const;

    FrameEntity &operator&=(const FrameEntity &other);

    FrameEntity &operator|=(const FrameEntity &other);

    FrameEntity &operator^=(const FrameEntity &other);

    FrameEntity &operator>>=(byte_t i);

    FrameEntity &operator<<=(byte_t i);


private:
    bool spliceIsValid(size_t beginIndex, size_t endIndex) const;

    byte_exposed_t storage;
};

template <>
bool FrameEntity::operator==
<const FrameEntity &>(
const FrameEntity &other
) const;

template <>
bool FrameEntity::operator==
<byte_exposed_t>(byte_exposed_t
other) const;

template <>
bool FrameEntity::operator!=
<const FrameEntity &>(
const FrameEntity &other
) const;

template <>
bool FrameEntity::operator!=
<byte_exposed_t>(byte_exposed_t
other) const;

