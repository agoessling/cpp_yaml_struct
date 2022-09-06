load("@rules_python//python:pip.bzl", "pip_install")

def cpp_yaml_struct_second_level_deps():
    pip_install(
       name = "cpp_yaml_struct_py_deps",
       requirements = "@cpp_yaml_struct//:requirements.txt",

    )
