//
// Created by Егор Федюнин on 05.02.2024.
//

#pragma once
#ifndef MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_StackArrT_HPP_
#define MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_StackArrT_HPP_

#include "complex/complex.hpp"
#include <stdexcept>
#include <algorithm>

template<class T>
class StackArrT {
 public:
  StackArrT() = default;

  StackArrT(const StackArrT&);

  StackArrT(StackArrT&&) noexcept;

  ~StackArrT();

  StackArrT& operator=(const StackArrT&);

  StackArrT& operator=(StackArrT&&) noexcept;

  void Push(const T& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const T& Top() const&;

  [[nodiscard]] T& Top() &;

  void Clear() noexcept;

 private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t i_top_ = -1;
  T *data_ = nullptr;
};

template<class T>
StackArrT<T>::StackArrT(const StackArrT<T>& st)
    : i_top_(st.i_top_) {
  if (!st.IsEmpty()) {
    size_ = ((i_top_ + 1) / 4 + 1) * 4;
    data_ = new T[size_];
    std::copy(st.data_, st.data_ + i_top_ + 1, data_);
  }
}

#if 1
template<class T>
StackArrT<T>::StackArrT(StackArrT<T>&& st) noexcept {
  std::swap(st.size_, size_);
  std::swap(st.i_top_, i_top_);
  std::swap(st.data_, data_);
}
#else
template<class T>
StackArrT<T>::StackArrT(StackArrT<T>&& st) noexcept
  : StackArrT(st) {
}
#endif

template<class T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT<T>& st) {
  if (this != &st) {
    if (st.IsEmpty()) {
      Clear();
    }
    if (size_ <= st.i_top_) {
      size_ = (st.i_top_ + 4) / 4 * 4;
      T* buf = new T[size_];
      std::swap(data_, buf);
      delete[] buf;
    }
    i_top_ = st.i_top_;
    std::copy(st.data_, st.data_ + i_top_ + 1, data_);
  }
  return *this;
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(StackArrT<T>&& src) noexcept {
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

template<class T>
StackArrT<T>::~StackArrT() {
  delete[] data_;
}

template<class T>
bool StackArrT<T>::IsEmpty() const noexcept {
  return i_top_ < 0;
}

template<class T>
void StackArrT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    i_top_ -= 1;
  }
}

template<class T>
void StackArrT<T>::Push(const T& val) {
  if (nullptr == data_) {
    size_ = 1;
    data_ = new T[size_];
  } else if (size_ == i_top_ + 1) {
    auto buf = new T[size_ * 2];
    std::copy(data_, data_ + size_, buf);
    std::swap(data_, buf);
    delete[] buf;
    size_ *= 2;
  }
  data_[++i_top_] = val;
}

template<class T>
T& StackArrT<T>::Top() & {
  if (i_top_ < 0) {
    throw std::logic_error("StackArrT - try get top form empty stack.");
  }
  return data_[i_top_];
}

template<class T>
const T& StackArrT<T>::Top() const & {
  if (i_top_ < 0) {
    throw std::logic_error("StackArrT - try get top form empty stack.");
  }
  return data_[i_top_];
}

template<class T>
void StackArrT<T>::Clear() noexcept {
  i_top_ = -1;
}

#endif //MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_StackArrT_HPP_