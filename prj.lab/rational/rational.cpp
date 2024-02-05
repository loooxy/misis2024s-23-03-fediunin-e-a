//
// Created by Егор Федюнин on 04.12.2023.
//
//
// Created by Егор Федюнин on 22.11.2023.
//
#include "rational/rational.hpp"
#include <iostream>
#include <stdexcept>

Rational& Rational::gcd() {
  int64_t a = abs(num_), b = abs(den_);
  if (a < b) {
    std::swap(a, b);
  }
  if (b == 0) {
    num_ = 0, den_ = 1;
    return *this;
  };
  while (a % b != 0) {
    a = a % b;
    std::swap(a, b);
  }
  num_ /= b;
  den_ /= b;
  return *this;
}

bool Rational::operator<(const Rational& rhs) const noexcept {
  return (num_ * rhs.den_ < rhs.num_ * den_);
}
bool Rational::operator<=(const Rational& rhs) const noexcept {
  return (num_ * rhs.den_ <= rhs.num_ * den_);
}
bool Rational::operator>(const Rational& rhs) const noexcept {
  return (num_ * rhs.den_ > rhs.num_ * den_);
}
bool Rational::operator>=(const Rational& rhs) const noexcept {
  return (num_ * rhs.den_ >= rhs.num_ * den_);
}

Rational& Rational::operator+=(const Rational& lhs) {
  num_ *= lhs.den_;
  num_ += lhs.num_ * den_;
  den_ *= lhs.den_;
  return gcd();
};
Rational& Rational::operator+=(const int64_t var) {
  Rational tmp{var};
  *this += tmp;
  return *this;
}
Rational& Rational::operator-=(const Rational& lhs) {
  num_ *= lhs.den_;
  num_ -= lhs.num_ * den_;
  den_ *= lhs.den_;
  return gcd();
};
Rational& Rational::operator-=(const int64_t lhs) {
  Rational tmp{lhs};
  *this -= tmp;
  return *this;
}
Rational& Rational::operator*=(const Rational& lhs) {
  num_ *= lhs.num_;
  den_ *= lhs.den_;
  return gcd();
}
Rational& Rational::operator*=(const int64_t var) {
  Rational tmp{var};
  *this *= tmp;
  return *this;
}
Rational& Rational::operator/=(const Rational& lhs) {
  if (lhs.num_ == 0) {
    throw std::runtime_error("Division by zero");
  }
  num_ *= lhs.den_;
  den_ *= lhs.num_;
  return gcd();
}
Rational& Rational::operator/=(const int64_t var) {
  Rational tmp{var};
  return *this /= tmp;
}

[[nodiscard]] Rational operator+(const Rational& lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans += rhs;
}

[[nodiscard]] Rational operator+(const Rational& lhs, const int64_t rhs) {
  Rational ans{rhs};
  return ans += lhs;
}

[[nodiscard]] Rational operator+(const int64_t lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans += rhs;
}

[[nodiscard]] Rational operator-(const Rational& lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans -= rhs;
}

[[nodiscard]] Rational operator-(const Rational& lhs, const int64_t rhs) {
  Rational tmp{rhs};
  Rational ans{lhs};
  return ans -= tmp;
}

[[nodiscard]] Rational operator-(const int64_t lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans -= rhs;
}

[[nodiscard]] Rational operator*(const Rational& lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans *= rhs;
}

[[nodiscard]] Rational operator*(const Rational& lhs, const int64_t rhs) {
  Rational tmp{rhs};
  Rational ans{lhs};
  return ans *= tmp;
}

[[nodiscard]] Rational operator*(const int64_t lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans *= rhs;
}

[[nodiscard]] Rational operator/(const Rational& lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans /= rhs;
}

[[nodiscard]] Rational operator/(const Rational& lhs, const int64_t rhs) {
  Rational ans{lhs};
  Rational tmp{rhs};
  return ans /= tmp;
}

[[nodiscard]] Rational operator/(const int64_t lhs, const Rational& rhs) {
  Rational ans{lhs};
  return ans /= rhs;
}

std::istream& Rational::readFrom(std::istream& istrm) noexcept {
  int64_t num = 0;
  int64_t den = 1;
  char separator_ = '0';
  istrm >> num;
  istrm.get(separator_);
  int64_t trash = istrm.peek();
  istrm >> den;
  if(!istrm || trash > '9' || trash < '0'){
    istrm.setstate(std::ios_base::failbit);
    return istrm;
  }if(istrm.good() || istrm.eof()){
    if('/' == separator_ && den > 0){
      *this = Rational(num,den);
    }else{
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept {
  ostrm << num_ << separator << den_;
  return ostrm;
}

