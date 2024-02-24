//
// Created by Егор Федюнин on 19.02.2024.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <queuelst/queuelst.hpp>

TEST_CASE("Testing StackArr class") {
  SUBCASE("Testing methods"){
    QueueLst arr;
    Complex val = {1,0};
    Complex val1 = {3,4};
    arr.Push(val);
    CHECK(arr.Top() == val);
    arr.Push(val1);
    CHECK(arr.Top() == val);
    arr.Pop();
    CHECK(arr.Top() == val1);
    arr.Pop();
    CHECK(arr.IsEmpty());
    arr.Push(val);
    arr.Push(val1);
    QueueLst arr1{arr};
    CHECK(arr1.Top() == val);
    arr.Pop();
    CHECK(arr.Top() == val1);
    CHECK(arr1.Top() == val);
    arr.Clear();
    arr.Push(val1);
    arr.Push(val);
    QueueLst arr2 = arr;
    CHECK(arr2.Top() == val);
    arr.Pop();
    CHECK(arr2.Top() == val);
    CHECK(arr.Top() == val1);
  }
}

