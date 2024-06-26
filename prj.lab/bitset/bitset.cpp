//
// Created by egorf on 31.03.2024.
//
#include "BitSet.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>



// Constructor from an int32_t
BitSet::BitSet(const std::int32_t size) : size_(size) {
  if (size <= 0) {
    throw std::runtime_error("Size must be greater than 0");
  }
  bits_.resize(size / 32 + (size % 32 != 0));
}


// Resize the bitset
void BitSet::Resize(const int32_t size) {
  if (size <= 0) {
    throw std::runtime_error("Size must be greater than 0");
  }
  size_ = size;
  bits_.resize(size / 32 + (size % 32 != 0));
}

// Get the value of a bit at a specific index
bool BitSet::Get(const int32_t idx) const {
  if (!(idx >= 0 && idx < size_)) {
    throw std::runtime_error("Index out of bounds");
  }
  return (bits_[idx / 32] & (1 << (idx % 32))) != 0;
}

// Set the value of a bit at a specific index
void BitSet::Set(const int32_t idx, const bool val) {
  if (!(idx >= 0 && idx < size_)) {
    throw std::runtime_error("Index out of bounds");
  }
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
  if (size_ != rhs.size_) {
    throw std::runtime_error("Sizes must be equal");
  }
  for (size_t i = 0; i < bits_.size(); ++i) {
    bits_[i] &= rhs.bits_[i];
  }
  return *this;
}

// Bitwise OR assignment
BitSet& BitSet::operator|=(const BitSet& rhs) {
  if (size_ != rhs.size_) {
    throw std::runtime_error("Sizes must be equal");
  }
  for (size_t i = 0; i < bits_.size(); ++i) {
    bits_[i] |= rhs.bits_[i];
  }
  return *this;
}

// Bitwise XOR assignment
BitSet& BitSet::operator^=(const BitSet& rhs) {
  if (size_ != rhs.size_) {
    throw std::runtime_error("Sizes must be equal");
  }
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
bool BitSet::operator==(const BitSet& rhs) const noexcept
{
  if (size_ != rhs.size_)
    return false;

  for (int i = 0; i < bits_.size() - 1; ++i)
    if (bits_[i] != rhs.bits_[i])
      return false;

  for (int i = (bits_.size() - 1) * 32; i < size_; ++i)
    if (Get(i) != rhs.Get(i))
      return false;

  return true;
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
  const int width = ceil(log10(size_));  // Adjust this value as needed
  for (int32_t i = 0; i < size_; i += 32) {
    os << std::setw(width) << i << ": ";
    int32_t j = 0;
    for (; j < 32 && i + j < size_; ++j) {
      if (j % 8 == 0 && j != 0) {
        os << ' ';
      }
      os << Get(i + j);
    }
    // If the number of bits is not a multiple of 8, pad with zeros
    /*for (; j < 32; ++j) {
      if (j % 8 == 0 && j != 0) {
        os << ' ';
      }
      os << '0';
    }*/
    os << '\n';
  }
  os << std::string(50, '-') << '\n';
  return os;
}


// Writing to a binary file
std::ostream& BitSet::WriteBinary(std::ostream& os) {
  // Write the input flag
  os.put(0x00);

  // Write the size of the bitset
  std::int32_t size = size_;
  os.write(reinterpret_cast<const char*>(&size), sizeof(size));

  // Write the bits_
  for (size_t i = 0; i < bits_.size(); ++i) {
    os.write(reinterpret_cast<const char*>(&bits_[i]), sizeof(bits_[i]));

    // Write the checksum byte after every 32 bytes
    if ((i + 1) % 8 == 0) {
      char checksum = 0;
      for (size_t j = i - 7; j <= i; ++j) {
        checksum ^= bits_[j] & 0xff;
        checksum ^= (bits_[j] >> 8) & 0xff;
        checksum ^= (bits_[j] >> 16) & 0xff;
        checksum ^= (bits_[j] >> 24) & 0xff;
      }
      os.put(checksum);
    }
  }

  // Write the terminating sequence
  os.put(0xff);

  return os;
}

// Reading from a text file
std::istream& BitSet::ReadTxt(std::istream& is) {
  std::string line;
  while (std::getline(is, line) && line != std::string(50, '-')) {
    std::istringstream iss{line};
    int32_t index;
    char colon;
    iss >> index >> colon;
    for (int32_t i = 0; i < line.size(); ++i) {
      char bit;
      if (i % 8 == 0 && i != 0) {
        iss.ignore();  // Skip the space
      }
      iss >> bit;
      // Ignore the padding zeros
      if (index + i < size_) {
        Set(index + i, bit == '1');
      }
    }
  }
  return is;
}
// Reading from a binary file
std::istream& BitSet::ReadBinary(std::istream& is) {
  // Read and check the input flag
  if (is.get() != 0x00) {
    is.setstate(std::ios_base::failbit);
    return is;
  }

  // Read the size of the bitset
  std::int32_t size;
  is.read(reinterpret_cast<char*>(&size), sizeof(size));
  Resize(size);

  // Read the bits_
  for (size_t i = 0; i < bits_.size(); ++i) {
    is.read(reinterpret_cast<char*>(&bits_[i]), sizeof(bits_[i]));

    // Check the checksum byte after every 32 bytes
    if ((i + 1) % 8 == 0) {
      char checksum = 0;
      for (size_t j = i - 7; j <= i; ++j) {
        checksum ^= bits_[j] & 0xff;
        checksum ^= (bits_[j] >> 8) & 0xff;
        checksum ^= (bits_[j] >> 16) & 0xff;
        checksum ^= (bits_[j] >> 24) & 0xff;
      }
      if (is.get() != checksum) {
        is.setstate(std::ios_base::failbit);
        return is;
      }
    }
  }

  // Check the terminating sequence
  if (is.get() != 0xff) {
    is.setstate(std::ios_base::failbit);
    return is;
  }

  return is;
}