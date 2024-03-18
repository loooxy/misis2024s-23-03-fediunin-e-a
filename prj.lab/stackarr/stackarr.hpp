//
// Created by Егор Федюнин on 05.02.2024.
//

#pragma once
#ifndef MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_STACKARR_HPP_
#define MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_STACKARR_HPP_

#include "complex/complex.hpp"

class StackArr {
 public:
  [[nodiscard]] StackArr() = default;

  [[nodiscard]] StackArr(const StackArr&);

  [[nodiscard]] StackArr(StackArr&&) noexcept;

  ~StackArr();

  [[nodiscard]]StackArr& operator=(const StackArr&);

  [[nodiscard]]StackArr& operator=(StackArr&&) noexcept;

  void Push(const Complex& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const Complex& Top() const;

  [[nodiscard]] Complex& Top();

  void Clear() noexcept;

 private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  Complex* data_ = nullptr;
};

#endif //MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_STACKARR_HPP_