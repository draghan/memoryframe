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

#include "external/Catch2/single_include/catch2/catch.hpp"

#include "Frame.hpp"


FrameEntity getFrame()
{
    byte_t value = 0b01010101;
    FrameEntity x{value};
    return x;
}

TEST_CASE("Memory: frame entity bitwise operatos", "[memory][Frame]")
{
    SECTION("~")
    {
        constexpr byte_t expectedValue = ~0b11110000u;
        FrameEntity f{byte_t{0b11110000}};
        f = ~f;
        REQUIRE(f == expectedValue);
        REQUIRE(f[0] == 1);
        REQUIRE(f[7] == 0);
    }
}

TEST_CASE("Memory: frame entity comparison", "[memory][Frame]")
{
    SECTION("notEquality FrameEntities")
    {
        byte_t value = 0b01010101;
        FrameEntity x{value};
        FrameEntity y{x};

        y[0] = 0;
        y[1] = 0;

        REQUIRE(x != y);
    }

    SECTION("Equality FrameEntities")
    {
        byte_t value = 0b01010101;
        FrameEntity x{value};
        FrameEntity y{x};

        REQUIRE(x == y);
    }

    SECTION("Equality bitset")
    {
        byte_t value = 0b01010101;
        FrameEntity x{value};
        std::bitset<8> y;
        y[0] = 1;
        y[1] = 0;
        y[2] = 1;
        y[3] = 0;
        y[4] = 1;
        y[5] = 0;
        y[6] = 1;
        y[7] = 0;

        REQUIRE(x == y);
    }
}

TEST_CASE("Memory: frame entity assignment", "[memory][Frame]")
{
    SECTION("value")
    {
        byte_t value = 0b01010101;
        FrameEntity x;
        x = value;

        REQUIRE(x[0] == 1);
        REQUIRE(x[1] == 0);
        REQUIRE(x[2] == 1);
        REQUIRE(x[3] == 0);
        REQUIRE(x[4] == 1);
        REQUIRE(x[5] == 0);
        REQUIRE(x[6] == 1);
        REQUIRE(x[7] == 0);
    }

    SECTION("bitset")
    {
        byte_exposed_t value = 0b01010101;
        FrameEntity f{};
        f = value;
        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 0);
        REQUIRE(f[2] == 1);
        REQUIRE(f[3] == 0);
        REQUIRE(f[4] == 1);
        REQUIRE(f[5] == 0);
        REQUIRE(f[6] == 1);
        REQUIRE(f[7] == 0);
    }

//    SECTION("string")
//    {
//        std::string value = "0b01010101";
//        FrameEntity f{};
//        f = value;
//        REQUIRE(f[0] == 1);
//        REQUIRE(f[1] == 0);
//        REQUIRE(f[2] == 1);
//        REQUIRE(f[3] == 0);
//        REQUIRE(f[4] == 1);
//        REQUIRE(f[5] == 0);
//        REQUIRE(f[6] == 1);
//        REQUIRE(f[7] == 0);
//    }

}

TEST_CASE("Memory: frame entity conversion", "[memory][Frame]")
{
    SECTION("To value")
    {
        byte_t value = 0b01010101;
        FrameEntity x{value};

        byte_t converted = x;
        REQUIRE(value == converted);
    }

    SECTION("To bitset")
    {
        byte_t value = 0b01010101;
        FrameEntity x{value};

        byte_exposed_t converted = x;
        REQUIRE(value == converted.to_ulong());
    }

//    SECTION("To string")
//    {
//        byte_t value = 0xAF;
//        FrameEntity x{value};
//
//        std::string converted = x;
//        REQUIRE(converted == "af");
//    }
}

