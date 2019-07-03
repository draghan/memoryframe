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

#include "Frame.hpp"


Frame::Frame()
        : storage{},
          byteStorage{},
          defaultFill{false}
{
}

Frame::Frame(const Frame &f)
        : storage{f.storage},
          byteStorage{},
          defaultFill{f.defaultFill}
{
}

Frame::Frame(Frame &&f)
        : storage{std::move(f.storage)},
          byteStorage{},
          defaultFill{f.defaultFill}
{
}

Frame &Frame::operator=(const Frame &f)
{
    this->storage = f.storage;
    return *this;
}

Frame::Frame(size_t frameLength, bool defaultSet)
        : storage(frameLength, FrameEntity{defaultSet}),
          byteStorage{},
          defaultFill{defaultSet}
{
}

Frame::Frame(std::initializer_list<FrameEntity> bytesCollection)
        : storage{bytesCollection},
          byteStorage{},
          defaultFill{false}
{
}

Frame::Frame(const byte_t *bytesArray, size_t arraySize)
        : Frame{}
{
    std::copy(bytesArray, bytesArray + arraySize, std::back_inserter(storage));
}

size_t Frame::size() const
{
    return this->storage.size();
}

bool Frame::operator==(const Frame &f) const
{
    return this->storage == f.storage;
}

bool Frame::operator!=(const Frame &f) const
{
    return this->storage != f.storage;
}

Frame &Frame::operator+=(const Frame &f)
{
    std::copy(f.storage.begin(), f.storage.end(), std::back_inserter(this->storage));
    return *this;
}

Frame &Frame::operator+=(const FrameEntity &f)
{
    this->storage.push_back(f);
    return *this;
}

Frame &Frame::operator+=(byte_t f)
{
    this->storage.push_back(f);
    return *this;
}

Frame Frame::operator+(const Frame &f) const
{
    std::vector<FrameEntity> temporaryStorage{this->storage};
    std::copy(f.storage.begin(), f.storage.end(), std::back_inserter(temporaryStorage));
    return Frame{temporaryStorage};
}

Frame Frame::operator+(const FrameEntity &f) const
{
    std::vector<FrameEntity> temporaryStorage{this->storage};
    temporaryStorage.push_back(f);
    return Frame{temporaryStorage};
}

Frame &Frame::placeAt(size_t where, const FrameEntity &byte)
{
    this->resizeToProvideElementAtIndex(where);

    this->storage[where] = byte;

    return *this;
}

Frame &Frame::placeAt(size_t where, byte_t byte)
{
    return this->placeAt(where, FrameEntity{byte});
}

Frame &Frame::placeAt(size_t where, const Frame &bytes)
{
    this->resizeToProvideElementAtIndex(where + bytes.size() - 1);

    std::copy(bytes.storage.begin(), bytes.storage.end(), this->storage.begin() + static_cast<decltype(this->storage
                                                                                                           .begin())::difference_type>(where));

    return *this;
}

Frame &Frame::placeAt(size_t where, const std::vector<uint8_t> &bytes)
{
    this->resizeToProvideElementAtIndex(where + bytes.size() - 1);

    std::copy(bytes.begin(), bytes.end(), this->storage.begin() + static_cast<decltype(this->storage
                                                                                           .begin())::difference_type>(where));

    return *this;
}

Frame &Frame::placeAt(size_t where, const std::vector<FrameEntity> &bytes)
{
    this->resizeToProvideElementAtIndex(where + bytes.size() - 1);

    std::copy(bytes.begin(), bytes.end(), this->storage.begin() + static_cast<decltype(this->storage
                                                                                           .begin())::difference_type>(where));

    return *this;
}

Frame &Frame::placeAt(size_t where, const byte_t *bytesArray, size_t arraySize)
{
    this->resizeToProvideElementAtIndex(where + arraySize - 1);

    std::copy(bytesArray, bytesArray + arraySize, this->storage.begin() + static_cast<decltype(this->storage
                                                                                                   .begin())::difference_type>(where));
    return *this;
}

Frame &Frame::insert(const FrameEntity &byte)
{
    return this->placeAt(this->size(), byte);
}

Frame &Frame::insert(const Frame &bytes)
{
    return this->placeAt(this->size(), bytes);
}

Frame &Frame::insert(byte_t byte)
{
    return this->placeAt(this->size(), FrameEntity{byte});
}

Frame &Frame::insert(const std::vector<uint8_t> &bytes)
{
    return this->placeAt(this->size(), bytes);
}

Frame &Frame::insert(const std::vector<FrameEntity> &bytes)
{
    return this->placeAt(this->size(), bytes);
}

Frame &Frame::insert(const byte_t *bytesArray, size_t arraySize)
{
    return this->placeAt(this->size(), bytesArray, arraySize);
}

FrameEntity &Frame::operator[](size_t index)
{
    if (index >= this->size())
    {
        throw std::out_of_range{"Index [" + std::to_string(index) + "] exceeds current number of elements: " + std::to_string(this->size())};
    }
    return this->storage[index];
}

const FrameEntity &Frame::operator[](size_t index) const
{
    if (index >= this->size())
    {
        throw std::out_of_range{"Index [" + std::to_string(index) + "] exceeds current number of elements: " + std::to_string(this->size())};
    }
    return this->storage[index];
}

bool Frame::spliceIsValid(size_t beginIndex, size_t endIndex)
{
    if (beginIndex > endIndex)
    {
        return false;
    }

    if (beginIndex >= this->size())
    {
        return false;
    }

    if (endIndex >= this->size())
    {
        return false;
    }

    return true;
}

Frame Frame::operator()(size_t beginIndex, size_t endIndex)
{
    if (beginIndex > endIndex)
    {
        throw std::invalid_argument{"Begin index is bigger than end index."};
    }

    if (!this->spliceIsValid(beginIndex, endIndex))
    {
        throw std::out_of_range{"Splice is pointing to invalid elements range [" + std::to_string(beginIndex) + " - " + std::to_string(endIndex) + "]; valid range: [0 - " + std::to_string(this->size() - 1) + "]."};
    }

    std::vector<FrameEntity> temporaryStorage;
    std::copy(this->storage.begin() + static_cast<decltype(this->storage
                                                               .begin())::difference_type>(beginIndex), this->storage
                                                                                                            .begin() + static_cast<decltype(this
            ->storage.begin())::difference_type>(endIndex + 1), std::back_inserter(temporaryStorage));
    return Frame(temporaryStorage);
}

void Frame::reverse()
{
    std::reverse(this->storage.begin(), this->storage.end());
}

byte_t *Frame::data()
{
    this->byteStorage.clear();
    std::copy(this->storage.begin(), this->storage.end(), std::back_inserter(this->byteStorage));
    return this->byteStorage.data();
}

void Frame::resizeToProvideElementAtIndex(size_t index)
{
    const auto count = index + 1;
    if (count > this->size())
    {
        this->storage.resize(count, this->defaultFill);
    }
}
