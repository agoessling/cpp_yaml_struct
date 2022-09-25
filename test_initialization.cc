#include <array>
#include <iostream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "struct_to_initialize.h"
#include "yaml_initialization.h"

TEST(TestStruct, Initialization) {
  YAML::Node config = YAML::LoadFile("test.yaml");

  test::TestStruct init;
  EXPECT_TRUE(cpp_yaml_struct::CheckKeyAndInit(init, config, "TestStruct", ""));

  EXPECT_EQ(init.d, 5.34);
  EXPECT_EQ(init.b, true);
  EXPECT_EQ(init.i, 442);
  EXPECT_EQ(init.s, "Hello, World!");

  std::vector<std::vector<int>> vec{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  EXPECT_EQ(init.vec, vec);

  std::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(init.arr, arr);

  std::vector<int> arr_vec[3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  EXPECT_EQ(init.arr_vec[0], arr_vec[0]);
  EXPECT_EQ(init.arr_vec[1], arr_vec[1]);
  EXPECT_EQ(init.arr_vec[2], arr_vec[2]);

  EXPECT_EQ(init.struct_arr[0][0].i, 555);
  EXPECT_EQ(init.struct_arr[0][1].i, 555);

  EXPECT_EQ(init.pair.first, 1);
  EXPECT_EQ(init.pair.second.i, 555);

  EXPECT_EQ(init.some_struct.i, 230);

  EXPECT_EQ(init.some_struct_vec.size(), 2);
  EXPECT_EQ(init.some_struct_vec[0].i, 231);
  EXPECT_EQ(init.some_struct_vec[1].i, 232);
}
