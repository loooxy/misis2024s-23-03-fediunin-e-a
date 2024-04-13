//
// Created by egorf on 14.04.2024.
//

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QueueLstTT_QueueLstTT_H_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QueueLstTT_QueueLstTT_H_

#include <complex/complex.hpp>
#include <stdexcept>

template<class T>
class QueueLstT{
 public:
  QueueLstT() = default;

  QueueLstT(const QueueLstT&);

  QueueLstT(QueueLstT&&) noexcept;

  ~QueueLstT();

  QueueLstT& operator=(const QueueLstT&);

  QueueLstT& operator=(QueueLstT&&) noexcept;

  void Push(const T& val);

  void Pop() noexcept;

  [[nodiscard]] bool IsEmpty() const noexcept;

  [[nodiscard]] const T& Top() const &;

  [[nodiscard]] T& Top() &;

  void Clear() noexcept;
 private:
  struct Node{
    Node(T v, Node* ptr) : v{v}, next{ptr}{};
    T v = {0,0};
    Node* next = nullptr;
  };

  Node* tail_ = nullptr;
  Node* head_ = nullptr;
};


template<class T>
QueueLstT<T>::QueueLstT(const QueueLstT<T>& lst) {
  if (lst.head_) {
    head_ = new Node(lst.head_->v, nullptr);
    Node* pl = head_;
    Node* pr = lst.head_;
    while (pr != nullptr) {
      pl->next = new Node(pr->next->v, nullptr);
      pr = pr->next;
      pl = pl->next;
    }
    tail_ = pl;
  }
}

template<class T>
QueueLstT<T>::~QueueLstT() {
  Clear();
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(const QueueLstT<T>& lst) {
  if (this != &lst) {
    if (lst.head_) {
      head_ = new Node(lst.head_->v, nullptr);
      Node* pl = head_;
      Node* pr = lst.head_;
      while (pr != nullptr) {
        pl->next = new Node(pr->next->v, nullptr);
        pr = pr->next;
        pl = pl->next;
      }
      tail_ = pl;
    }
  }
  return *this;
}

template<class T>
void QueueLstT<T>::Push(const T& val) {
  if (IsEmpty()) {
    tail_ = new Node{val, nullptr};
    head_ = tail_;
  } else {
    tail_->next = new Node{val, nullptr};
    tail_ = tail_->next;
  }
}

template<class T>
bool QueueLstT<T>::IsEmpty() const noexcept {
  return head_ == nullptr;
}

template<class T>
const T& QueueLstT<T>::Top() const &{
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}

template<class T>
T& QueueLstT<T>::Top() & {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}

template<class T>
void QueueLstT<T>::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T>
void QueueLstT<T>::Pop() noexcept {
  if (head_) {
    Node* deleted = head_;
    head_ = head_->next;
    delete deleted;
  }else{
    tail_ = nullptr;
  }
}

template<class T>
QueueLstT<T>::QueueLstT(QueueLstT<T>&& rhs) noexcept {
  std::swap(tail_, rhs.tail_);
  std::swap(head_, rhs.head_);
  rhs.tail_ = nullptr;
  rhs.head_ = nullptr;
}

template<class T>
QueueLstT<T>& QueueLstT<T>::operator=(QueueLstT<T>&& rhs) noexcept{
  if(this != &rhs) {
    std::swap(tail_, rhs.tail_);
    std::swap(head_, rhs.head_);
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;;
  }
  return *this;
}



#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QueueLstTT_QueueLstTT_H_
