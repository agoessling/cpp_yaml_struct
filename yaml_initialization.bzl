def _yaml_initialization_impl(ctx):
    dep_cc_infos = []
    headers = []
    primitives = []
    post_includes = []

    dep_cc_infos.append(ctx.attr._yaml_cpp[CcInfo])

    primitives += ctx.attr._base_primitives[CcInfo].compilation_context.direct_public_headers

    for src in ctx.attr.inputs:
        dep_cc_infos.append(src[CcInfo])
        headers += src[CcInfo].compilation_context.direct_public_headers

    for primitive in ctx.attr.primitives:
        dep_cc_infos.append(primitive[CcInfo])
        primitives += primitive[CcInfo].compilation_context.direct_public_headers

    for include in ctx.attr._post_includes:
        dep_cc_infos.append(include[CcInfo])
        post_includes += include[CcInfo].compilation_context.direct_public_headers

    output = ctx.actions.declare_file("{}.h".format(ctx.label.name))

    args = ctx.actions.args()
    args.add_all("-i", headers)
    args.add("-o", output)
    args.add_all("-p", primitives)
    args.add_all("--post_includes", post_includes)

    ctx.actions.run(
        outputs = [output],
        inputs = headers,
        executable = ctx.attr._gen_yaml_initialization.files_to_run,
        arguments = [args],
        mnemonic = "GenYamlInitialization",
        progress_message = "Generating YAML initialization",
    )

    output_depset = depset([output])

    cc_info = CcInfo(
        compilation_context = cc_common.create_compilation_context(headers = output_depset)
    )

    return [
        DefaultInfo(files = output_depset),
        cc_common.merge_cc_infos(
            direct_cc_infos = [cc_info],
            cc_infos = dep_cc_infos,
        ),
    ]


yaml_initialization = rule(
    implementation = _yaml_initialization_impl,
    doc = "Generate struct YAML initialization library.",
    attrs = {
        "inputs": attr.label_list(
            doc = "Libraries with structs to initialize.",
            providers = [CcInfo],
            mandatory = True,
        ),
        "primitives": attr.label_list(
            doc = "Primitive initialization template headers.",
            providers = [CcInfo],
        ),
        "_gen_yaml_initialization": attr.label(
            doc = "YAML initialization generation script.",
            default = Label("@cpp_yaml_struct//:gen_yaml_initialization"),
            executable = True,
            cfg = "exec",
        ),
        "_base_primitives": attr.label(
            doc = "Base YAML initialization primitives.",
            default = Label("@cpp_yaml_struct//:yaml_base_primitives"),
            providers = [CcInfo],
        ),
        "_post_includes": attr.label_list(
            doc = "Includes for after InitFromYaml definitions.",
            default = [
                Label("@cpp_yaml_struct//:yaml_base_primitives_impl"),
            ],
            providers = [CcInfo],
        ),
        "_yaml_cpp": attr.label(
            doc = "yaml-cpp library.",
            default = Label("@yaml-cpp"),
            providers = [CcInfo],
        ),
    },
)
