//
// Created by Егор Федюнин on 05.02.2024.
//
#include "complex/complex.hpp"

class StackArr{
 public:
  StackArr();

  StackArr(const StackArr&);

  ~StackArr();

  StackArr& operator=(const StackArr&);

  void Push(const Complex&);
  void Pop() noexcept;
  bool IsEmpty() noexcept;
  const Complex& Top();
};