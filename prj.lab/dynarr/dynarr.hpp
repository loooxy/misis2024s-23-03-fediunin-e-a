//
// Created by egorf on 10.12.2023.
//

#ifndef DYNARR_H
#define DYNARR_H

#include <cstddef>

class DynArr {
 public:
  DynArr() = default;
  DynArr(const DynArr& rhs);
  DynArr(DynArr&& rhs) noexcept;
  [[nodiscard]]DynArr(const std::ptrdiff_t size);
  ~DynArr();
  DynArr& operator=(const DynArr& dynarr);
  DynArr& operator=(DynArr&& dynarr) noexcept;

  [[nodiscard]]std::ptrdiff_t Size() const noexcept { return size_; }
  [[nodiscard]]std::ptrdiff_t Capacity() const noexcept { return capacity_; }
  void Resize(const std::ptrdiff_t size);
  [[nodiscard]]float& operator[](const std::ptrdiff_t idx);
  [[nodiscard]]const float& operator[](const std::ptrdiff_t idx) const;
 private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  float* data_ = nullptr;
};

#endif //DYNARR_H
