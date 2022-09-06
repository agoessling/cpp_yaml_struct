#pragma once

#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include <yaml-cpp/yaml.h>

// Helper type traits / meta functions.
namespace {

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

};  // namespace

struct YamlInitable {};

template<typename T>
bool InitFromYaml(T& data, const YAML::Node& node);

template<typename T>
bool CheckAndInit(T& child_data,
                  const YAML::Node& parent_node,
                  const std::string& child_key,
                  const std::string& parent_name) {
  YAML::Node child_node = parent_node[child_key];

  if (!child_node) {
    std::cout << "WARNING (YAML): No value for \"" << child_key << "\" ";
    std::cout << "in \"" << parent_name << "\"" << std::endl;
    return false;
  }

  if constexpr (::is_sequence<T>::value) {
    if (!child_node.IsSequence()) {
      std::cout << "WARNING (YAML): Value for \"" << child_key << "\" ";
      std::cout << "in \"" << parent_name << "\" is not sequence." << std::endl;
      return false;
    }

    if constexpr (::is_fixed_array<T>::value) {
      size_t len = ::GetSize(child_data);
      if (child_node.size() != len) {
        std::cout << "WARNING (YAML): Length of \"" << child_key << "\" ";
        std::cout << "in \"" << parent_name << "\" is not " << len << "." << std::endl;
        return false;
      }
    }
  }

  return InitFromYaml(child_data, child_node);
}

template<typename T>
bool InitFromYaml(T& data, const YAML::Node& node) {
  // Sequences.
  if constexpr (::is_sequence<T>::value) {
    if constexpr (::is_vector<T>::value) {
      data.clear();
      data.resize(node.size());
    }

    bool success = true;
    for (size_t i = 0; i < ::GetSize(data); ++i) {
      success &= InitFromYaml(data[i], node[i]);
    }
    return success;

  // Everything else.
  } else {
    data = node.as<T>();
    return true;
  }
}
