//
// Created by Егор Федюнин on 13.11.2023.
//
#include "complex/complex.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

bool TestParse(const std::string& str) {
  std::istringstream istrm(str);
  Complex z;
  istrm >> z;
  if (istrm.good()) {
    std::cout << "Read succeeded: " << str << "->" << z << '\n';
  } else {
    std::cout << "Read error: " << str << "->" << z << '\n';
  }
  return istrm.good();
}

int main() {
  Complex z{2, 3};
  Complex z1{-1, 1};
  Complex z2{0};
  Complex z3{2.0000000000000001, 3};
  //input check
  TestParse("{9.1,2.0}");
  TestParse("{7.0, 2}");
  TestParse("{9}");
  TestParse("7,2");
  bool result = z == z3;
  std::cout << z << " == " << z3 << " : " << result << '\n';
  std::cout << z << " + " << z1 << " = " << z + z1 << '\n'; //{1,4}
  std::cout << z << " - " << z1 << " = " << z - z1 << '\n'; //{3,2}
  std::cout << z << " * " << z1 << " = " << z * z1 << '\n'; //{-5,-1}
  try {
    std::cout << z << " / " << z1 << " = " << z / z1 << '\n'; //{0.5,-2.5}
    std::cout << z << " / " << z2 << " = " << z / z2 << '\n'; //{0.5,-2.5}
  } catch (std::runtime_error& e) {
    std::cout << e.what();
  }
}
