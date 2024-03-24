//
// Created by Егор Федюнин on 19.02.2024.
//
#include "queuelst.hpp"
#include <stdexcept>

QueueLst::QueueLst(const QueueLst& lst) {
  if (lst.head_) {
    head_ = new Node(lst.head_->v, nullptr);
    Node* pl = head_;
    Node* pr = lst.head_->next;
    while (pr != nullptr) {
      pl->next = new Node(pr->v, nullptr);
      pr = pr->next;
      pl = pl->next;
    }
  }
}
QueueLst::~QueueLst() {
  Clear();
}
QueueLst& QueueLst::operator=(const QueueLst& lst) {
  if (this != &lst) {
    if (lst.head_) {
      Clear();
      head_ = new Node(lst.head_->v, nullptr);
      Node* pl = head_->next;
      Node* pr = lst.head_->next;
      while (pr != nullptr) {
        pl = new Node(pr->v, nullptr);
        pr = pr->next;
        pl = pl->next;
      }
    }
  }
  return *this;
}
void QueueLst::Push(const Complex& val) {
  if (head_) {
    Node* cur = head_;
    while (cur->next != nullptr) {
      cur = cur->next;
    }
    cur->next = new Node(val, nullptr);
  } else {
    head_ = new Node(val, nullptr);
  }
}
bool QueueLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}
const Complex& QueueLst::Top() const {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
Complex& QueueLst::Top() {
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
    Node* cur = head_->next;
    delete head_;
    head_ = cur;
  }
}
QueueLst::QueueLst(QueueLst&& rhs) noexcept {
    std::swap(tail_, rhs.tail_);
    std::swap(head_, rhs.head_);
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;
}

QueueLst& QueueLst::operator=(QueueLst&& rhs) noexcept{
    std::swap(tail_, rhs.tail_);
    std::swap(head_, rhs.head_);
    rhs.tail_ = nullptr;
    rhs.head_ = nullptr;
}

