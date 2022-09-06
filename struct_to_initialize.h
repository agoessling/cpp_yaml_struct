#pragma once

#include <array>
#include <string>
#include <vector>

#include "another_struct.h"
#include "yaml_base_primitives.h"

using namespace cpp_yaml_struct;

namespace test {

struct TestStruct : YamlInitable {
  double d;
  bool b;
  int i;
  std::string s;
  std::vector<std::vector<double>> vec;
  std::array<double, 5> arr;
  std::vector<double> arr_vec[3];
  SubStruct struct_arr[1][2];
};

};  // namespace test
