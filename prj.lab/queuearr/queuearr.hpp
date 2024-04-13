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
  QueueArr() = default;

  QueueArr(const QueueArr&);

  QueueArr(QueueArr&& rhs) noexcept ;

  ~QueueArr();

  QueueArr& operator=(const QueueArr&);

  QueueArr& operator=(QueueArr&& rhs) noexcept ;

  [[nodiscard]] bool IsEmpty() const noexcept;

  void Pop() noexcept;

  void Push(const Complex& val);

  [[nodiscard]] Complex& Top();

  [[nodiscard]] const Complex& Top() const;

  void Clear() noexcept;


 private:
  std::ptrdiff_t size_ = 0;
  Complex* data_ = nullptr;
  std::ptrdiff_t head_ = -1;
  std::ptrdiff_t tail_ = -1;
  std::ptrdiff_t Count() const;
};

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUEARR_QUEUEARR_H_