TEST_CASE("Memory: frame entity creation", "[memory][Frame]")
{
    SECTION("Default ctor")
    {
        FrameEntity byteZero{};
        FrameEntity byteOne{true};

        REQUIRE(byteOne[0] == true);
        REQUIRE(byteOne[1] == true);
        REQUIRE(byteOne[2] == true);
        REQUIRE(byteOne[3] == true);
        REQUIRE(byteOne[4] == true);
        REQUIRE(byteOne[5] == true);
        REQUIRE(byteOne[6] == true);
        REQUIRE(byteOne[7] == true);
        REQUIRE_THROWS(byteOne[8]);

        REQUIRE(byteZero[0] == false);
        REQUIRE(byteZero[1] == false);
        REQUIRE(byteZero[2] == false);
        REQUIRE(byteZero[3] == false);
        REQUIRE(byteZero[4] == false);
        REQUIRE(byteZero[5] == false);
        REQUIRE(byteZero[6] == false);
        REQUIRE(byteZero[7] == false);
        REQUIRE_THROWS(byteZero[8]);
    }

    SECTION("Creation from single value")
    {
        byte_t value = 0b01010101;
        FrameEntity f{value};
        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 0);
        REQUIRE(f[2] == 1);
        REQUIRE(f[3] == 0);
        REQUIRE(f[4] == 1);
        REQUIRE(f[5] == 0);
        REQUIRE(f[6] == 1);
        REQUIRE(f[7] == 0);
    }

    SECTION("Creation from bitset")
    {
        byte_exposed_t value = 0b01010101;
        FrameEntity f{value};
        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 0);
        REQUIRE(f[2] == 1);
        REQUIRE(f[3] == 0);
        REQUIRE(f[4] == 1);
        REQUIRE(f[5] == 0);
        REQUIRE(f[6] == 1);
        REQUIRE(f[7] == 0);
    }

//    SECTION("Creation from string")
//    {
//        std::string value = "0b01010101";
//        FrameEntity f{value};
//        REQUIRE(f[0] == 1);
//        REQUIRE(f[1] == 0);
//        REQUIRE(f[2] == 1);
//        REQUIRE(f[3] == 0);
//        REQUIRE(f[4] == 1);
//        REQUIRE(f[5] == 0);
//        REQUIRE(f[6] == 1);
//        REQUIRE(f[7] == 0);
//    }

    SECTION("Copy constructor")
    {
        byte_t value = 0b01010101;
        FrameEntity x{value};
        FrameEntity f{x};
        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 0);
        REQUIRE(f[2] == 1);
        REQUIRE(f[3] == 0);
        REQUIRE(f[4] == 1);
        REQUIRE(f[5] == 0);
        REQUIRE(f[6] == 1);
        REQUIRE(f[7] == 0);

        REQUIRE(x[0] == 1);
        REQUIRE(x[1] == 0);
        REQUIRE(x[2] == 1);
        REQUIRE(x[3] == 0);
        REQUIRE(x[4] == 1);
        REQUIRE(x[5] == 0);
        REQUIRE(x[6] == 1);
        REQUIRE(x[7] == 0);
    }

    SECTION("Move constructor")
    {
        FrameEntity f{getFrame()};
        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 0);
        REQUIRE(f[2] == 1);
        REQUIRE(f[3] == 0);
        REQUIRE(f[4] == 1);
        REQUIRE(f[5] == 0);
        REQUIRE(f[6] == 1);
        REQUIRE(f[7] == 0);
    }
}

