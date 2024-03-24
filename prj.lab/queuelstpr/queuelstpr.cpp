//
// Created by Егор Федюнин on 04.03.2024.
//

#include "queuelstpr.hpp"
#include <stdexcept>

QueueLstPr::QueueLstPr(const QueueLstPr &lst) {
  if (lst.head_) {
    head_ = new Node(lst.head_->v, nullptr);
    Node *pl = head_->next;
    Node *pr = lst.head_->next;
    while (pr != nullptr) {
      pl = new Node(pr->v, nullptr);
      pr = pr->next;
      pl = pl->next;
    }
  }
}

QueueLstPr::~QueueLstPr() {
  Clear();
}

QueueLstPr &QueueLstPr::operator=(const QueueLstPr &lst) {
  if (this != &lst) {
    if (lst.head_) {
      Clear();
      head_ = new Node(lst.head_->v, nullptr);
      Node *pl = head_->next;
      Node *pr = lst.head_->next;
      while (pr != nullptr) {
        pl = new Node(pr->v, nullptr);
        pr = pr->next;
        pl = pl->next;
      }
    }
  }
  return *this;
}

void QueueLstPr::Push(const float &val) {
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

bool QueueLstPr::IsEmpty() const noexcept {
  return head_ == nullptr;
}

const float &QueueLstPr::Top() const {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}

float &QueueLstPr::Top() {
  if (head_ == nullptr) {
    throw std::out_of_range("Index out of range");
  }
  return head_->v;
}

void QueueLstPr::Clear() noexcept {
  while (!IsEmpty()) {
    Pop();
  }
}

void QueueLstPr::Pop() noexcept {
  if (head_) {
    Node *cur = head_->next;
    delete head_;
    head_ = cur;
  }
}

QueueLstPr::QueueLstPr(QueueLstPr &&rhs) noexcept {
  std::swap(head_, rhs.head_);
  rhs.head_ = nullptr;
}

QueueLstPr &QueueLstPr::operator=(QueueLstPr &&rhs) noexcept {
  std::swap(head_, rhs.head_);
  rhs.head_ = nullptr;
}

