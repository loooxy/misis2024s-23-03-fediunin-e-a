//
// Created by Егор Федюнин on 04.03.2024.
//



//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"


#include <queuelstpr/queuelstpr.hpp>
#include <iostream>
int main() {
  QueueLstPr arr;
  arr.Push(-1);
  arr.Push(2);
  arr.Push(0);
  arr.Push(5);
  arr.Pop();
  arr.Pop();
  std::cout << arr.Top();
}

