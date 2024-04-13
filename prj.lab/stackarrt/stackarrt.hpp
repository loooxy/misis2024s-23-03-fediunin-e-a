//
// Created by Егор Федюнин on 08.04.2024.
//

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_StackArrTT_StackArrTT_HPP_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_StackArrTT_StackArrTT_HPP_

#include <cstddef>
#include <algorithm>

template<class T>
class StackArrT {
 public:
  [[nodiscard]] StackArrT() = default;

  [[nodiscard]] StackArrT(const StackArrT&);

  [[nodiscard]] StackArrT(StackArrT&&) noexcept;

  ~StackArrT();

  [[nodiscard]]StackArrT& operator=(const StackArrT&);

  [[nodiscard]]StackArrT& operator=(StackArrT&&) noexcept;

  void Push(const T& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const T& Top() const &;

  [[nodiscard]] T& Top() &;

  void Clear() noexcept;

 private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  T* data_ = nullptr;
};

template<class T>
StackArrT<T>::StackArrT(StackArrT&& rhs) noexcept {
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(data_, rhs.data_);
  rhs.data_ = nullptr;
}

template<class T>
StackArrT<T>::StackArrT(const StackArrT& rhs)
    : size_(rhs.size_), capacity_(rhs.size_) {
  data_ = new T[rhs.size_];
  for (int i = 0; i < rhs.size_; ++i) {
    *(data_ + i) = *(rhs.data_ + i);
  }
}

template<class T>
StackArrT<T>& StackArrT<T>::operator=(const StackArrT<T>& rhs) {
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
StackArrT<T>& StackArrT<T>::operator=(StackArrT&& rhs) noexcept{
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(data_, rhs.data_);
  rhs.data_ = nullptr;
  return *this;
}

template<class T>
void StackArrT<T>::Push(const T& val) {
  if (data_ == nullptr) {
    capacity_ = 8;
    data_ = new T[capacity_];
  } else if (size_ + 1 > capacity_) {
    auto buf = new T[capacity_ * 2];
    std::copy(data_, data_ + size_, buf);
    std::swap(data_, buf);
    delete[] buf;
    capacity_ *= 2;
  }
  data_[size_++] = val;
}

template<class T>
void StackArrT<T>::Pop() noexcept {
  if (size_ != 0) {
    size_--;
  }
}

template<class T>
bool StackArrT<T>::IsEmpty() const noexcept {
  return size_ == 0;
}

template<class T>
const T& StackArrT<T>::Top() const & {
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  } else {
    return data_[size_ - 1];
  }
}

template<class T>
T& StackArrT<T>::Top() & {
  if (size_ == 0) {
    throw std::out_of_range("Index out of range");
  } else {
    return data_[size_ - 1];
  }
}

template<class T>
void StackArrT<T>::Clear() noexcept {
  size_ = 0;
}

template<class T>
StackArrT<T>::~StackArrT() {
  delete[] data_;
  data_ = nullptr;
  capacity_ = 0;
}

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_StackArrTT_StackArrTT_HPP_
