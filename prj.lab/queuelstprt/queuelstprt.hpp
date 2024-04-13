//
// Created by egorf on 14.04.2024.
//

#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELSTPRT_QUEUELSTPRT_H_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELSTPRT_QUEUELSTPRT_H_

#include <complex/complex.hpp>
#include <stdexcept>

template<class T>
class QueueLstPrT{
 public:
  QueueLstPrT() = default;

  QueueLstPrT(const QueueLstPrT&);

  QueueLstPrT(QueueLstPrT&&) noexcept;

  ~QueueLstPrT();

  QueueLstPrT& operator=(const QueueLstPrT&);

  QueueLstPrT& operator=(QueueLstPrT&&) noexcept;

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
QueueLstPrT<T>::QueueLstPrT(const QueueLstPrT<T>& lst) {
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
QueueLstPrT<T>::~QueueLstPrT() {
  Clear();
}

template<class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(const QueueLstPrT<T>& lst) {
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
void QueueLstPrT<T>::Push(const T &val) {
  if (head_) {
    bool flag = false;
    Node *cur = head_;
    if (val <= head_->v) {
      Node *tmp = new Node(val, head_);
      head_ = tmp;
    } else {
      while (cur->next != nullptr) {
        if (val <= cur->next->v) {
          Node *tmp = new Node(val, cur->next);
          cur->next = tmp;
          flag = true;
          break;
        }
        cur = cur->next;
      }
      if (!flag)cur->next = new Node(val, nullptr);
    }
  } else {
    head_ = new Node(val, nullptr);
  }
}

template<class T>
bool QueueLstPrT<T>::IsEmpty() const noexcept {
  return head_ == nullptr;
}

template<class T>
const T& QueueLstPrT<T>::Top() const &{
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}

template<class T>
T& QueueLstPrT<T>::Top() & {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}

template<class T>
void QueueLstPrT<T>::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

template<class T>
void QueueLstPrT<T>::Pop() noexcept {
  if (head_) {
    Node* deleted = head_;
    head_ = head_->next;
    delete deleted;
  }else{
    tail_ = nullptr;
  }
}

template<class T>
QueueLstPrT<T>::QueueLstPrT(QueueLstPrT<T>&& rhs) noexcept {
  std::swap(tail_, rhs.tail_);
  std::swap(head_, rhs.head_);
  rhs.tail_ = nullptr;
  rhs.head_ = nullptr;
}

template<class T>
QueueLstPrT<T>& QueueLstPrT<T>::operator=(QueueLstPrT<T>&& rhs) noexcept{
  if(this != &rhs) {
    std::swap(tail_, rhs.tail_);
    std::swap(head_, rhs.head_);
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;;
  }
  return *this;
}





#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_LAB_QUEUELSTPRT_QUEUELSTPRT_H_
