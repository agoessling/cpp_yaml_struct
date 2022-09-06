import argparse

import CppHeaderParser


def get_init_function_declaration(type_name):
  return f'''\
template <>
inline bool InitFromYaml({type_name}& data, const YAML::Node& node, const std::string& path)'''


def get_init_function(struct):
  s = f'{get_init_function_declaration(qualified_struct_type(struct))} {{\n'
  s += '  bool success = true;\n'

  num_prop = len(struct['properties']['public'])
  for i, member in enumerate(struct['properties']['public']):
    s += '  success &= CheckKeyAndInit('
    s += f'data.{member["name"]}, node, "{member["name"]}", path);\n'

  s += '  return success;\n'

  s += '}'

  return s


def get_header_header(inputs, primitives):
  s = ''
  s += '#pragma once\n\n'
  s += '#include <string>\n\n'
  s += '#include <yaml-cpp/yaml.h>\n'

  for f in inputs:
    s += f'\n#include "{f}"'

  s += '\n'

  for f in primitives:
    s += f'\n#include "{f}"'

  s += '\n\nnamespace cpp_yaml_struct {'

  return s


def qualified_struct_type(struct):
  namespace = f'{struct["namespace"]}::' if struct['namespace'] else ''
  return f'{namespace}{struct["name"]}'


def qualified_member_type(member):
  namespace = f'{member["namespace"]}' if member['namespace'] else ''
  return f'{namespace}{member["type"]}'


def main():
  parser = argparse.ArgumentParser(
      description="Create YAML init functions from struct definitions.")
  parser.add_argument('-i', '--input', required=True, nargs='+', help='Input header file(s).')
  parser.add_argument('-o', '--output', help='Output header file.')
  parser.add_argument('-p', '--primitives', nargs='+', default=[],
      help='YAML primitive initialization header file(s).')
  parser.add_argument('-d', '--debug', action='store_true',
      help='Print details from parsed header files.')

  args = parser.parse_args()

  structs = []
  for input_file in args.input:
    header = CppHeaderParser.CppHeader(input_file)

    if args.debug:
      print(header.toJSON())

    for struct in header.classes.values():
      for base in struct['inherits']:
        if 'YamlInitable' in base['class']:
          structs.append(struct)

  s = get_header_header(args.input, args.primitives)

  for struct in structs:
    s += '\n\n'
    s += f'{get_init_function_declaration(qualified_struct_type(struct))};'

  for struct in structs:
    s += '\n\n'
    s += get_init_function(struct)

  s += '\n\n}; // namespace cpp_yaml_struct'

  if args.output:
    with open(args.output, 'w') as f:
      f.write(s)
  else:
    print(s)


if __name__ == '__main__':
  main()
