//
// Created by Егор Федюнин on 05.02.2024.
//
#include "stackarr/stackarr.hpp"

StackArr::StackArr(const StackArr &rhs)
  : size_(rhs.size_), capacity_(rhs.size_) {
    data_ = new Complex[rhs.size_];
    for (int i = 0; i < rhs.size_; ++i) {
      *(data_ + i) = *(rhs.data_ + i);
    }
}
StackArr &StackArr::operator=(const StackArr &rhs) {
  if (this != &rhs) {
    delete[] data_;
    size_ = rhs.size_;
    capacity_ = rhs.size_ * 2;
    data_ = new Complex[capacity_] {};
    for (int i = 0; i < rhs.size_; i++) {
      data_[i] = rhs.data_[i];
    }
  }
  return *this;
}
void StackArr::Push(const Complex &) {
  if (size_ + 1 > capacity_) {
    std::ptrdiff_t new_capacity = (size_ + 1) * 2;
    auto new_data = new Complex[new_capacity] { {0,0}};
    for (int i = 0; i < size_; i++)
      new_data[i] = data_[i];
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  } else {
    for (std::ptrdiff_t i = size_; i < size_ + 1; i++) {
      data_[i] = {0,0};
    }
  }
  size_ += 1;
}
void StackArr::Pop() noexcept {

}
bool StackArr::IsEmpty() noexcept {
  return false;
}
const Complex &StackArr::Top() {

}
