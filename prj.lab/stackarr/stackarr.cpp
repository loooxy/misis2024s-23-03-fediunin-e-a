//
// Created by Егор Федюнин on 05.02.2024.
//
#include "stackarr/stackarr.hpp"
#include <stdexcept>
#include <algorithm>

StackArr::StackArr(const StackArr& st)
    : i_top_(st.i_top_) {
  if (!st.IsEmpty()) {
    size_ = ((i_top_ + 1) / 4 + 1) * 4;
    data_ = new Complex[size_];
    std::copy(st.data_, st.data_ + i_top_ + 1, data_);
  }
}

#if 1
StackArr::StackArr(StackArr&& st) noexcept {
  std::swap(st.size_, size_);
  std::swap(st.i_top_, i_top_);
  std::swap(st.data_, data_);
}
#else
StackArr::StackArr(StackArr&& st) noexcept
  : StackArr(st) {
}
#endif

StackArr& StackArr::operator=(const StackArr& st) {
  if (this != &st) {
    if (st.IsEmpty()) {
      Clear();
    }
    if (size_ <= st.i_top_) {
      size_ = (st.i_top_ + 4) / 4 * 4;
      Complex* buf = new Complex[size_];
      std::swap(data_, buf);
      delete[] buf;
    }
    i_top_ = st.i_top_;
    std::copy(st.data_, st.data_ + i_top_ + 1, data_);
  }
  return *this;
}

StackArr& StackArr::operator=(StackArr&& src) noexcept {
  if (this != &src) {
    if (!src.IsEmpty()) {
      std::swap(size_, src.size_);
      std::swap(i_top_, src.i_top_);
      std::swap(data_, src.data_);
    } else {
      Clear();
    }
  }
  return *this;
}

StackArr::~StackArr() {
  delete[] data_;
}

bool StackArr::IsEmpty() const noexcept {
  return i_top_ < 0;
}

void StackArr::Pop() noexcept {
  if (!IsEmpty()) {
    i_top_ -= 1;
  }
}

void StackArr::Push(const Complex& val) {
  if (nullptr == data_) {
    size_ = 1;
    data_ = new Complex[size_];
  } else if (size_ == i_top_ + 1) {
    auto buf = new Complex[size_ * 2];
    std::copy(data_, data_ + size_, buf);
    std::swap(data_, buf);
    delete[] buf;
    size_ *= 2;
  }
  data_[++i_top_] = val;
}

Complex& StackArr::Top() & {
  if (i_top_ < 0) {
    throw std::logic_error("StackArr - try get top form empty stack.");
  }
  return data_[i_top_];
}

const Complex& StackArr::Top() const & {
  if (i_top_ < 0) {
    throw std::logic_error("StackArr - try get top form empty stack.");
  }
  return data_[i_top_];
}

void StackArr::Clear() noexcept {
  i_top_ = -1;
}