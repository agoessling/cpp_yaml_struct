#pragma once

#include <array>
#include <string>
#include <utility>
#include <vector>

#include "another_header.h"
#include "another_struct.h"
#include "yaml_base_primitives.h"

using namespace cpp_yaml_struct;

namespace test {

struct TestStruct : YamlInitable {
  double d;
  bool b;
  int i;
  std::string s;
  std::vector<std::vector<int>> vec;
  std::array<int, 5> arr;
  std::vector<int> arr_vec[3];
  SubStruct struct_arr[1][2];
  std::pair<int, SubStruct> pair;
  SomeStruct<int> some_struct;
  std::vector<SomeStruct<int>> some_struct_vec;
};

};  // namespace test
