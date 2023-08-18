#pragma once

#include "another_header.h"
#include "yaml_base_primitives.h"

namespace test {

struct SubStruct : cpp_yaml_struct::YamlInitable {
  int i;
};

struct OutOfLineStruct {
  float i;
};

};  // namespace test
