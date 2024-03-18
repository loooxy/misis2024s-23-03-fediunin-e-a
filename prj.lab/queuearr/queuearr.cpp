//
// Created by egorf on 03.03.2024.
//
#include <stdexcept>
#include <queuearr/queuearr.hpp>
#include <algorithm>

QueueArr::QueueArr() {
  mass_ = new Complex[capacity_];
}

QueueArr::QueueArr(const QueueArr& other) {
  capacity_ = other.capacity_;
  begin = 0;
  end = other.Size();
  mass_ = new Complex[capacity_];

  if (other.begin < other.end)
    std::copy(other.mass_ + other.begin, other.mass_ + other.end, mass_);
  if (other.begin > other.end)
  {
    std::copy(other.mass_ + other.begin, other.mass_ + other.capacity_, mass_);
    std::copy(other.mass_, other.mass_ + other.end, mass_ + (other.capacity_ - other.begin));
  }
}

QueueArr::~QueueArr() {
  delete[] mass_;
}

QueueArr& QueueArr::operator=(const QueueArr& rhs) {
  if (rhs.capacity_ > capacity_)
  {
    delete[] mass_;
    capacity_ = rhs.capacity_;
    begin = 0;
    end = rhs.Size();
    mass_ = new Complex[capacity_];

    if (rhs.begin < rhs.end)
      std::copy(rhs.mass_ + rhs.begin, rhs.mass_ + rhs.end, mass_);
    if (rhs.begin > rhs.end)
    {
      std::copy(rhs.mass_ + rhs.begin, rhs.mass_ + rhs.capacity_, mass_);
      std::copy(rhs.mass_, rhs.mass_ + rhs.end, mass_ + (rhs.capacity_ - rhs.begin));
    }
  }
  else {
    begin = 0;
    end = rhs.Size();

    if (rhs.begin < rhs.end)
      std::copy(rhs.mass_ + rhs.begin, rhs.mass_ + rhs.end, mass_);
    if (rhs.begin > rhs.end)
    {
      std::copy(rhs.mass_ + rhs.begin, rhs.mass_ + rhs.capacity_, mass_);
      std::copy(rhs.mass_, rhs.mass_ + rhs.end, mass_ + (rhs.capacity_ - rhs.begin));
    }
  }

  return *this;
}

bool QueueArr::IsEmpty() const noexcept {
  return Size() == 0;
}

void QueueArr::Pop() noexcept {
  if (!IsEmpty())
  {
    begin++;
    if (capacity_ == begin)
      begin = 0;
  }
}

void QueueArr::Push(const Complex& val) {
  if (Size() == capacity_) {
    int new_capacity_ = 2 * capacity_;
    Complex* new_mass_ = new Complex[new_capacity_];
    int new_begin = 0;
    int new_end = Size();

    if (begin < end)
      std::copy(mass_ + begin, mass_ + end, new_mass_);
    if (begin > end)
    {
      std::copy(mass_ + begin, mass_ + capacity_, new_mass_);
      std::copy(mass_, mass_ + end, new_mass_ + (capacity_ - begin));
    }

    begin = new_begin;
    end = new_end;
    capacity_ = new_capacity_;
    delete[] mass_;
    mass_ = new_mass_;
  }

  if (end == capacity_)
  {
    end = 1;
    mass_[0] = val;
  }
  else
  {
    mass_[end] = val;
    end++;
  }
}

Complex& QueueArr::Top() {
  if (IsEmpty())
    throw std::out_of_range("Queue is empty");
  else
    return mass_[begin];
}

const Complex& QueueArr::Top() const {
  if (IsEmpty())
    throw std::out_of_range("Queue is empty");
  else
    return mass_[begin];
}

void QueueArr::Clear() noexcept {
  begin = 0;
  end = 0;
  capacity_ = 10;
  delete[] mass_;
  mass_ = new Complex[capacity_];
}
QueueArr::QueueArr(QueueArr&& rhs) noexcept {
  std::swap(*this, rhs);
  rhs.mass_ = nullptr;
}
QueueArr& QueueArr::operator=(QueueArr&& rhs) {
  std::swap(*this, rhs);
  rhs.mass_ = nullptr;
}
