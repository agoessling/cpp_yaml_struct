# cpp_yaml_struct

Automatic YAML serialization to C++ structures.

## Usage

### WORKSPACE

To incorporate `cpp_yaml_struct` into your project copy the following into your `WORKSPACE` file.

```Starlark
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "cpp_yaml_struct",
    # See release page for latest version url and sha.
)

load("@cpp_yaml_struct//:cpp_yaml_struct_first_level_deps.bzl", "cpp_yaml_struct_first_level_deps")
cpp_yaml_struct_first_level_deps()

load("@cpp_yaml_struct//:cpp_yaml_struct_second_level_deps.bzl", "cpp_yaml_struct_second_level_deps")
cpp_yaml_struct_second_level_deps()
```
