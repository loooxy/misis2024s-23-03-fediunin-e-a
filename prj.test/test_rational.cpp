//
// Created by Егор Федюнин on 05.12.2023.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <rational/rational.hpp>

TEST_CASE("Testing Rational class") {
  SUBCASE("Testing default constructor") {
    Rational r;
    CHECK(r.num() == 0);
    CHECK(r.den() == 1);
  }

  SUBCASE("Testing constructor with numerator and denominator") {
    Rational r(3, 4);
    CHECK(r.num() == 3);
    CHECK(r.den() == 4);
    Rational r1(-1, -1);
    CHECK(r1.num() == 1);
    CHECK(r1.den() == 1);
    Rational r2{4, 2};
    CHECK(r2.num() == 2);
    CHECK(r2.den() == 1);
  }

  SUBCASE("Testing operator==") {
    Rational r1(3, 4);
    Rational r2(3, 4);
    CHECK(r1 == r2);
  }

  SUBCASE("Testing operator!=") {
    Rational r1(3, 4);
    Rational r2(2, 3);
    CHECK(r1 != r2);
  }

  SUBCASE("Testing comparison operators") {
    Rational r1(3, 4);
    Rational r2(2, 3);
    Rational r3(3, 4);
    CHECK((r1 > r2) == true);
    CHECK((r2 < r1) == true);
    CHECK((r3 >= r1) == true);
    CHECK((r3 <= r1) == true);
  }

  SUBCASE("Testing operator+") { // Realized using operator+=
    Rational r1(3, 4);
    Rational r2(2, 3);
    Rational r3 = r1 + r2;
    CHECK(r3.num() == 17);
    CHECK(r3.den() == 12);
  }

  SUBCASE("Testing operator-") { // Realized using operator-=
    Rational r1(3, 4);
    Rational r2(2, 3);
    Rational r3 = r1 - r2;
    CHECK(r3.num() == 1);
    CHECK(r3.den() == 12);
  }

  SUBCASE("Testing operator*") { // Realized using operator*=
    Rational r1(3, 4);
    Rational r2(2, 3);
    Rational r3 = r1 * r2;
    CHECK(r3.num() == 1);
    CHECK(r3.den() == 2);
  }

  SUBCASE("Testing operator/") { // Realized using operator+=
    Rational r1(3, 4);
    Rational r2(2, 3);
    Rational r4(0);
    Rational r3 = r1 / r2;
    CHECK(r3.num() == 9);
    CHECK(r3.den() == 8);
    CHECK_THROWS(r1 / r4);
  }

  SUBCASE("Testing operator-") { // Realized using operator+=
    Rational r1(3, 4);
    r1 = -r1;
    CHECK(r1.num() == -3);
    CHECK(r1.den() == 4);
  }

}