//
// Created by egorf on 14.04.2024.
//

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QueueArrT_QueueArrT_H_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QueueArrT_QueueArrT_H_

#include <complex/complex.hpp>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

template<class T>
class QueueArrT {
 public:
  QueueArrT() = default;

  QueueArrT(const QueueArrT&);

  QueueArrT(QueueArrT&& src) noexcept ;

  ~QueueArrT();

  QueueArrT& operator=(const QueueArrT&);

  QueueArrT& operator=(QueueArrT&& rhs) noexcept ;

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Pop() noexcept;

  void Push(const T& val);

  [[nodiscard]] T& Top();

  [[nodiscard]] const T& Top() const;

  void Clear() noexcept;


 private:
  std::ptrdiff_t size_ = 0;
  T* data_ = nullptr;
  std::ptrdiff_t head_ = -1;
  std::ptrdiff_t tail_ = -1;
  std::ptrdiff_t Count() const;
};

//
// Created by egorf on 03.03.2024.
//

template<class T>
std::ptrdiff_t QueueArrT<T>::Count() const {
  return IsEmpty() ? 0 : (tail_ + size_ - head_) % size_ + 1;
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(const QueueArrT<T>& src) {
  if (this != &src) {
    std::ptrdiff_t count = src.Count();
    if (0 == count) {
      head_ = -1;
    } else {
      if (size_ < count) {
        size_ = (count + 4) / 4 * 4;
        delete[] data_;
        data_ = new T[size_];
      }
      if (src.head_ < src.tail_) {
        std::copy(src.data_ + src.head_, src.data_ + src.tail_ + 1, data_);
      }
      else {
        std::copy(src.data_ + src.head_, src.data_ + src.size_, data_);
        std::copy(src.data_, src.data_ + src.tail_ + 1, data_ + src.size_ - src.head_);
      }
      head_ = 0;
      tail_ = count - 1;
    }
  }
  return *this;
}

template<class T>
QueueArrT<T>::QueueArrT(const QueueArrT<T>& src) {
  if (!src.IsEmpty()) {
    std::ptrdiff_t count = src.Count();
    head_ = 0;
    tail_ = count - 1;
    size_ = (count + 4) / 4 * 4;
    data_ = new T[size_];
    if (src.head_ < src.tail_) {
      std::copy(src.data_ + src.head_, src.data_ + src.tail_ + 1, data_);
    } else {
      std::copy(src.data_ + src.head_, src.data_ + src.size_, data_);
      std::copy(src.data_, src.data_ + src.tail_ + 1, data_ + src.size_ - src.head_);
    }
  }
}

template<class T>
QueueArrT<T>::QueueArrT(QueueArrT<T>&& src) noexcept {
  std::swap(size_, src.size_);
  std::swap(data_, src.data_);
  std::swap(head_, src.head_);
  std::swap(tail_, src.tail_);
}

template<class T>
QueueArrT<T>& QueueArrT<T>::operator=(QueueArrT<T>&& src) noexcept {
  if (this != &src) {
    std::swap(size_, src.size_);
    std::swap(data_, src.data_);
    std::swap(head_, src.head_);
    std::swap(tail_, src.tail_);
  }
  return *this;
}

template<class T>
QueueArrT<T>::~QueueArrT() {
  delete[] data_;
}

template<class T>
bool QueueArrT<T>::IsEmpty() const noexcept {
  return head_ < 0;
}

template<class T>
void QueueArrT<T>::Pop() noexcept {
  if (!IsEmpty()) {
    if (head_ != tail_) {
      head_ = (head_ + 1) % size_;
    } else {
      head_ = -1;
    }
  }
}

template<class T>
void QueueArrT<T>::Push(const T& val) {
  if (nullptr == data_) {
    size_ = 2;
    data_ = new T[size_];
  }
  if (IsEmpty()) {
    head_ = 0;
    tail_ = 0;
  } else {
    if (head_ == (tail_ + 1) % size_) {
      // resize
      T* buf = new T[size_ * 2];
      std::swap(buf, data_);
      if (head_ < tail_) {
        std::copy(buf + head_, buf + tail_ + 1, data_);
      } else {
        std::copy(buf + head_, buf + size_, data_);
        std::copy(buf, buf + tail_ + 1, data_ + tail_ - head_);
      }
      delete[] buf;
      size_ *= 2;
      tail_ = Count();
    } else {
      tail_ = (tail_ + 1) % size_;
    }
  }
  data_[tail_] = val;
}

template<class T>
T& QueueArrT<T>::Top() {
  if (IsEmpty()) {
    throw std::logic_error("QueueArrT - try get top form empty queue.");
  }
  return data_[head_];
}

template<class T>
const T& QueueArrT<T>::Top() const {
  if (IsEmpty()) {
    throw std::logic_error("QueueArrT - try get top form empty queue.");
  }
  return data_[head_];
}

template<class T>
void QueueArrT<T>::Clear() noexcept {
  head_ = -1;
}


#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QueueArrTT_QueueArrTT_H_
