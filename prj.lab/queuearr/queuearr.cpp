//
// Created by egorf on 03.03.2024.
//
#include <stdexcept>
#include <queuearr/queuearr.hpp>
#include <algorithm>

QueueArr::QueueArr() {
    data_ = new Complex[capacity_];
}

QueueArr::QueueArr(const QueueArr &other) {
    capacity_ = other.capacity_;
    begin = 0;
    end = other.Size();
    data_ = new Complex[capacity_];

    if (other.begin < other.end)
        std::copy(other.data_ + other.begin, other.data_ + other.end, data_);
    if (other.begin > other.end) {
        std::copy(other.data_ + other.begin, other.data_ + other.capacity_, data_);
        std::copy(other.data_, other.data_ + other.end, data_ + (other.capacity_ - other.begin));
    }
}

QueueArr::~QueueArr() {
    delete[] data_;
}

QueueArr &QueueArr::operator=(const QueueArr &rhs) {
    if (rhs.capacity_ > capacity_) {
        delete[] data_;
        capacity_ = rhs.capacity_;
        begin = 0;
        end = rhs.Size();
        data_ = new Complex[capacity_];

        if (rhs.begin < rhs.end)
            std::copy(rhs.data_ + rhs.begin, rhs.data_ + rhs.end, data_);
        if (rhs.begin > rhs.end) {
            std::copy(rhs.data_ + rhs.begin, rhs.data_ + rhs.capacity_, data_);
            std::copy(rhs.data_, rhs.data_ + rhs.end, data_ + (rhs.capacity_ - rhs.begin));
        }
    } else {
        begin = 0;
        end = rhs.Size();

        if (rhs.begin < rhs.end)
            std::copy(rhs.data_ + rhs.begin, rhs.data_ + rhs.end, data_);
        if (rhs.begin > rhs.end) {
            std::copy(rhs.data_ + rhs.begin, rhs.data_ + rhs.capacity_, data_);
            std::copy(rhs.data_, rhs.data_ + rhs.end, data_ + (rhs.capacity_ - rhs.begin));
        }
    }

    return *this;
}

bool QueueArr::IsEmpty() const noexcept {
    return Size() == 0;
}

void QueueArr::Pop() noexcept {
    if (!IsEmpty()) {
        begin++;
        if (capacity_ == begin)
            begin = 0;
    }
}

void QueueArr::Push(const Complex &val) {
    if (Size() == capacity_) {
        int new_capacity_ = 2 * capacity_;
        Complex *new_data_ = new Complex[new_capacity_];
        int new_begin = 0;
        int new_end = Size();

        if (begin < end)
            std::copy(data_ + begin, data_ + end, new_data_);
        if (begin > end) {
            std::copy(data_ + begin, data_ + capacity_, new_data_);
            std::copy(data_, data_ + end, new_data_ + (capacity_ - begin));
        }

        begin = new_begin;
        end = new_end;
        capacity_ = new_capacity_;
        delete[] data_;
        data_ = new_data_;
    }

    if (end == capacity_) {
        end = 1;
        data_[0] = val;
    } else {
        data_[end] = val;
        end++;
    }
}

Complex &QueueArr::Top() {
    if (IsEmpty())
        throw std::out_of_range("Queue is empty");
    else
        return data_[begin];
}

const Complex &QueueArr::Top() const {
    if (IsEmpty())
        throw std::out_of_range("Queue is empty");
    else
        return data_[begin];
}

void QueueArr::Clear() noexcept {
    begin = 0;
    end = 0;
    capacity_ = 10;
    delete[] data_;
    data_ = new Complex[capacity_];
}

QueueArr::QueueArr(QueueArr &&rhs) noexcept {
    std::swap(begin, rhs.begin);
    std::swap(end, rhs.end);
    std::swap(data_, rhs.data_);
    std::swap(capacity_, rhs.capacity_);
    rhs.data_ = nullptr;
}

QueueArr &QueueArr::operator=(QueueArr &&rhs) {
    std::swap(begin, rhs.begin);
    std::swap(end, rhs.end);
    std::swap(data_, rhs.data_);
    std::swap(capacity_, rhs.capacity_);
    rhs.data_ = nullptr;
    return *this;
}
