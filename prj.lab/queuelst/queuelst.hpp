//
// Created by Егор Федюнин on 19.02.2024.
//

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELST_QUEUELST_HPP_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELST_QUEUELST_HPP_

#include <complex/complex.hpp>

class QueueLst{
 public:
  [[nodiscard]] QueueLst() = default;

  [[nodiscard]] QueueLst(const QueueLst&);

  [[nodiscard]] QueueLst(QueueLst&&) noexcept;

  ~QueueLst();

  [[nodiscard]]QueueLst& operator=(const QueueLst&);

  [[nodiscard]]QueueLst& operator=(QueueLst&&) noexcept;

  void Push(const Complex& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const Complex& Top() const;

  [[nodiscard]] Complex& Top();

  void Clear() noexcept;
 private:
  struct Node{
    Node(Complex v, Node* ptr) : v{v}, next{ptr}{};
    Complex v = {0,0};
    Node* next = nullptr;
  };

  Node* tail_ = nullptr;
  Node* head_ = nullptr;
};


#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELST_QUEUELST_HPP_
