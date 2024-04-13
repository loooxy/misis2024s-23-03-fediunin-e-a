//
// Created by Егор Федюнин on 12.02.2024.
//
#include "stacklst/stacklst.hpp"
#include <stdexcept>

StackLst::StackLst(StackLst&& rhs) noexcept {
  std::swap(head_, rhs.head_);
  rhs.head_ = nullptr;
}

StackLst::StackLst(const StackLst& lst) {
  if (lst.head_) {
    head_ = new Node(lst.head_->v, nullptr);
    Node* pl = head_;
    Node* pr = lst.head_->next;
    while (pr->next) {
      pl->next = new Node(pr->next->v, nullptr);
      pr = pr->next;
      pl = pl->next;
    }
  }
}
StackLst::~StackLst() {
  Clear();
}
StackLst& StackLst::operator=(const StackLst& lst) {
  if (this != &lst) {
    if (lst.IsEmpty()) {
      Clear();
    } else {
      Node* p_lst = lst.head_;
      if (IsEmpty()) {
        head_ = new Node{lst.head_->v, nullptr};
      } else {
        head_->v = lst.head_->v;
      }
      Node* p_dst = head_;
      while (p_lst->next) {
        if (p_dst->next) {
          p_dst->next->v = p_lst->next->v;
        } else {
          p_dst->next = new Node{ p_lst->next->v, nullptr };
        }
        p_lst = p_lst->next;
        p_dst = p_dst->next;
      }
      if (p_dst->next) {
        Node* tail = p_dst->next->next;
        while (p_dst->next) {
          delete p_dst->next;
          p_dst->next = nullptr;
          p_dst = tail;
        }
      }
    }
  }
  return *this;
}

StackLst& StackLst::operator=(StackLst&& lst) noexcept{
  std::swap(head_, lst.head_);
  lst.head_ = nullptr;
  return *this;
}

void StackLst::Push(const Complex& val) {
  head_ = new Node(val, head_);
}
void StackLst::Pop() noexcept {
  if (head_ != nullptr) {
    Node* head = head_;
    head_ = head_->next;
    delete head;
  }
}
bool StackLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}
const Complex& StackLst::Top() const & {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
Complex& StackLst::Top() & {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
void StackLst::Clear() noexcept {
  while (head_ != nullptr) {
    Pop();
  }
}
