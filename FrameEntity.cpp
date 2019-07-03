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

#include "FrameEntity.hpp"

template <>
bool FrameEntity::operator== <const FrameEntity &>(const FrameEntity &other) const
{
    return this->storage == other.storage;
}

template <>
bool FrameEntity::operator==<byte_exposed_t>(byte_exposed_t other) const
{
    return this->storage == other;
}

template <>
bool FrameEntity::operator!=<const FrameEntity &>(const FrameEntity &other) const
{
    return this->storage != other.storage;
}

template <>
bool FrameEntity::operator!= <byte_exposed_t>(byte_exposed_t other) const
{
    return this->storage != other;
}

FrameEntity::Iterator::Iterator(FrameEntity *parentFrame, size_t bitNumber)
        : parent{parentFrame},
          bitIndex{bitNumber}
{
}

bool FrameEntity::Iterator::operator==(const FrameEntity::Iterator &other)
{
    return !(this->parent != other.parent || this->bitIndex != other.bitIndex);
}

bool FrameEntity::Iterator::operator!=(const FrameEntity::Iterator &other)
{
    return !(*this == other);
}

FrameEntity::Iterator &FrameEntity::Iterator::operator=(const FrameEntity::Iterator &other)
{
    this->bitIndex = other.bitIndex;
    this->parent = other.parent;
    return *this;
}

FrameEntity::Iterator &FrameEntity::Iterator::operator++() //prefix increment
{
    ++this->bitIndex;
    return *this;
}

byte_exposed_t::reference FrameEntity::Iterator::operator*() const
{
    return (*this->parent)[bitIndex];
}

FrameEntity::FrameEntity(bool defaultSet)
        : storage{defaultSet ? std::numeric_limits<byte_t>::max() : std::numeric_limits<byte_t>::min()}
{
}

FrameEntity::FrameEntity(byte_t value)
        : storage{value}
{

}

FrameEntity::FrameEntity(const byte_exposed_t &value)
        : storage{value}
{
}

FrameEntity::FrameEntity(byte_exposed_t &&value)
        : storage{value}
{
}

FrameEntity::operator byte_t() const
{
    return static_cast<byte_t>(this->storage.to_ulong());
}

FrameEntity::operator byte_exposed_t() const
{
    return this->storage;
}

bool FrameEntity::operator<(const FrameEntity &other)
{
    return this->storage.to_ulong() < other.storage.to_ulong();
}

bool FrameEntity::operator[](size_t bitNumber) const
{
    if (bitNumber >= this->storage.size())
    {
        throw std::out_of_range{"Cannot access " + std::to_string(bitNumber) + " bit of " + std::to_string(this->storage
                                                                                                               .size()) + "-bit value!"};
    }

    return this->storage[bitNumber];
}

byte_exposed_t::reference FrameEntity::operator[](size_t bitNumber)
{
    if (bitNumber >= this->storage.size())
    {
        throw std::out_of_range{"Cannot access " + std::to_string(bitNumber) + " bit of " + std::to_string(this->storage
                                                                                                               .size()) + "-bit value!"};
    }

    return this->storage[bitNumber];
}

FrameEntity::Iterator FrameEntity::begin()
{
    return Iterator{this, 0};
}

FrameEntity::Iterator FrameEntity::end()
{
    return Iterator{this, this->storage.size()};
}

FrameEntity FrameEntity::operator~() const
{
    return FrameEntity{~this->storage};
}

FrameEntity FrameEntity::operator&(const FrameEntity &other) const
{
    return FrameEntity{this->storage & other.storage};
}

FrameEntity FrameEntity::operator|(const FrameEntity &other) const
{
    return FrameEntity{static_cast<byte_t>(static_cast<byte_t>(this->storage.to_ulong()) | static_cast<byte_t>(other
            .storage.to_ulong()))};
}

FrameEntity FrameEntity::operator^(const FrameEntity &other) const
{
    return FrameEntity{this->storage ^ other.storage};
}

FrameEntity FrameEntity::operator>>(byte_t i) const
{
    return FrameEntity{static_cast<byte_t>(static_cast<byte_t>(this->storage.to_ulong()) >> i)};
}

FrameEntity FrameEntity::operator<<(byte_t i) const
{
    return FrameEntity{static_cast<byte_t>(static_cast<byte_t>(this->storage.to_ulong()) << i)};
}

FrameEntity &FrameEntity::operator&=(const FrameEntity &other)
{
    this->storage = this->storage & other.storage;
    return *this;
}

FrameEntity &FrameEntity::operator|=(const FrameEntity &other)
{
    this->storage = this->storage | other.storage;
    return *this;
}

FrameEntity &FrameEntity::operator^=(const FrameEntity &other)
{
    this->storage = this->storage ^ other.storage;
    return *this;
}

FrameEntity &FrameEntity::operator>>=(byte_t i)
{
    this->storage = this->storage >> i;
    return *this;
}

FrameEntity &FrameEntity::operator<<=(byte_t i)
{
    this->storage = this->storage << i;
    return *this;
}
