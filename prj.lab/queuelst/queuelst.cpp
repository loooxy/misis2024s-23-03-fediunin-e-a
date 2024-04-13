//
// Created by Егор Федюнин on 19.02.2024.
//
#include "queuelst.hpp"
#include <stdexcept>

QueueLst::QueueLst(const QueueLst& lst) {
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
QueueLst::~QueueLst() {
  Clear();
}
QueueLst& QueueLst::operator=(const QueueLst& lst) {
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
void QueueLst::Push(const Complex& val) {
  if (IsEmpty()) {
    tail_ = new Node{val, nullptr};
    head_ = tail_;
  } else {
    tail_->next = new Node{val, nullptr};
    tail_ = tail_->next;
  }
}
bool QueueLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}
const Complex& QueueLst::Top() const &{
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
Complex& QueueLst::Top() & {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
void QueueLst::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}
void QueueLst::Pop() noexcept {
  if (head_) {
    Node* deleted = head_;
    head_ = head_->next;
    delete deleted;
  }else{
    tail_ = nullptr;
  }
}
QueueLst::QueueLst(QueueLst&& rhs) noexcept {
    std::swap(tail_, rhs.tail_);
    std::swap(head_, rhs.head_);
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;
}

QueueLst& QueueLst::operator=(QueueLst&& rhs) noexcept{
  if(this != &rhs) {
    std::swap(tail_, rhs.tail_);
    std::swap(head_, rhs.head_);
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;
    return *this;
  }
}

