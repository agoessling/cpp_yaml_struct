workspace(name = "cpp_yaml_struct")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

load("@cpp_yaml_struct//:cpp_yaml_struct_first_level_deps.bzl", "cpp_yaml_struct_first_level_deps")
cpp_yaml_struct_first_level_deps()

load("@cpp_yaml_struct//:cpp_yaml_struct_second_level_deps.bzl", "cpp_yaml_struct_second_level_deps")
cpp_yaml_struct_second_level_deps()

# Google test
http_archive(
    name = "gtest",
    sha256 = "353571c2440176ded91c2de6d6cd88ddd41401d14692ec1f99e35d013feda55a",
    strip_prefix = "googletest-release-1.11.0",
    url = "https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip",
)
