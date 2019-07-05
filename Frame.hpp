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

/// Class representing basically a chunk of memory (contiguous byte table) with handy interface for indexing bytes,
/// slicing, conversions from and to different types.
class Frame
{
public:
    // rule of five:
    /// Default constructor.
    Frame();

    /// Default copy constructor.
    Frame(const Frame &f);

    /// Default move constructor.
    Frame(Frame &&f);

    /// Default destructor.
    ~Frame() = default;

    /// Default assignment operator.
    Frame &operator=(const Frame &f);

    /// Construct \p Frame with given length and set all its bits to given value.
    /// \param frameLength Amount of bytes to reserve.
    /// \param defaultSet Flag indicating whether all bits set to 1 (true) or 0 (false).
    Frame(size_t frameLength, bool defaultSet = false);

    /// Construct \p Frame from any std-like container.
    /// \example std::vector<uint8_t> v{0xDE, 0xAD, 0xBE, 0xEF}; Frame f{v};
    template <typename Container>
    Frame(Container bytesCollection)
            : Frame{}
    {
        std::copy(bytesCollection.begin(), bytesCollection.end(), std::back_inserter(storage));
    }

    /// Construct \p Frame with brace syntax from explicit given elements.
    /// \example Frame f{0xDE, 0xAD, 0xBE, 0xEF};
    Frame(std::initializer_list<FrameEntity> bytesCollection);

    Frame(int) = delete;

    /// Construct \p Frame from an old-school-style pair of pointer and length. Ensure that length is valid!
    /// \param bytesArray Pointer to array to copy bytes from.
    /// \param arraySize Declared size of the array.
    Frame(const byte_t *bytesArray, size_t arraySize);

    /// Return number of bytes.
    size_t size() const;

    /// Check whether one \p Frame object contains exactly the same bytes as the other \p Frame object.
    /// \param other  Other object to comparison.
    bool operator==(const Frame &other) const;

    /// Check whether one \p Frame object contains different bytes than the other \p Frame object.
    /// \param other  Other object to comparison.
    bool operator!=(const Frame &other) const;

    /// Append bytes from the \p other \p Frame object at the end of this \p Frame.
    Frame &operator+=(const Frame &other);

    /// Append byte at the end of this \p Frame.
    Frame &operator+=(const FrameEntity &other);

    /// Append byte at the end of this \p Frame.
    Frame &operator+=(byte_t other);

    /// Create new \p Frame with appended bytes from the \p other \p Frame object at the end of this \p Frame.
    Frame operator+(const Frame &other) const;

    /// Create new \p Frame with appended byte at the end of this \p Frame.
    Frame operator+(const FrameEntity &other) const;

    /// Put one byte at given place. Resize frame if needed.
    /// \param where Index on which the byte will be placed. Could be out of current byte range, frame will be resized and filled with default value.
    Frame &placeAt(size_t where, const FrameEntity &byte);

    /// Put one byte at given place. Resize frame if needed.
    /// \param where Index on which the byte will be placed. Could be out of current byte range, frame will be resized and filled with default value.
    Frame &placeAt(size_t where, byte_t byte);

    /// Put bytes at given place. Resize frame if needed.
    /// \param where Index on which the begin of given bytes range will be placed. Could be out of current byte range, frame will be resized and filled with default value.
    Frame &placeAt(size_t where, const Frame &bytes);

    /// Put bytes at given place. Resize frame if needed.
    /// \param where Index on which the begin of given bytes range will be placed. Could be out of current byte range, frame will be resized and filled with default value.
    Frame &placeAt(size_t where, const std::vector<uint8_t> &bytes);

    /// Put bytes at given place. Resize frame if needed.
    /// \param where Index on which the begin of given bytes range will be placed. Could be out of current byte range, frame will be resized and filled with default value.
    Frame &placeAt(size_t where, const std::vector<FrameEntity> &bytes);

    /// Put bytes at given place. Resize frame if needed.
    /// \param where Index on which the begin of given bytes range will be placed. Could be out of current byte range, frame will be resized and filled with default value.
    Frame &placeAt(size_t where, const byte_t *bytesArray, size_t arraySize);

    /// Insert one byte at the end of the frame.
    Frame &insert(const FrameEntity &byte);

    /// Insert given bytes at the end of the frame.
    Frame &insert(const Frame &bytes);

    /// Insert one byte at the end of the frame.
    Frame &insert(byte_t byte);

    /// Insert given bytes at the end of the frame.
    Frame &insert(const std::vector<uint8_t> &bytes);

    /// Insert given bytes at the end of the frame.
    Frame &insert(const std::vector<FrameEntity> &bytes);

    /// Insert given bytes at the end of the frame.
    Frame &insert(const byte_t *bytesArray, size_t arraySize);

    /// Indexing operator.
    /// \param index Index of byte to get. Throws if out of current bytes' range.
    /// \return Byte residing at given \p index.
    FrameEntity &operator[](size_t index);

    /// Indexing operator. Const version.
    /// \param index Index of byte to get. Throws if out of current bytes' range.
    /// \return Byte residing at given \p index.
    const FrameEntity &operator[](size_t index) const;

    /// Slice range of bytes from current frame. Range indexes are inclusive.
    /// \param beginIndex Starting byte index to cut, must be in the range of [0 - \p size() - 1].
    /// \param endIndex Ending byte index to cut, must be in the range of [0 - \p size()- 1] and be not less than \p beginIndex.
    /// \return New \p Frame instance.
    Frame operator()(size_t beginIndex, size_t endIndex) const;

    /// Check if given range is valid for current frame.
    bool spliceIsValid(size_t beginIndex, size_t endIndex) const;

    /// Reverse bytes order.
    Frame &reverse();

    /// Get pointer to data. Pointed table will not be updated along with the frame but keeps its value between \p data() calls.
    /// \remark Use with caution - dangling pointers guaranteed when call multiple times and store pointers' value!
    const byte_t *data();

private:
    void resizeToProvideElementAtIndex(size_t index);

    std::vector<FrameEntity> storage;
    const bool defaultFill;
};