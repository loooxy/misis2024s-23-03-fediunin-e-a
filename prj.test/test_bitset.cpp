//
// Created by egorf on 31.03.2024.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "bitset/bitset.hpp"

TEST_CASE("BitSet basic operations") {
    BitSet bitset(10);

    CHECK(bitset.Size() == 10);

    bitset.Set(0, true);
    CHECK(bitset.Get(0) == true);

    bitset.Set(0, false);
    CHECK(bitset.Get(0) == false);

    bitset.Set(5, true);
    CHECK(bitset.Get(5) == true);

    bitset.Resize(20);
    CHECK(bitset.Size() == 20);
    CHECK(bitset.Get(5) == true);
}

TEST_CASE("BitProxy operations") {
    BitSet bitset(42);

    bitset[0] = true;
    CHECK(bitset[0] == true);

    bitset[0] = false;
    CHECK(bitset[0] == false);

    bitset[5] = true;
    CHECK(bitset[5] == true);

    bitset[41] = true;
    CHECK(bitset[41] == true);
}

TEST_CASE("BitSet bitwise operations") {
    BitSet bitset1(10);
    bitset1.Set(0, true);
    bitset1.Set(1, true);

    BitSet bitset2(10);
    bitset2.Set(1, true);
    bitset2.Set(2, true);

    BitSet bitset3 = bitset1 & bitset2;
    CHECK(bitset3.Get(0) == false);
    CHECK(bitset3.Get(1) == true);
    CHECK(bitset3.Get(2) == false);

    bitset3 = bitset1 | bitset2;
    CHECK(bitset3.Get(0) == true);
    CHECK(bitset3.Get(1) == true);
    CHECK(bitset3.Get(2) == true);

    bitset3 = bitset1 ^ bitset2;
    CHECK(bitset3.Get(0) == true);
    CHECK(bitset3.Get(1) == false);
    CHECK(bitset3.Get(2) == true);
}

TEST_CASE("BitSet serialization") {
    BitSet bitset(10);
    bitset.Set(0, true);
    bitset.Set(1, true);

    // Serialize to binary
    std::ofstream ofs("bitset.bin", std::ios::binary);
    bitset.WriteBinary(ofs);
    ofs.close();

    // Deserialize from binary
    BitSet deserializedBitset(10);
    std::ifstream ifs("bitset.bin", std::ios::binary);
    deserializedBitset.ReadBinary(ifs);
    ifs.close();

    CHECK(deserializedBitset.Get(0) == true);
    CHECK(deserializedBitset.Get(1) == true);
}