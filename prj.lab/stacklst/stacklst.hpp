//
// Created by Егор Федюнин on 12.02.2024.
//

#pragma once
#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_STACKLST_STACKLST_HPP_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_STACKLST_STACKLST_HPP_

#include <complex/complex.hpp>

class StackLst{
 public:
  StackLst() = default;

  StackLst(const StackLst&);

  StackLst(StackLst&&) noexcept;

  ~StackLst();

  [[nodiscard]] StackLst& operator=(const StackLst&);

  [[nodiscard]] StackLst& operator=(StackLst&&) noexcept;

  void Push(const Complex& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const Complex& Top() const;

  [[nodiscard]] Complex& Top();

  void Clear() noexcept;

 private:
  struct Node{
    Node(Complex v, Node* ptr) : v{v}, next{ptr}{};
    Complex v;
    Node* next = nullptr;
  };

  Node* head_ = nullptr;
};

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_STACKLST_STACKLST_HPP_
