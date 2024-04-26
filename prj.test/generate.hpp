//
// Created by Егор Федюнин on 22.04.2024.
//
#pragma once
#ifndef MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_TEST_GENERATE_HPP_
#define MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_TEST_GENERATE_HPP_

#include <vector>
#include <string>

template<class T>
void FillData(const int n, std::vector<T>& data){
  data.clear();
  data.reserve(n);
  for(int i = 0 ; i < n ; i++){
    data.emplace_back(i);
  }
}

template<>
void FillData(const int n, std::vector<std::string>& data){
  data.clear();
  data.reserve(n);
  for(int i = 0 ; i < n; i++){
    data.emplace_back(std::to_string(i));
  }
}

#endif //MISIS2023F_23_03_FEDIUNIN_E_A_PRJ_TEST_GENERATE_HPP_
