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

class FrameEntity
{
public:

    constexpr static size_t bits = std::numeric_limits<byte_t>::digits;

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
    explicit FrameEntity(bool defaultSet = false);

    FrameEntity(const FrameEntity &f) = default;

    FrameEntity(FrameEntity &&f) noexcept = default;

    ~FrameEntity() = default;

    FrameEntity &operator=(const FrameEntity &f) = default;

    // custom c-tors:
    FrameEntity(byte_t value);

    FrameEntity(const byte_exposed_t &value);

    FrameEntity(byte_exposed_t &&value);

    // conversions to:
    operator byte_t() const;

    operator byte_exposed_t() const;

    // comparisons:
    bool operator<(const FrameEntity &other);

    template <typename T>
    bool operator==(T other) const
    {
        return this->storage.to_ulong() == static_cast<byte_t>(other);
    }

    template <typename T>
    bool operator!=(T other) const
    {
        return this->storage.to_ulong() != other;
    }

    // selections:
    bool operator[](size_t bitNumber) const;

    byte_exposed_t::reference operator[](size_t bitNumber);

    Iterator begin();

    Iterator end();

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

