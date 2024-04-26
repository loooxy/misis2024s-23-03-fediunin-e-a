//
// Created by Егор Федюнин on 15.04.2024.
//
#include "bitset/bitset.hpp"
#include <random>
#include <chrono>
#include <iostream>
#include <sstream>

int main(){
  BitSet bitset(10);
  for(int i = 0;i < 10; i++){
    bitset.Set(i, i % 2);
  }
  std::ostringstream oss;
  bitset.WriteTxt(oss);
  std::cout << oss.str();
  std::istringstream iss(oss.str());
  BitSet bitset1{10};
  bitset1.ReadTxt(iss);
  std::ostringstream oss1;
  bitset1.WriteTxt(oss1);
  for(int i = 0 ; i < bitset1.Size(); i++){
    std::cout << bitset1[i];
  }
  std::cout << '\n';
  std::cout << oss1.str();
  /*oss.flush();
  bitset.WriteBinary(oss);
  std::cout << oss.str();
*/
}