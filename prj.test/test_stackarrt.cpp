//
// Created by Егор Федюнин on 08.04.2024.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <stackarrt/stackarrt.hpp>
#include <complex/complex.hpp>

template <typename T, T Value>
struct value_as_type {
  static constexpr const T value = Value;
};

TEST_CASE_TEMPLATE("bar", T, int, char, long long, double) {
  SUBCASE("Testing StackArrT class") {
    SUBCASE("Testing methods") {
      StackArrT<T> arr;
      T val = 123;
      T val1 = 123;
      arr.Push(val);
      CHECK(arr.Top() == val);
      arr.Push(val1);
      CHECK(arr.Top() == val1);
      arr.Pop();
      CHECK(arr.Top() == val);
      arr.Pop();
      CHECK(arr.IsEmpty());
      arr.Push(val);
      arr.Push(val1);
      StackArrT arr1{arr};
      CHECK(arr1.Top() == val1);
      arr.Pop();
      CHECK(arr.Top() == val);
      CHECK(arr1.Top() == val1);
      StackArrT arr2 = arr1;
      CHECK(arr2.Top() == val1);
      arr1.Pop();
      CHECK(arr2.Top() == val1);
      CHECK(arr1.Top() == val);
    }
  }
}

