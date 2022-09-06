load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def cpp_yaml_struct_first_level_deps():
    http_archive(
        name = "rules_python",
        sha256 = "cdf6b84084aad8f10bf20b46b77cb48d83c319ebe6458a18e9d2cebf57807cdd",
        strip_prefix = "rules_python-0.8.1",
        url = "https://github.com/bazelbuild/rules_python/archive/refs/tags/0.8.1.tar.gz",
    )

    http_archive(
	name = "yaml-cpp",
	sha256 = "43e6a9fcb146ad871515f0d0873947e5d497a1c9c60c58cb102a97b47208b7c3",
	strip_prefix = "yaml-cpp-yaml-cpp-0.7.0",
	url = "https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz",
    )