TEST_CASE("Memory: frame insert", "[memory][Frame]")
{
    SECTION("Insert array")
    {
        Frame f{1, 2};
        uint8_t g[]{3, 4, 5};

        f.insert(g, 2);
        REQUIRE(f.size() == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }

    SECTION("Insert frame")
    {
        Frame f{1, 2};
        Frame g{3, 4};

        f.insert(g);
        REQUIRE(f.size() == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }

    SECTION("Insert vector of values")
    {
        Frame f{1, 2};
        std::vector<uint8_t> v{3, 4};

        f.insert(v);
        REQUIRE(f.size() == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }

    SECTION("Insert single value")
    {
        Frame f{1, 2};

        f.insert(6);
        REQUIRE(f.size() == 3);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 6);
    }
}

void expect1_2_3(uint8_t table[], size_t size)
{
    REQUIRE(size == 3);
    REQUIRE(table[0] == 1);
    REQUIRE(table[1] == 2);
    REQUIRE(table[2] == 3);
}

TEST_CASE("Memory: reverse", "[memory][Frame]")
{
    SECTION("reverse")
    {
        Frame f{1, 2, 3};
        f.reverse();
        REQUIRE(f.size() == 3);
        REQUIRE(f[0] == 3);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 1);
    }
}

TEST_CASE("Memory: data access", "[memory][Frame]")
{
    SECTION("Data access")
    {
        Frame f{1, 2, 3};
        expect1_2_3(f.data(), f.size());
    }
}

TEST_CASE("Memory: frame indexing", "[memory][Frame]")
{
    SECTION("Bit indexing")
    {
        Frame f{0b11000000, 0b10000011};
        REQUIRE(f[0][0] == 0);
        REQUIRE(f[0][1] == 0);
        REQUIRE(f[0][2] == 0);
        REQUIRE(f[0][3] == 0);
        REQUIRE(f[0][4] == 0);
        REQUIRE(f[0][5] == 0);
        REQUIRE(f[0][6] == 1);
        REQUIRE(f[0][7] == 1);

        REQUIRE(f[1][0] == 1);
        REQUIRE(f[1][1] == 1);
        REQUIRE(f[1][2] == 0);
        REQUIRE(f[1][3] == 0);
        REQUIRE(f[1][4] == 0);
        REQUIRE(f[1][5] == 0);
        REQUIRE(f[1][6] == 0);
        REQUIRE(f[1][7] == 1);
    }

    SECTION("Byte indexing")
    {
        Frame f{0b11000000, 0b11000011};
        REQUIRE(f[0] == 0b11000000);
        REQUIRE(f[1] == 0b11000011);
    }
}

TEST_CASE("Memory: frame splice", "[memory][Frame]")
{
    SECTION("Valid splice")
    {
        Frame f{0, 1, 2, 3};
        REQUIRE(f(0, 2) == Frame{0, 1, 2});
        REQUIRE(f(1, 3) == Frame{1, 2, 3});
        REQUIRE(f(0, 3) == Frame{0, 1, 2, 3});
        REQUIRE(f(0, 0) == Frame{0});
    }

    SECTION("Checking splice")
    {
        Frame f{0, 1, 2, 3};
        REQUIRE(f.spliceIsValid(0, 3));
        REQUIRE(!f.spliceIsValid(3, 0));
        REQUIRE(!f.spliceIsValid(0, 4));
        REQUIRE(!f.spliceIsValid(4, 5));
        REQUIRE(!f.spliceIsValid(4, 4));
    }

    SECTION("Invalid splice")
    {
        Frame f{0, 1, 2, 3};
        REQUIRE_THROWS(f(3, 0));
        REQUIRE_THROWS(f(0, 4));
        REQUIRE_THROWS(f(4, 5));
        REQUIRE_THROWS(f(4, 4));
    }
}


TEST_CASE("Memory: frame place at", "[memory][Frame]")
{
    SECTION("Insert array")
    {
        Frame f{1, 2};
        uint8_t g[]{3, 4};

        f.placeAt(1, g, 2);
        REQUIRE(f.size() == 3);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 3);
        REQUIRE(f[2] == 4);
    }

    SECTION("Insert frame")
    {
        Frame f{1, 2};
        Frame g{3, 4};

        f.placeAt(2, g);
        REQUIRE(f.size() == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }

    SECTION("Insert vector of values")
    {
        Frame f{1, 2};
        std::vector<uint8_t> v{3, 4};

        f.placeAt(3, v);
        REQUIRE(f.size() == 5);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 0);
        REQUIRE(f[3] == 3);
        REQUIRE(f[4] == 4);
    }

    SECTION("Insert single value")
    {
        Frame f{1, 2};

        f.placeAt(2, 6);
        REQUIRE(f.size() == 3);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 6);

        f.placeAt(5, 55);
        REQUIRE(f.size() == 6);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 6);
        REQUIRE(f[3] == 0);
        REQUIRE(f[4] == 0);
        REQUIRE(f[5] == 55);
    }
}

