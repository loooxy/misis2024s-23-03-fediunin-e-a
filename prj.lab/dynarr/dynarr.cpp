//
// Created by egorf on 10.12.2023.
//
#include "dynarr/dynarr.hpp"
#include <stdexcept>

DynArr::DynArr(const DynArr& rhs)
    : size_(rhs.size_), capacity_(rhs.size_) {
  data_ = new float[rhs.size_];
  for (int i = 0; i < rhs.size_; ++i) {
    *(data_ + i) = *(rhs.data_ + i);
  }
}

DynArr::DynArr(const ptrdiff_t size)
    : size_(size), capacity_(size) {
  if (size <= 0) {
    throw std::invalid_argument("Zero size is not allowed in DynArr ctor");
  }
  data_ = new float[size] {0};
}

DynArr& DynArr::operator=(DynArr const& rhs) {
  if (this != &rhs) {
    delete[] data_;
    size_ = rhs.size_;
    capacity_ = rhs.size_ * 2;
    data_ = new float[capacity_] {};
    for (int i = 0; i < rhs.size_; i++) {
      data_[i] = rhs.data_[i];
    }
  }
  return *this;
}

DynArr::~DynArr() {
  delete[] data_;
  data_ = nullptr;
  capacity_ = 0;
}

void DynArr::Resize(const std::ptrdiff_t size) {
  if (size <= 0) {
    throw std::invalid_argument("Resizing by negative value");
  }
  if (size > capacity_) {
    std::ptrdiff_t new_capacity = size * 2;
    auto new_data = new float[new_capacity] {0};
    for (int i = 0; i < size_; i++)
      new_data[i] = data_[i];
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  } else {
    for (std::ptrdiff_t i = size_; i < size; i++) {
      data_[i] = 0;
    }
  }
  size_ = size;
}

float& DynArr::operator[](const std::ptrdiff_t idx) {
  if (idx >= size_ || idx < 0) {
    throw std::out_of_range("Index out of range");
  }
  return data_[idx];
}

const float& DynArr::operator[](const std::ptrdiff_t idx) const {
  if (idx >= size_ || idx < 0) {
    throw std::out_of_range("Index out of range");
  }
  return data_[idx];
}
