What's this project?
====================

Utility classes with basic unit tests for manipulating of data frames.

Classes are providing handy interface for accessing ranges of bits, ranges of bytes, 
single bytes, single bits, conversions from and to different types.

Beware!
-------
This classes are not optimised in neither way; this is my first approach to define their interface in order to make them kind of useful.

Any issues / pull request are welcome.


Example
=======
```C++

// constructing from std-like containers:
const std::vector<uint8_t> v{0xDE, 0xAD, 0xBE, 0xEF};
const Frame f{v};

// access to byte range:
const Frame beef = f(2, 3);
REQUIRE(beef == Frame{0xBE, 0xEF}); // ...and constructing from initializer list

// access to single byte:
const FrameEntity ad = f[1];
REQUIRE(ad == 0xAD); // ...and comparing bytes

// access to single bit (0 - least significant bit):
REQUIRE(ad == 0b10101101);
REQUIRE(ad[0] == 1); // ...and comparing bits
REQUIRE(ad[1] == 0);
REQUIRE(ad[2] == 1);
REQUIRE(ad[3] == 1);

// access to range of bits:
REQUIRE(ad(0, 3) == 0b1101);

// appending frames:
auto fbeef = f + beef;
REQUIRE(fbeef == Frame{0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0xEF});

fbeef += 0;
REQUIRE(fbeef == Frame{0xDE, 0xAD, 0xBE, 0xEF, 0xBE, 0xEF, 0x00});

// get second, third and fourth bits from third byte:
auto foo = f[3](1, 3);
REQUIRE(foo == 0b111);

```

How to get started
==================

Copy FrameEntity.cpp / hpp and Frame.cpp / hpp to your project.