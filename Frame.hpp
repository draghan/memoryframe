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

#include "FrameEntity.hpp"


class Frame
{
public:
    // rule of five:
    Frame();

    Frame(const Frame &f);

    Frame(Frame &&f);

    ~Frame() = default;

    Frame &operator=(const Frame &f);

    // custom c-tors
    Frame(size_t frameLength, bool defaultSet = false);

    template <typename Container>
    Frame(Container bytesCollection)
            : Frame{}
    {
        std::copy(bytesCollection.begin(), bytesCollection.end(), std::back_inserter(storage));
    }

    Frame(int) = delete;

    Frame(std::initializer_list<FrameEntity> bytesCollection);

    Frame(const byte_t *bytesArray, size_t arraySize);

    // todo: implement this
    //Frame(const std::string &hexString);

    size_t size() const;

    // comparison operators:
    bool operator==(const Frame &f) const;

    bool operator!=(const Frame &f) const;

    // appending frames
    Frame &operator+=(const Frame &f);

    Frame &operator+=(const FrameEntity &f);

    Frame &operator+=(byte_t f);

    Frame operator+(const Frame &f) const;

    Frame operator+(const FrameEntity &f) const;

    // other appending functions
    Frame &placeAt(size_t where, const FrameEntity &byte);

    Frame &placeAt(size_t where, byte_t byte);

    Frame &placeAt(size_t where, const Frame &bytes);

    Frame &placeAt(size_t where, const std::vector<uint8_t> &bytes);

    Frame &placeAt(size_t where, const std::vector<FrameEntity> &bytes);

    Frame &placeAt(size_t where, const byte_t *bytesArray, size_t arraySize);

    Frame &insert(const FrameEntity &byte);

    Frame &insert(const Frame &bytes);

    Frame &insert(byte_t byte);

    Frame &insert(const std::vector<uint8_t> &bytes);

    Frame &insert(const std::vector<FrameEntity> &bytes);

    Frame &insert(const byte_t *bytesArray, size_t arraySize);

    // indexing:
    FrameEntity &operator[](size_t index);

    const FrameEntity &operator[](size_t index) const;

    bool spliceIsValid(size_t beginIndex, size_t endIndex);

    // get splice:
    Frame operator()(size_t beginIndex, size_t endIndex);

    void reverse();

    byte_t *data();

private:
    void resizeToProvideElementAtIndex(size_t index);

    std::vector<FrameEntity> storage;
    std::vector<byte_t> byteStorage;
    const bool defaultFill;
};