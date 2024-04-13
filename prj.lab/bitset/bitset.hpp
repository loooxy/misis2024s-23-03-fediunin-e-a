//
// Created by egorf on 31.03.2024.
//
#pragma once
#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_BITSET_H
#define MISIS2023F_23_03_FEDIUNIN_E_A_BITSET_H


#include <cstdint>
#include <iosfwd>
#include <vector>

class BitProxy;

class BitSet {
public:
    BitSet() = default;

    BitSet(const BitSet&) = default;

    BitSet(BitSet&&) = default;

    BitSet(const std::int32_t);

    BitSet& operator=(const BitSet&) = default;

    BitSet& operator=(BitSet&&) = default;

    BitProxy operator[](std::int32_t idx);

    ~BitSet() = default;

    [[nodiscard]] bool operator==(const BitSet& rhs) const noexcept;

    [[nodiscard]] bool operator!=(const BitSet& rhs) const noexcept;

    [[nodiscard]] int32_t Size() const noexcept { return size_; }

    void Resize(const int32_t size); // 0 < size

    [[nodiscard]] bool Get(const int32_t idx) const;

    void Set(const int32_t idx, const bool val);

    void Fill(const bool val) noexcept;

    [[nodiscard]] BitSet& operator&=(const BitSet& rhs);

    [[nodiscard]] BitSet& operator|=(const BitSet& rhs);

    [[nodiscard]] BitSet& operator^=(const BitSet& rhs);

    [[nodiscard]] BitSet operator~();


    // ? operator[](const int32_t) - what can return
    std::ostream& WriteTxt(std::ostream&) const;
    std::ostream& WriteBinary(std::ostream&);
    std::istream& ReadTxt(std::istream&);
    std::istream& ReadBinary(std::istream&);
private:
    std::int32_t size_ = 0;
    std::vector<uint32_t> bits_;
};

class BitProxy {
public:
    BitProxy(BitSet& bitset, std::int32_t idx) : bitset_(bitset), idx_(idx) {}

    BitProxy& operator=(bool val) {
        bitset_.Set(idx_, val);
        return *this;
    }

    operator bool() const {
        return bitset_.Get(idx_);
    }

private:
    BitSet& bitset_;
    std::int32_t idx_ = 0;
};

std::ostream& operator<<(std::ostream&, const BitSet&);
std::istream& operator>>(std::istream&, BitSet&);



[[nodiscard]] BitSet operator&(const BitSet& lhs, const BitSet& rhs);

[[nodiscard]] BitSet operator|(const BitSet& lhs, const BitSet& rhs);

[[nodiscard]] BitSet operator^(const BitSet& lhs, const BitSet& rhs);

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_BITSET_H
