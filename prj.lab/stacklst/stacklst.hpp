//
// Created by Егор Федюнин on 12.02.2024.
//

#pragma once
#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_STACKLST_STACKLST_HPP_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_STACKLST_STACKLST_HPP_

#include <complex/complex.hpp>

class StackLst{
 public:
  [[nodiscard]] StackLst() = default;

  [[nodiscard]] StackLst(const StackLst&);

  ~StackLst();

  [[nodiscard]]StackLst& operator=(const StackLst&);

  void Push(const Complex& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const Complex& Top() const;

  [[nodiscard]] Complex& Top();

  void Clear() noexcept;
 private:
  struct Node{
    Node(Complex v, Node* ptr) : v{v}, prev{ptr}{};
    Complex v = {0,0};
    Node* prev = nullptr;
  };

  Node* head_ = nullptr;
};

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_STACKLST_STACKLST_HPP_
