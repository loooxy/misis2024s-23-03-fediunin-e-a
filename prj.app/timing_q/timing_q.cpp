//
// Created by Егор Федюнин on 22.04.2024. fixx
//
#include "queuelstt//queuelstt.hpp"
#include <chrono>
#include <iostream>
#include <queue>
#include <functional>
#include "complex/complex.hpp"

template <typename Func, typename... Args>
auto measureTime(Func func, Args... args) {
  auto start = std::chrono::steady_clock::now();
  func(std::forward<Args>(args)...);
  auto end = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

int main() {
  //Testing push() of 100 elements
  auto begin_ctor = std::chrono::steady_clock::now();
  QueueLstT<int> a{};
  for (int i = 0; i < 1000000; i++) {
    a.Push(i);
  }
  auto end_ctor = std::chrono::steady_clock::now();
  auto ans = std::chrono::duration_cast<std::chrono::microseconds>(end_ctor - begin_ctor);
  std::cout << "queuelstt push mln" << " " << ans.count() << '\n';

  QueueLstT<int> b{};
  auto time = measureTime([&]() {
      for(int i = 0 ; i < 1000000; i++){
        b.Push(i);
      }
  });
  std::cout << "Time taken: " << time << " microseconds\n";
}