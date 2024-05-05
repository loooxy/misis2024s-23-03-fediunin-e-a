//
// Created by Егор Федюнин on 22.04.2024. fixx
//
#include "queuelstt//queuelstt.hpp"
#include <chrono>
#include <iostream>
#include <queue>
#include "complex/complex.hpp"

int main(){
  //Testing push() of 100 elements
  auto begin_ctor = std::chrono::steady_clock::now();
  QueueLstT<Complex>a{};
  for(int i = 0 ; i < 1000000; i++){
    a.Push(Complex(i));
  }
  auto end_ctor = std::chrono::steady_clock::now();
  auto ans = std::chrono::duration_cast<std::chrono::microseconds>(end_ctor - begin_ctor);
  std::cout << "queuelstt push mln" << " "  << ans.count() << '\n';
  begin_ctor = std::chrono::steady_clock::now();
  std::queue<Complex>b;
  for(int i = 0 ; i < 1000000; i++){
    b.push(Complex(i));
  }
  end_ctor = std::chrono::steady_clock::now();
  ans = std::chrono::duration_cast<std::chrono::microseconds>(end_ctor - begin_ctor);
  std::cout << "std::queue push 10000" << " " << ans.count() << "\n";
  //Testing pop() of 100 elements
  begin_ctor = std::chrono::steady_clock::now();
  for(int i = 0 ; i < 1000000; i++){
    a.Pop();
  }
  end_ctor = std::chrono::steady_clock::now();
  ans = std::chrono::duration_cast<std::chrono::microseconds>(end_ctor - begin_ctor);
  std::cout << "queuelstt pop 10000" << " "  << ans.count() << '\n';
  begin_ctor = std::chrono::steady_clock::now();
  for(int i = 0 ; i < 1000000; i++){
    b.pop();
  }
  end_ctor = std::chrono::steady_clock::now();
  ans = std::chrono::duration_cast<std::chrono::microseconds>(end_ctor - begin_ctor);
  std::cout << "std::queue pop 10000" << " " << ans.count() << "\n";
}