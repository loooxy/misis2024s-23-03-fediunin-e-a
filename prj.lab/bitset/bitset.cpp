//
// Created by egorf on 31.03.2024.
//
#include "BitSet.hpp"
#include <iostream>
#include <cassert>

// Constructor from an int32_t
BitSet::BitSet(const std::int32_t size) : size_(size) {
    assert(size > 0);
    bits_.resize(size / 32 + (size % 32 != 0));
}

// Resize the bitset
void BitSet::Resize(const int32_t size) {
    assert(size > 0);
    size_ = size;
    bits_.resize(size / 32 + (size % 32 != 0));
}

// Get the value of a bit at a specific index
bool BitSet::Get(const int32_t idx) const {
    assert(idx >= 0 && idx < size_);
    return (bits_[idx / 32] & (1 << (idx % 32))) != 0;
}

// Set the value of a bit at a specific index
void BitSet::Set(const int32_t idx, const bool val) {
    assert(idx >= 0 && idx < size_);
    if (val) {
        bits_[idx / 32] |= (1 << (idx % 32));
    } else {
        bits_[idx / 32] &= ~(1 << (idx % 32));
    }
}

// Fill the bitset with a specific value
void BitSet::Fill(const bool val) noexcept {
    if (val) {
        for (auto& bit : bits_) {
            bit = ~0;
        }
    } else {
        bits_.assign(bits_.size(), 0);
    }
}

// Bitwise AND assignment
BitSet& BitSet::operator&=(const BitSet& rhs) {
    assert(size_ == rhs.size_);
    for (size_t i = 0; i < bits_.size(); ++i) {
        bits_[i] &= rhs.bits_[i];
    }
    return *this;
}

// Bitwise OR assignment
BitSet& BitSet::operator|=(const BitSet& rhs) {
    assert(size_ == rhs.size_);
    for (size_t i = 0; i < bits_.size(); ++i) {
        bits_[i] |= rhs.bits_[i];
    }
    return *this;
}

// Bitwise XOR assignment
BitSet& BitSet::operator^=(const BitSet& rhs) {
    assert(size_ == rhs.size_);
    for (size_t i = 0; i < bits_.size(); ++i) {
        bits_[i] ^= rhs.bits_[i];
    }
    return *this;
}

// Bitwise NOT
BitSet BitSet::operator~() {
    BitSet result(*this);
    for (auto& bit : result.bits_) {
        bit = ~bit;
    }
    return result;
}

// Comparison operators
bool BitSet::operator==(const BitSet& rhs) const noexcept {
    return size_ == rhs.size_ && bits_ == rhs.bits_;
}

bool BitSet::operator!=(const BitSet& rhs) const noexcept {
    return !(*this == rhs);
}

// Bitwise operations
BitSet operator&(const BitSet& lhs, const BitSet& rhs) {
    BitSet result(lhs);
    result &= rhs;
    return result;
}

BitSet operator|(const BitSet& lhs, const BitSet& rhs) {
    BitSet result(lhs);
    result |= rhs;
    return result;
}

BitSet operator^(const BitSet& lhs, const BitSet& rhs) {
    BitSet result(lhs);
    result ^= rhs;
    return result;
}

BitProxy BitSet::operator[](std::int32_t idx) {
    return BitProxy{*this, idx};
}

// Input/Output operations
std::ostream& operator<<(std::ostream& os, const BitSet& bs) {
    for (int32_t i = 0; i < bs.Size(); ++i) {
        os << bs.Get(i);
    }
    return os;
}

std::istream& operator>>(std::istream& is, BitSet& bs) {
    for (int32_t i = 0; i < bs.Size(); ++i) {
        bool bit;
        is >> bit;
        bs.Set(i, bit);
    }
    return is;
}

// Writing to a text file
std::ostream& BitSet::WriteTxt(std::ostream& os) const {
    for (int32_t i = 0; i < size_; ++i) {
        os << Get(i);
    }
    return os;
}

// Writing to a binary file
std::ostream& BitSet::WriteBinary(std::ostream& os) {
    os.write(reinterpret_cast<const char*>(bits_.data()), bits_.size() * sizeof(uint32_t));
    return os;
}

// Reading from a text file
std::istream& BitSet::ReadTxt(std::istream& is) {
    for (int32_t i = 0; i < size_; ++i) {
        bool bit;
        is >> bit;
        Set(i, bit);
    }
    return is;
}

// Reading from a binary file
std::istream& BitSet::ReadBinary(std::istream& is) {
    is.read(reinterpret_cast<char*>(bits_.data()), bits_.size() * sizeof(uint32_t));
    return is;
}