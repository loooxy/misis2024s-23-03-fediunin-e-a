//
// Created by Егор Федюнин on 05.02.2024.
//
#include "stackarr/stackarr.hpp"
#include <stdexcept>
#include <algorithm>

StackArr::StackArr(StackArr&& rhs) noexcept {
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(data_, rhs.data_);
  rhs.data_ = nullptr;
}

StackArr::StackArr(const StackArr& rhs)
    : size_(rhs.size_), capacity_(rhs.size_) {
  data_ = new Complex[rhs.size_];
  for (int i = 0; i < rhs.size_; ++i) {
    *(data_ + i) = *(rhs.data_ + i);
  }
}
StackArr& StackArr::operator=(const StackArr& rhs) {
  if (this != &rhs) {
    delete[] data_;
    size_ = rhs.size_;
    capacity_ = rhs.size_ * 2;
    data_ = new Complex[capacity_]{};
    for (int i = 0; i < rhs.size_; i++) {
      data_[i] = rhs.data_[i];
    }
  }
  return *this;
}

StackArr& StackArr::operator=(StackArr&& rhs) noexcept{
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(data_, rhs.data_);
  rhs.data_ = nullptr;
  return *this;
}

void StackArr::Push(const Complex& val) {
  if (data_ == nullptr) {
    capacity_ = 8;
    data_ = new Complex[capacity_];
  } else if (size_ + 1 > capacity_) {
    auto buf = new Complex[capacity_ * 2];
    std::copy(data_, data_ + size_, buf);
    std::swap(data_, buf);
    delete[] buf;
    capacity_ *= 2;
  }
  data_[size_++] = val;
}

void StackArr::Pop() noexcept {
  if (size_ != 0) {
    size_--;
  }
}
bool StackArr::IsEmpty() const noexcept {
  return size_ == 0;
}
const Complex& StackArr::Top() const {
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  } else {
    return data_[size_ - 1];
  }
}

Complex& StackArr::Top() {
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  } else {
    return data_[size_ - 1];
  }
}

void StackArr::Clear() noexcept {
  size_ = 0;
}

StackArr::~StackArr() {
  delete[] data_;
  data_ = nullptr;
  capacity_ = 0;
}