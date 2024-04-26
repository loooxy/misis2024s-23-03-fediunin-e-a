//
// Created by Егор Федюнин on 08.04.2024.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "generate.hpp"
#include <stackarrt/stackarrt.hpp>
#include <complex/complex.hpp>
#include <vector>


TEST_CASE_TEMPLATE("bar", T, int, char, long long, double) {
  SUBCASE("Testing StackArrT class") {
    SUBCASE("Testing methods") {
      StackArrT<T> arr;
      std::vector<T>data;
      int n = 10;
      FillData(n, data);
      for(int i = 0; i < n; i++){
        arr.Push(data[i]);
      }
      for(int i = n-1; i >= 0; i--){
        CHECK(data[i] == arr.Top());
        arr.Pop();
      }
    }
  }
}

