//
// Created by Егор Федюнин on 13.11.2023.
//
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iosfwd>
#include <cmath>
#include <limits>

//!\class Complex complex.h complex/complex.h
//!\brief  Комплексные числа
struct Complex{
  double re{0.0}; //!< вещественная часть комплексного числа

  double im = {0.0}; //!< мнимая часть комплексного числа

  //! \brief Умолчательный конструктор
  [[nodiscard]] Complex() = default;

  //! \brief Копирующий конструктор.
  [[nodiscard]] Complex(const Complex&) = default;

  //! \brief Конструирование комплексного числа
  //! с заданными вещественной real и мнимой imaginary частями.
  //! \param[in] real - вещественная часть комплексного числа
  //! \param[in] imaginary - мнимая часть комплексного числа
  [[nodiscard]] Complex(const double &real, const double &imaginary){re = real; im = imaginary;}

  //! \brief Конструирование комплексного числа из заданного вещественного.
  //! \param real - вещественная часть комплексного числа
  [[nodiscard]]explicit Complex(double real) : Complex(real, 0.0) {}

  //! \brief Присваивание.
  Complex& operator=(const Complex&) = default;


  //! \brief Деструктор.
  ~Complex() = default;

  //! \brief Унарный минус.
  Complex operator-() const noexcept { return Complex{-re, -im};  }

  //! \brief Сравнение комплексных чисел на равенство.
  //!
  //! Два комплексных числа считаются равными, если модуль разности
  //! вещественных и мнимых частей не превосходит eps = 2 * std::numeric_limits<double>::epsilon()
  [[nodiscard]]bool operator==(const Complex& complex) const {
    return ( std::abs(re - complex.re) < 2 * std::numeric_limits<double>::epsilon() && std::abs(im - complex.im)  <
                          2 * std::numeric_limits<double>::epsilon());
  }

  [[nodiscard]]bool operator>(const Complex& complex) const {
    return ( std::abs(re - complex.re) < 2 * std::numeric_limits<double>::epsilon() && std::abs(im - complex.im)  <
        2 * std::numeric_limits<double>::epsilon());
  }

  //! \brief Сравнение комплексного и вещественного чисел на равенство.
  [[nodiscard]]bool operator==(const double& var) const noexcept {return (std::abs(re - var) <
                                  std::numeric_limits<double>::epsilon() && im < 2 * std::numeric_limits<double>::epsilon());}

  //! \brief Сравнение комплексных чисел на неравенство. \sa Complex::operator==
  [[nodiscard]]bool operator!=(const Complex& complex) const noexcept {return !operator==(complex);}

  //! \brief Сравнение комплексного и вещественного чисел на неравенство. \sa Complex::operator==
  [[nodiscard]]bool operator!=(const double& var) const noexcept {return !operator==(var);}

  //! \brief Присваивающее сложение с комплексным числом.
  Complex& operator+=(const Complex& complex) noexcept;

  //! \brief Присваивающее сложение с вещественным числом.
  Complex& operator+=(const double var) noexcept;

  //! \brief Присваивающее вычитание с комплексным числом.
  Complex& operator-=(const Complex& complex) noexcept;

  //! \brief Присваивающее сложение с вещественным числом.
  Complex& operator-=(const double var) noexcept;

  //! \brief Присваивающее умножение на комплексное число.
  Complex& operator*=(const Complex& complex) noexcept;

  //! \brief Присваивающее умножение на вещественное  число.
  Complex& operator*=(const double var) noexcept;

  //! \brief Присваивающее деление на комплексное число.
  Complex& operator/=(const Complex& complex);

  //! \brief Присваивающее деление на вещественное  число.
  Complex& operator/=(const double var);


  //! \brief Форматированный вывод в поток ostrm комплексного числа в виде {re,im}.
  //!
  //! \param[in,out] ostrm - поток
  //! \retval поток
  [[nodiscard]]std::ostream &writeTo(std::ostream &ostrm) const noexcept;

  //! \brief Форматированный ввод из потока istrm комплексного числа в виде {re,im}.
  //!
  //! \param[in,out] istrm - поток
  //! \retval поток

  [[nodiscard]]std::istream &readFrom(std::istream &istrm) noexcept;
  static const char leftBrace{ '{' };  //!< левая скобка форматированного представления
  static const char rightBrace{ '}' };  //!< разделитель форматированного представления
  static const char separator{ ',' };  //!< правая скобка форматированного представления
};

//! \brief Сложение комплексных чисел.
[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs);

//! \brief Сложение комплексного и вещественного чисел.
[[nodiscard]] Complex operator+(const Complex& lhs, const double rhs);

//! \brief Сложение вещественного и комплексного чисел.
[[nodiscard]] Complex operator+(const double lhs, const Complex& rhs);

//! \brief Вычитание комплексного из комплексного числа.
[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs);

//! \brief Вычитание вещественного из комплексного числа.
[[nodiscard]] Complex operator-(const Complex& lhs, const double rhs);

//! \brief Вычитание комплексного из вещественного числа.
[[nodiscard]] Complex operator-(const double lhs, const Complex& rhs);

//! \brief Умножение комплексного числа на комплексное.
[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs);

//! \brief Умножение комплексного числа на вещественное.
[[nodiscard]] Complex operator*(const Complex& lhs, const double rhs);

//! \brief Умножение вещественного числа на комплексное.
[[nodiscard]] Complex operator*(const double lhs, const Complex& rhs);

//! \brief Деление комплексного числа на комплексное.
[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);

//! \brief Деление комплексного числа на вещественное.
[[nodiscard]] Complex operator/(const Complex& lhs, const double rhs);

//! \brief Деление вещественного числа на комплексное.
[[nodiscard]] Complex operator/(const double lhs, const Complex& rhs);


inline std::ostream &operator<<(std::ostream &ostrm, const Complex &complex){
  return complex.writeTo(ostrm);
}


inline std::istream &operator>>(std::istream &istrm,Complex &complex){
  return complex.readFrom(istrm);
}

#endif //COMPLEX_h
