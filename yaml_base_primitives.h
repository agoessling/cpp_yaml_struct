#pragma once

#include <string>

#include <yaml-cpp/yaml.h>

namespace cpp_yaml_struct {

struct YamlInitable {};

// Only declarations here and save definition for end of generated header so all InitFromYaml
// templates are available.

template<typename T>
bool CheckKeyAndInit(T& data,
                     const YAML::Node& parent_node,
                     const std::string& name,
                     const std::string& parent_path);

template<typename T>
bool InitFromYaml(T& data, const YAML::Node& node, const std::string& path);

}; // namespace cpp_yaml_struct
