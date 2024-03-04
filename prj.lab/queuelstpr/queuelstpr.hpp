//
// Created by Егор Федюнин on 04.03.2024.
//
#pragma once
#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELSTPR_QUEUELSTPR_HPP_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELSTPR_QUEUELSTPR_HPP_


class QueueLstPr{
 public:
  [[nodiscard]] QueueLstPr() = default;

  [[nodiscard]] QueueLstPr(const QueueLstPr&);

  ~QueueLstPr();

  [[nodiscard]]QueueLstPr& operator=(const QueueLstPr&);

  void Push(const float& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const float& Top() const;

  [[nodiscard]] float& Top();

  void Clear() noexcept;
 private:
  struct Node{
    Node(float v, Node* ptr) : v{v}, next{ptr}{};
    float v = 0.0f;
    Node* next = nullptr;
  };

  Node* head_ = nullptr;
};


#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELSTPR_QUEUELSTPR_HPP_
