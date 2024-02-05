//
// Created by Егор Федюнин on 22.11.2023.
//
#ifndef RATIONAL_H
#define RATIONAL_H

#include <cstdint>
#include <iosfwd>
#include <stdexcept>

class Rational {
 public :
  //! \brief Умолчательный конструктор
  [[nodiscard]] Rational() = default;

  //! \brief Копирующий конструктор.
  [[nodiscard]] Rational(const Rational&) = default;

  //! \brief Конструирование рационального числа
  //! с заданными числителем и знаменателем
  //! \param[in] lhs - числитель рационального числа
  //! \param[in] rhs - знаменатель рационального числа
  [[nodiscard]] Rational(const int64_t& lhs, const int64_t& rhs) : num_(lhs), den_(rhs) {
    if (rhs == 0) {
      throw std::runtime_error("Division by zero");
    }
    if (den_ < 0) {
      num_ = -num_;
      den_ = -den_;
    }
    gcd();
  }

  //! \brief Конструирование рационального числа из заданного числителя
  //! \param lhs - числитель рационального числа
  [[nodiscard]]explicit Rational(int64_t lhs) : Rational(lhs, 1) {}

  [[nodiscard]]bool operator==(const Rational& lhs) const noexcept { return (num_ * lhs.den_ == den_ * lhs.num_); }

  [[nodiscard]]bool operator!=(const Rational& lhs) const noexcept { return !operator==(lhs); }

  [[nodiscard]] bool operator<(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator<=(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator>(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator>=(const Rational& rhs) const noexcept;

  [[nodiscard]] Rational operator-() const noexcept { return {-num_, den_}; }

  Rational& operator+=(const Rational& lhs);
  Rational& operator+=(const int64_t var);
  Rational& operator-=(const Rational& lhs);
  Rational& operator-=(const int64_t lhs);
  Rational& operator*=(const Rational& lhs);
  Rational& operator*=(const int64_t var);
  Rational& operator/=(const Rational& lhs);
  Rational& operator/=(const int64_t var);

  [[nodiscard]] std::int64_t num() { return num_; };
  [[nodiscard]] std::int64_t den() { return den_; };

  std::istream& readFrom(std::istream& istrm) noexcept;

  std::ostream& writeTo(std::ostream& ostrm) const noexcept;

  static const char separator{'/'};  //!< разделитель форматированного представления
 private:
  std::int64_t num_ = 0;
  std::int64_t den_ = 1;
  //! \brief Сокращение дроби
  Rational& gcd();

};

//! \brief Сложение рациональных чисел.
[[nodiscard]] Rational operator+(const Rational& lhs, const Rational& rhs);

//! \brief Сложение рационального и целого чисел.
[[nodiscard]] Rational operator+(const Rational& lhs, const int64_t rhs);

//! \brief Сложение целого и рационального чисел.
[[nodiscard]] Rational operator+(const int64_t lhs, const Rational& rhs);

//! \brief Вычитание рационального из рационального числа.
[[nodiscard]] Rational operator-(const Rational& lhs, const Rational& rhs);

//! \brief Вычитание целого из рационального числа.
[[nodiscard]] Rational operator-(const Rational& lhs, const int64_t rhs);

//! \brief Вычитание рационального из целого числа.
[[nodiscard]] Rational operator-(const int64_t lhs, const Rational& rhs);

//! \brief Умножение рационального числа на рациональное.
[[nodiscard]] Rational operator*(const Rational& lhs, const Rational& rhs);

//! \brief Умножение рационального числа на рациональное.
[[nodiscard]] Rational operator*(const Rational& lhs, const int64_t rhs);

//! \brief Умножение целого числа на рациональное.
[[nodiscard]] Rational operator*(const int64_t lhs, const Rational& rhs);

//! \brief Деление рационального числа на рациональное.
[[nodiscard]] Rational operator/(const Rational& lhs, const Rational& rhs);

//! \brief Деление рационального числа на рациональное.
[[nodiscard]] Rational operator/(const Rational& lhs, const int64_t rhs);

//! \brief Деление целого числа на рациональное.
[[nodiscard]] Rational operator/(const int64_t lhs, const Rational& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& Rational) noexcept {
  return Rational.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& Rational) noexcept {
  return Rational.readFrom(istrm);
}

#endif //RATIONAL_h