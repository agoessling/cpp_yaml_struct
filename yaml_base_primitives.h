#pragma once

#include <array>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include <yaml-cpp/yaml.h>

// Helper type traits / meta functions.
namespace cpp_yaml_struct {
namespace type_traits {

// is_indexable_container
template <typename T>
struct is_indexable_container : std::false_type {};

template <typename U, size_t N>
struct is_indexable_container<std::array<U, N>> : std::true_type {};

template <typename U>
struct is_indexable_container<std::vector<U>> : std::true_type {};

// is_vector
template <typename T>
struct is_vector : std::false_type {};

template <typename U>
struct is_vector<std::vector<U>> : std::true_type {};

// is_fixed_array
template <typename T>
struct is_fixed_array : std::false_type {};

template <typename U, size_t N>
struct is_fixed_array<U[N]> : std::true_type {};

template <typename U, size_t N>
struct is_fixed_array<std::array<U, N>> : std::true_type {};

// is_sequence
template <typename T>
struct is_sequence : std::false_type {};

template <typename U, size_t N>
struct is_sequence<U[N]> : std::true_type {};

template <typename U, size_t N>
struct is_sequence<std::array<U, N>> : std::true_type {};

template <typename U>
struct is_sequence<std::vector<U>> : std::true_type {};

// GetSize
template <typename T>
size_t GetSize(const T& array_like) {
  if constexpr(is_indexable_container<T>::value) {
    return array_like.size();
  }

  if constexpr(std::is_array<T>::value) {
    return std::extent<T>::value;
  }
}

// always_false
template <typename T>
struct always_false : std::false_type {};

};  // namespace type_traits

struct YamlInitable {};

// Only declare here and save definition for end of generated header so all InitFromYaml templates
// are available.
template<typename T>
bool CheckKeyAndInit(T& data,
                     const YAML::Node& parent_node,
                     const std::string& name,
                     const std::string& parent_path);

template<typename T>
bool CheckSequence(const T& data, const YAML::Node& node, const std::string& path) {
  if (!node.IsSequence()) {
    std::cout << "WARNING (YAML): Value for \"" << path;
    std::cout << "\" is not sequence." << std::endl;
    return false;
  }

  if constexpr (type_traits::is_fixed_array<T>::value) {
    size_t len = type_traits::GetSize(data);
    if (node.size() != len) {
      std::cout << "WARNING (YAML): Length of \"" << path;
      std::cout << "\" is not " << len << "." << std::endl;
      return false;
    }
  }

  return true;
}

template<typename T>
bool InitFromYaml(T& data, const YAML::Node& node, const std::string& path) {
  // Sequences.
  if constexpr (type_traits::is_sequence<T>::value) {
    if (!CheckSequence(data, node, path)) {
      return false;
    }

    if constexpr (type_traits::is_vector<T>::value) {
      data.clear();
      data.resize(node.size());
    }

    bool success = true;
    for (size_t i = 0; i < type_traits::GetSize(data); ++i) {
      const std::string elem_path = path + "[" + std::to_string(i) + "]";
      success &= InitFromYaml(data[i], node[i], elem_path);
    }
    return success;

  // Everything else.
  } else {
    data = node.as<T>();
    return true;
  }
}

}; // namespace cpp_yaml_struct
