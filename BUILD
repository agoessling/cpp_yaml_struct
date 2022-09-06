load("@cpp_yaml_struct//:yaml_initialization.bzl", "yaml_initialization")
load("@cpp_yaml_struct_py_deps//:requirements.bzl", "requirement")

exports_files(["yaml_base_primitives.h"])

cc_library(
    name = "yaml_base_primitives",
    hdrs = ["yaml_base_primitives.h"],
    deps = [
        "@yaml-cpp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "struct_to_initialize",
    hdrs = ["struct_to_initialize.h"],
    deps = [
        ":another_struct",
        ":yaml_base_primitives",
    ],
)

cc_library(
    name = "another_struct",
    hdrs = ["another_struct.h"],
    deps = [
        ":another_header",
        ":yaml_base_primitives",
    ],
)

cc_library(
    name = "another_header",
    hdrs = ["another_header.h"],
)

yaml_initialization(
    name = "yaml_initialization",
    inputs = [
        ":another_struct",
        ":struct_to_initialize",
    ],
)

cc_binary(
    name = "test_initialization",
    srcs = ["test_initialization.cc"],
    data = ["test.yaml"],
    deps = [
        ":yaml_initialization",
        ":struct_to_initialize",
    ],
)

py_binary(
    name = "gen_yaml_initialization",
    srcs = ["gen_yaml_initialization.py"],
    deps = [
        requirement("robotpy-cppheaderparser"),
    ],
    visibility = ["//visibility:public"],
)
