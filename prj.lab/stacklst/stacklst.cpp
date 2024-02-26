//
// Created by Егор Федюнин on 12.02.2024.
//
#include "stacklst/stacklst.hpp"
#include <stdexcept>

StackLst::StackLst(const StackLst& lst) {
  if (lst.head_) {
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
StackLst::~StackLst() {
  Clear();
}
StackLst& StackLst::operator=(const StackLst& lst) {
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
void StackLst::Push(const Complex& val) {
  Node* new_head = new Node(val, head_);
  head_ = new_head;
}
void StackLst::Pop() noexcept {
  if (head_ != nullptr) {
    Node* head = head_;
    head_ = head->next;
    delete head;
  }
}
bool StackLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}
const Complex& StackLst::Top() const {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
Complex& StackLst::Top() {
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
