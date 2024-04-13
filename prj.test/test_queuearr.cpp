//
// Created by egorf on 03.03.2024.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <queuearr/queuearr.hpp>

TEST_CASE("cons") {
  SUBCASE("default") {
    QueueArr a;
  }
  SUBCASE("copy") {
    QueueArr a;
    for (int i = 0; i < 500; ++i)
      a.Push(Complex(1, i));

    QueueArr b(a);
    CHECK(b.Top() == a.Top());

    b.Push(Complex());
    CHECK(b.Top() == a.Top());

    b.Pop();
    CHECK(b.Top() != a.Top());
  }
}

TEST_CASE("appr") {
  SUBCASE("appr with empty") {
    QueueArr a;
    QueueArr b;
    for (int i = 0; i < 5; ++i)
      b.Push(Complex(1, i));
    a = b;
    CHECK(b.Top() == a.Top());

    b.Push(Complex());
    CHECK(b.Top() == a.Top());
  }
  SUBCASE("appr with full") {
    QueueArr a;
    QueueArr b;
    for (int i = 0; i < 5; ++i)
    {
      a.Push(Complex(1, i));
      b.Push(Complex(i, 2));
    }
    a = b;
    CHECK(b.Top() == a.Top());
    b.Push(Complex());
    CHECK(b.Top() == a.Top());
  }
}

TEST_CASE("Push, Pop & Top"){
  QueueArr a;
  for (int i = 0; i < 1000; ++i)
  {
    a.Push(Complex(i, i));
    CHECK(a.Top() == Complex(0, 0));
  }

  for (int i = 1; i < 1000; ++i)
  {
    a.Pop();
    CHECK(a.Top() == Complex(i, i));
  }
  a.Pop();
  CHECK_THROWS(a.Top());
  a.Pop();
}

TEST_CASE("Run around") {
  QueueArr a;
  for (int i = 0; i < 9; ++i)
    a.Push(Complex(1, i));
  for (int i = 0; i < 5; ++i)
    a.Pop();
  for (int i = 0; i < 4; ++i)
    a.Push(Complex(1, i));

  QueueArr b(a);
  QueueArr c;
  c = a;

  while (!a.IsEmpty())
  {
    CHECK(a.Top() == b.Top());
    CHECK(b.Top() == c.Top());
    a.Pop();
    b.Pop();
    c.Pop();
  }
}