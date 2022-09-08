#pragma once

#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

namespace cpp_yaml_struct {

template<typename T>
bool CheckKeyAndInit(T& data,
                     const YAML::Node& parent_node,
                     const std::string& name,
                     const std::string& parent_path) {
  YAML::Node node = parent_node[name];
  const std::string path = parent_path + "/" + name;

  if (!node) {
    std::cout << "WARNING (YAML): No value for \"" << path << "\"." << std::endl;
    return false;
  }

  return InitFromYaml(data, node, path);
}

}; // namespace cpp_yaml_struct
