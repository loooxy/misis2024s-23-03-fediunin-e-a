//
// Created by egorf on 03.03.2024.
//

#pragma once

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUEARR_QUEUEARR_H_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUEARR_QUEUEARR_H_

#include <complex/complex.hpp>
#include <cstddef>

class QueueArr {
 public:
  QueueArr();

  QueueArr(const QueueArr&);

  QueueArr(QueueArr&& rhs) noexcept ;

  ~QueueArr();

  [[nodiscard]] QueueArr& operator=(const QueueArr&);

  [[nodiscard]] QueueArr& operator=(QueueArr&& rhs);

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Pop() noexcept;

  void Push(const Complex& val);

  [[nodiscard]] Complex& Top();

  [[nodiscard]] const Complex& Top() const;

  void Clear() noexcept;

  int Size() const {
    if (begin <= end)
      return end - begin;
    else
      return capacity_ - begin + end;
  }

 private:
  std::ptrdiff_t begin = 0;
  std::ptrdiff_t end = 0;
  std::ptrdiff_t capacity_ = 10;
  Complex* data_ = nullptr;
};

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUEARR_QUEUEARR_H_
