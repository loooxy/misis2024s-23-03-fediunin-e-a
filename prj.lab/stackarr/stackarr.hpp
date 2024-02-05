//
// Created by Егор Федюнин on 05.02.2024.
//

#ifndef MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_STACKARR_HPP_
#define MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_STACKARR_HPP_

#include "complex/complex.hpp"

class StackArr{
 public:
  StackArr() = default;

  StackArr(const StackArr&);

  ~StackArr();

  StackArr& operator=(const StackArr&);

  void Push(const Complex&);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  const Complex& Top();

 private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  Complex* data_ = nullptr;
};

#endif //MISIS2024S_23_03_FEDIUNIN_E_A_PRJ_LAB_STACK_STACKARR_HPP_
