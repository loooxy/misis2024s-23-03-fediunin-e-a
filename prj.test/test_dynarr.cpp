//
// Created by egorf on 10.12.2023.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "dynarr/dynarr.hpp"
#include <iostream>

TEST_CASE("Testing DynArr constructors and assignment operator") {
  DynArr arr1(5); // Create a DynArr of size 5 using the size constructor
  CHECK(arr1.Size() == 5); // Check the size

  DynArr arr2{arr1}; // Assign arr2 from arr1
  CHECK(arr2.Size() == 5); // Check the size

  arr1.Resize(10); // Resize arr1 to size 10
  CHECK(arr1.Size() == 10); // Check the size

  arr2 = arr1; // Assign arr1 to arr2
  CHECK(arr2.Size() == 10); // Check the size


  DynArr arr3{5};
  for (ptrdiff_t i = 0; i < arr3.Size(); i++) {
    arr3[i] = static_cast<float>(i + 1);
  }
  CHECK(arr3.Size() == 5); // Check the size
  CHECK(arr3[0] == 1.0f); // Check the first element
  CHECK(arr3[1] == 2.0f); // Check the second element
  CHECK(arr3[2] == 3.0f); // Check the third element
  CHECK(arr3[3] == 4.0f); // Check the fourth element
  CHECK(arr3[4] == 5.0f); // Check the fifth element

  DynArr arr4 = arr3; // Create a DynArr using assignment operator
  CHECK(arr4.Size() == arr3.Size());
  for (int i = 0; i < arr3.Size(); i++) {
    CHECK(arr3[i] == arr4[i]); // Check if all elements are equal;
  }
  arr4[0] = -arr3[0];
  CHECK(arr4[0] != arr3[0]);
}

TEST_CASE("Testing DynArr methods") {
  DynArr arr(10); // Create a DynArr of size 10
  CHECK(arr.Size() == 10); // Check the initial size

  arr.Resize(5); // Resize the array to size 5
  CHECK(arr.Size() == 5); // Check the size after resizing

  arr.Resize(12); // Resize the array to size 12
  CHECK(arr.Size() == 12); // Check the size after resizing

  arr[0] = 1.0f; // Set the first element to 1.0
  CHECK(arr[0] == 1.0f); // Check the first element

  CHECK_THROWS(arr.Resize(-1)); // Resize the array to size -1

}

TEST_CASE("Testing DynArr operator[] with out of bounds index") {
  DynArr arr(5); // Create a DynArr of size 5
  CHECK_THROWS(arr[5]); // Check that accessing an element at index 5 throws an exception
  CHECK_THROWS(arr[10]); // Check that accessing an element at index 10 throws an exception
  CHECK_THROWS(arr[-1]);
}

