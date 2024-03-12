//
// Created by Егор Федюнин on 19.02.2024.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuelst/queuelst.hpp>

TEST_CASE("cons") {
  SUBCASE("default") {
    QueueLst a;

  }
  SUBCASE("copy") {
    QueueLst a;
    for (int i = 0; i < 500; ++i)
      a.Push(Complex(1, i));

    QueueLst b(a);

    CHECK(b.Top() == a.Top());

    b.Push(Complex());

    CHECK(b.Top() == a.Top());
  }
}

TEST_CASE("appr") {
  SUBCASE("appr with empty") {
    QueueLst a;
    QueueLst b;
    for (int i = 0; i < 5; ++i)
      b.Push(Complex(1, i));
    a = b;

    CHECK(b.Top() == a.Top());

    b.Push(Complex());
    CHECK(b.Top() == a.Top());
  }
  SUBCASE("appr with full") {
    QueueLst a;
    QueueLst b;
    for (int i = 0; i < 5; ++i) {
      a.Push(Complex(1, i));
      b.Push(Complex(i, 2));
    }
    a = b;
    CHECK(b.Top() == a.Top());
    b.Push(Complex());

    CHECK(b.Top() == a.Top());
  }
}

TEST_CASE("Push, Pop & Top") {
  QueueLst a;

  for (int i = 0; i < 1000; ++i) {
    a.Push(Complex(i, i));

    CHECK(a.Top() == Complex(0, 0));
  }

  for (int i = 1; i < 1000; ++i) {
    a.Pop();

    CHECK(a.Top() == Complex(i, i));
  }
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Pop();
}