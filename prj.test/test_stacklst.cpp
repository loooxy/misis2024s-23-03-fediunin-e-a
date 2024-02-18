//
// Created by Егор Федюнин on 12.02.2024.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <stacklst/stacklst.hpp>

TEST_CASE("Testing StackArr class") {
  SUBCASE("Testing methods"){
    StackLst arr;
    Complex val = {1,0};
    Complex val1 = {3,4};
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
    StackLst arr1{arr};
    CHECK(arr1.Top() == val1);
    arr.Pop();
    CHECK(arr.Top() == val);
    CHECK(arr1.Top() == val1);
  }
}

