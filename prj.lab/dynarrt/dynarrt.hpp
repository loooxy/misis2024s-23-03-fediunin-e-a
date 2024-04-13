//
// Created by egorf on 13.04.2024.
//

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_DynArrT_DynArrT_H_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_DynArrT_DynArrT_H_

#include <cstddef>
#include <complex/complex.hpp>
#include <stdexcept>

template<class T>
class DynArrT {
 public:
  DynArrT() = default;
  DynArrT(const DynArrT& rhs);
  DynArrT(DynArrT&& rhs) noexcept;
  [[nodiscard]] DynArrT(const std::ptrdiff_t size);
  ~DynArrT();
  DynArrT& operator=(const DynArrT& DynArrT);
  DynArrT& operator=(DynArrT&& rhs) noexcept;

  [[nodiscard]]std::ptrdiff_t Size() const noexcept { return size_; }
  [[nodiscard]]std::ptrdiff_t Capacity() const noexcept { return capacity_; }
  void Resize(const std::ptrdiff_t size);
  [[nodiscard]]T& operator[](const std::ptrdiff_t idx);
  [[nodiscard]]const T& operator[](const std::ptrdiff_t idx) const;
 private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  T *data_ = nullptr;
};


template<class T>
DynArrT<T>::DynArrT(DynArrT<T>&& rhs) noexcept {
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(data_, rhs.data_);
  rhs.data_ = nullptr;
}

template<class T>
DynArrT<T>::DynArrT(const DynArrT<T>& rhs)
    : size_(rhs.size_), capacity_(rhs.size_) {
  data_ = new T[rhs.size_];
  for (int i = 0; i < rhs.size_; ++i) {
    *(data_ + i) = *(rhs.data_ + i);
  }
}

template<class T>
DynArrT<T>::DynArrT(const ptrdiff_t size)
    : size_(size), capacity_(size) {
  if (size <= 0) {
    throw std::invalid_argument("Zero size is not allowed in DynArrT ctor");
  }
  data_ = new T[size]{0};
}

template<class T>
DynArrT<T>& DynArrT<T>::operator=(DynArrT<T> const& rhs) {
  if (this != &rhs) {
    delete[] data_;
    size_ = rhs.size_;
    capacity_ = rhs.size_ * 2;
    data_ = new T[capacity_]{};
    for (int i = 0; i < rhs.size_; i++) {
      data_[i] = rhs.data_[i];
    }
  }
  return *this;
}

template<class T>
DynArrT<T>::~DynArrT() {
  delete[] data_;
  data_ = nullptr;
  capacity_ = 0;
}

template<class T>
void DynArrT<T>::Resize(const std::ptrdiff_t size) {
  if (size <= 0) {
    throw std::invalid_argument("Resizing by negative value");
  }
  if (size > capacity_) {
    std::ptrdiff_t new_capacity = size * 2;
    auto new_data = new T[new_capacity]{0};
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

template<class T>
T& DynArrT<T>::operator[](const std::ptrdiff_t idx) {
  if (idx >= size_ || idx < 0) {
    throw std::out_of_range("Index out of range");
  }
  return data_[idx];
}

template<class T>
const T& DynArrT<T>::operator[](const std::ptrdiff_t idx) const {
  if (idx >= size_ || idx < 0) {
    throw std::out_of_range("Index out of range");
  }
  return data_[idx];
}

template<class T>
DynArrT<T>& DynArrT<T>::operator=(DynArrT<T>&& rhs) noexcept {
  if (this != &rhs) {
    std::swap(size_, rhs.size_);
    std::swap(capacity_, rhs.capacity_);
    std::swap(data_, rhs.data_);
    rhs.data_ = nullptr;
  }
  return *this;
}

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_DynArrT_DynArrT_H_
