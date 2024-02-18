//
// Created by Егор Федюнин on 12.02.2024.
//
#include "stacklst/stacklst.hpp"
#include <stdexcept>


StackLst::StackLst(const StackLst& lst) {
  if(lst.head_){
    head_ = new Node(lst.head_->v, lst.head_->prev);
    Node* prev = lst.head_->prev;
    while (prev != nullptr){
      Node* tmp = new Node(prev->v, prev->prev);
      prev = prev->prev;
    }
  }
}
StackLst::~StackLst() {
  if(head_ != nullptr){
    Node* cur = head_;
    Node* prev = head_->prev;
    while(cur != nullptr){
      delete cur;
      cur = prev;
      if(prev == nullptr){
        break;
      }
      prev = prev->prev;
    }
  }
}
StackLst& StackLst::operator=(const StackLst& lst) {
  if(this != &lst){
    Clear();
    if(lst.head_){
      head_ = new Node(lst.head_->v, lst.head_->prev);
      Node* prev = lst.head_->prev;
      while (prev != nullptr){
        Node* tmp = new Node(prev->v, prev->prev);
        prev = tmp->prev;
      }
    }
  }
}
void StackLst::Push(const Complex& val) {
  Node* new_head = new Node(val, head_);
  head_ = new_head;
}
void StackLst::Pop() noexcept {
  Node* head = head_;
  head_ = head->prev;
  delete head;
}
bool StackLst::IsEmpty() const noexcept {
  return head_ == nullptr;
}
const Complex& StackLst::Top() const {
  if(head_ == nullptr){
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
Complex& StackLst::Top() {
  if(head_ == nullptr){
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}
void StackLst::Clear() noexcept {
  if(head_ != nullptr){
    Node* cur = head_;
    Node* prev = head_->prev;
    while(cur != nullptr){
      delete cur;
      cur = prev;
      prev = prev->prev;
    }
  }
}