TEST_CASE("Memory: frame concatenation", "[memory][Frame]")
{
    SECTION("+= single value")
    {
        Frame f{1, 2};

        f += 5;

        REQUIRE(f.size() == 3);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 5);
    }

    SECTION("+= braced")
    {
        Frame f{1, 2};

        f += {3, 4};

        REQUIRE(f.size() == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }

    SECTION("+= vector")
    {
        Frame f{1, 2};

        std::vector<uint8_t> g{3, 4};

        f += g;

        REQUIRE(f.size() == 4);
        REQUIRE(g.size() == 2);

        REQUIRE(g[0] == 3);
        REQUIRE(g[1] == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }

    SECTION("+= Frame")
    {
        Frame f{1, 2};

        Frame g{3, 4};

        f += g;

        REQUIRE(f.size() == 4);
        REQUIRE(g.size() == 2);

        REQUIRE(g[0] == 3);
        REQUIRE(g[1] == 4);

        REQUIRE(f[0] == 1);
        REQUIRE(f[1] == 2);
        REQUIRE(f[2] == 3);
        REQUIRE(f[3] == 4);
    }
}

TEST_CASE("Memory: frame comparison", "[memory][Frame]")
{
    SECTION("Frames equality")
    {
        Frame f{{1, 2}};

        Frame g{1, 2};

        REQUIRE(f.size() == 2);
        REQUIRE(g.size() == 2);
        REQUIRE(f == g);
    }

    SECTION("Equality with table")
    {
        Frame f{{1, 2}};

        uint8_t v[] = {1, 2};

        REQUIRE(f == Frame(v, 2));
    }

    SECTION("Equality with vector")
    {
        Frame f{{1, 2}};

        std::vector<uint8_t> v{1, 2};

        REQUIRE(f == v);
    }

    SECTION("Frames inequality")
    {
        Frame f{{1, 2}};

        Frame g{2, 2};

        REQUIRE(f.size() == 2);
        REQUIRE(g.size() == 2);
        REQUIRE(f != g);
    }

    SECTION("Inequality with table")
    {
        Frame f{{1, 2}};

        uint8_t v[] = {2, 2};

        REQUIRE(f != Frame(v, 2));
    }

    SECTION("Ineuality with vector")
    {
        Frame f{{1, 2}};

        std::vector<uint8_t> v{2, 2};

        REQUIRE(f != v);
    }
}

TEST_CASE("Memory: frame creation", "[memory][Frame]")
{
    SECTION("Default ctor")
    {
        Frame f{};

        REQUIRE(f.size() == 0);
        REQUIRE_THROWS(f[0] == static_cast<uint8_t>(1));
    }

    SECTION("Copy ctor")
    {
        Frame f{{1, 2}};

        Frame g{f};

        REQUIRE(f.size() == 2);
        REQUIRE(g.size() == 2);
        REQUIRE(f == g);

        REQUIRE(f[0] == g[0]);
        REQUIRE(f[1] == g[1]);
        REQUIRE_THROWS(f[2]);
        REQUIRE_THROWS(g[2]);

// change value in one of them:
        REQUIRE_NOTHROW(g[0] = 15);
        REQUIRE(f[0] != g[0]);
        REQUIRE(f[0] == 1);
        REQUIRE(g[0] == 15);
        REQUIRE(f[1] == g[1]);
    }

    SECTION("Default filling")
    {
        Frame zero(5, false);
        Frame one(5, true);

        std::bitset<8> bits;
        bool value = false;
        bits[0] = value;
        bits[1] = value;
        bits[2] = value;
        bits[3] = value;
        bits[4] = value;
        bits[5] = value;
        bits[6] = value;
        bits[7] = value;

        REQUIRE(zero[0] == bits);
        REQUIRE(zero[1] == bits);
        REQUIRE(zero[2] == bits);
        REQUIRE(zero[3] == bits);
        REQUIRE(zero[4] == bits);
        REQUIRE_THROWS(zero[5] == bits);

        value = true;
        bits[0] = value;
        bits[1] = value;
        bits[2] = value;
        bits[3] = value;
        bits[4] = value;
        bits[5] = value;
        bits[6] = value;
        bits[7] = value;

        REQUIRE(one[0] == bits);
        REQUIRE(one[1] == bits);
        REQUIRE(one[2] == bits);
        REQUIRE(one[3] == bits);
        REQUIRE(one[4] == bits);
        REQUIRE_THROWS(one[5] == bits);
    }

    SECTION("From vector of bytes")
    {
        std::vector<uint8_t> bytes{10, 20, 50, 100};
        Frame f{bytes};

        REQUIRE(f.size() == bytes.size());
        REQUIRE(f == bytes);
    }

    SECTION("From braced values")
    {
        Frame f{10, 20, 50, 100};

        REQUIRE(f.size() == 4);
        REQUIRE(f[0] == 10);
        REQUIRE(f[1] == 20);
        REQUIRE(f[2] == 50);
        REQUIRE(f[3] == 100);
    }

    SECTION("From array")
    {
        uint8_t array[] = {10, 20, 50, 100};
        Frame f{array, 4};

        REQUIRE(f.size() == 4);
        REQUIRE(f[0] == 10);
        REQUIRE(f[1] == 20);
        REQUIRE(f[2] == 50);
        REQUIRE(f[3] == 100);
    }
}
