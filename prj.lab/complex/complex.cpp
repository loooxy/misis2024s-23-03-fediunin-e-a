#include "complex/complex.hpp"
#include <iostream>
#include <stdexcept>

Complex& Complex::operator+=(const Complex& complex) noexcept {
  re += complex.re;
  im += complex.im;
  return *this;
}

Complex& Complex::operator+=(const double var) noexcept {
  Complex tmp{var};
  Complex::operator+=(tmp);
  return *this;
}

Complex& Complex::operator-=(const Complex& complex) noexcept {
  re -= complex.re;
  im -= complex.im;
  return *this;
}

Complex& Complex::operator-=(const double var) noexcept {
  Complex tmp{var};
  Complex::operator-=(tmp);
  return *this;
}

Complex& Complex::operator*=(const Complex& complex) noexcept {
  double a = (re * complex.re - im * complex.im);
  double b = (re * complex.im + complex.re * im);
  re = a;
  im = b;
  return *this;
}

Complex& Complex::operator*=(const double var) noexcept {
  Complex complex(var);
  double a = (re * complex.re - im * complex.im);
  double b = (re * complex.im + complex.re * im);
  re = a;
  im = b;
  return *this;
}

Complex& Complex::operator/=(const Complex& complex) {
  if (complex == 0.0) {
    throw std::runtime_error("Division by zero");
  }
  double a = (re * complex.re + im * complex.im) /
      ((complex.re * complex.re) + (complex.im * complex.im));
  double b = (complex.re * im - re * complex.im) /
      ((complex.re * complex.re) + (complex.im * complex.im));
  re = a;
  im = b;
  return *this;
}

Complex& Complex::operator/=(const double var) {
  Complex complex(var);;
  return *this /= complex;
}

[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) {
  Complex ans{lhs};
  return ans += rhs;
}

[[nodiscard]] Complex operator+(const Complex& lhs, const double rhs) {
  Complex ans{rhs};
  return ans += lhs;
}

[[nodiscard]] Complex operator+(const double lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans += rhs;
}

[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans -= rhs;
}

[[nodiscard]] Complex operator-(const Complex& lhs, const double rhs) {
  Complex ans(lhs);
  return ans -= rhs;
}

[[nodiscard]] Complex operator-(const double lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans -= rhs;
}

[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans *= rhs;
}

[[nodiscard]] Complex operator*(const Complex& lhs, const double rhs) {
  Complex ans(rhs);
  return ans *= lhs;
}

[[nodiscard]] Complex operator*(const double lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans *= rhs;
}

[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans /= rhs;
}

[[nodiscard]] Complex operator/(const Complex& lhs, const double rhs) {
  Complex ans(lhs);
  return ans /= rhs;
}

[[nodiscard]] Complex operator/(const double lhs, const Complex& rhs) {
  Complex ans(lhs);
  return ans /= rhs;
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const noexcept {
  return ostrm << leftBrace << re << separator <<
               im << rightBrace;
}

std::istream& Complex::readFrom(std::istream& istrm) noexcept {
  double real = 0;
  double imaginary = 0;
  char leftBrace_, rightBrace_, separator_;
  istrm >> leftBrace_ >> real >> separator_ >> imaginary >> rightBrace_;
  if (istrm.good()) {
    if ((::Complex::leftBrace == leftBrace_) && (::Complex::rightBrace == rightBrace_)
        && ::Complex::separator == separator_) {
      re = real;
      im = imaginary;
    } else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}


