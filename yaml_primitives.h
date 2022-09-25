#pragma once

#include <string>

#include "yaml_base_primitives.h"
#include <yaml-cpp/yaml.h>

#include "another_header.h"

namespace cpp_yaml_struct {

template<typename T>
inline bool InitFromYaml(test::SomeStruct<T>& data,
                         const YAML::Node& node,
                         const std::string& path) {
  return CheckKeyAndInit(data.i, node, "i", path);
}

};  // namespace cpp_yaml_struct
