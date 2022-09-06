#include <iostream>

#include "struct_to_initialize.h"
#include "yaml_initialization.h"

int main() {
  YAML::Node config = YAML::LoadFile("test.yaml");

  test::TestStruct init;
  InitFromYaml(init, config["TestStruct"]);

  std::cout << "d: " << init.d << std::endl;
  std::cout << "b: " << init.b << std::endl;
  std::cout << "i: " << init.i << std::endl;
  std::cout << "s: " << init.s << std::endl;

  std::cout << "vec: [";
  size_t len_outer = init.vec.size();
  for (size_t i = 0; i < len_outer; ++i) {
    std::cout << "[";

    size_t len_inner = init.vec[i].size();
    for (size_t j = 0; j < len_inner; ++j) {
      std::cout << init.vec[i][j];
      if (j < len_inner - 1) std::cout << ", ";
    }

    std::cout << "]";
    if (i < len_outer - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  std::cout << "arr: [";
  len_outer = sizeof(init.arr) / sizeof(init.arr[0]);
  for (size_t i = 0; i < len_outer; ++i) {
    std::cout << init.arr[i];
    if (i < len_outer - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  std::cout << "arr_vec: [";
  len_outer = sizeof(init.arr_vec) / sizeof(init.arr_vec[0]);
  for (size_t i = 0; i < len_outer; ++i) {
    std::cout << "[";

    size_t len_inner = init.arr_vec[i].size();
    for (size_t j = 0; j < len_inner; ++j) {
      std::cout << init.arr_vec[i][j];
      if (j < len_inner - 1) std::cout << ", ";
    }

    std::cout << "]";
    if (i < len_outer - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  return 0;
}
