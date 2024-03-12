//
// Created by Егор Федюнин on 12.02.2024.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <stacklst/stacklst.hpp>


TEST_CASE("appr") {
  SUBCASE("appr with empty") {
    StackLst a;
    StackLst b;
    for (int i = 0; i < 5; ++i)
      b.Push(Complex());
    a = b;

    b.Push(Complex());
  }
  SUBCASE("appr with full") {
    StackLst a;
    StackLst b;
    for (int i = 0; i < 5; ++i)
    {
      a.Push(Complex());
      b.Push(Complex());
    }
    a = b;

    b.Push(Complex());
  }
}

TEST_CASE("Push, Pop & Top"){
  StackLst a;
  for (int i = 0; i < 1000; ++i)
  {
    a.Push(Complex(i, i));
    CHECK(a.Top() == Complex(i, i));
  }

  for (int i = 998; i >= 0; --i)
  {
    a.Pop();
    CHECK(a.Top() == Complex(i, i));
  }
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Pop();
}