#include <functional>
#include <iostream>
#include <string>

#include "./JSONObject.cpp"

template <typename any>
void testEqual(any a, any b, bool expected) {
  bool result = (a == b);
  std::cout << (a) << " ?= "
            << b << " "
            << (result ? "true" : "false")
            << " expected : " << (expected ? "true" : "false")
            << "\n";
}