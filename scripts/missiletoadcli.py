import os
from argparse import ArgumentParser, Namespace
import sys


# Utilities scripts for missiletoad
# It contains the following scripts:
# - generate_component: Generate a new component

def generate_system(name_nms: Namespace):
    name: str = name_nms.name
    if not name:
        print('System name is required')
        return
    if not name.islower():
        print('System name must be in snake_case')
        return

    # Name might contain a namespace in the form of namespace::name (only one level)
    # If it does, we need to create the namespace folder. If only the name is provided, we don't need to create any folder
    # More than one level of namespace is not supported and will throw an error
    namespace = ''
    namespace_folder = ''
    if '::' in name:
        splitted = name.split('::')
        if len(splitted) != 2:
            print('Only one level of namespace is supported')
            return
        namespace = f'missiletoad::{splitted[0]}'
        namespace_folder = splitted[0]
        name = splitted[1]
        # Create namespace folder
        try:
            os.mkdir(f'missile_toad/include/missile_toad/{namespace_folder}/systems')
        except FileExistsError:
            pass
        try:
            os.mkdir(f'missile_toad/src/{namespace_folder}/systems')
        except FileExistsError:
            pass
    else:
        namespace = 'missiletoad'
        namespace_folder = 'missiletoad'

    print(f'Generating system {name} in namespace {namespace}')

    # Convert snake_case to PascalCase
    pascal_case_name = ''.join([word.capitalize() for word in name.split('_')])

    component_template_h = f'''#pragma once
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>

namespace {namespace}
{{
    class {pascal_case_name}System : public missiletoad::core::BaseSystem
    {{
    public:
        static void register_system(entt::meta_ctx& ctx);
    }};
}}
'''

    component_template_cpp = f'''
#include "missile_toad/{namespace_folder}/systems/{name}.system.hpp"
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>


void {namespace}::{pascal_case_name}System::register_system(entt::meta_ctx &ctx)
{{
    using namespace entt::literals;
    entt::meta<{namespace}::{pascal_case_name}System>(ctx)
            .type("{namespace}::{pascal_case_name}System"_hs)
            .base<missiletoad::core::BaseSystem>()
            .ctor<>();
}}'''

    with open(f'missile_toad/include/missile_toad/{namespace_folder}/systems/{name}.system.hpp', 'w') as f:
        f.write(component_template_h)

    with open(f'missile_toad/src/{namespace_folder}/systems/{name}.system.cpp', 'w') as f:
        f.write(component_template_cpp)

    with open(f'missile_toad/cmake/systems.cmake', 'a') as f:
        f.write(
            f'''include_system(missile_toad/{namespace_folder}/systems/{name}.system.hpp src/{namespace_folder}/systems/{name}.system.cpp {namespace}::{pascal_case_name}System)\n''')

    print(f'Generated system {name}')


def generate_component(name_nms: Namespace):
    '''Generate a new component'''

    name: str = name_nms.name
    if not name:
        print('Component name is required')
        return
    if not name.islower():
        print('Component name must be in snake_case')
        return

    # Name might contain a namespace in the form of namespace::name (only one level)
    # If it does, we need to create the namespace folder. If only the name is provided, we don't need to create any folder
    # More than one level of namespace is not supported and will throw an error
    namespace = ''
    namespace_folder = ''
    if '::' in name:
        splitted = name.split('::')
        if len(splitted) != 2:
            print('Only one level of namespace is supported')
            return
        namespace = f'missiletoad::{splitted[0]}'
        namespace_folder = splitted[0]
        name = splitted[1]
        # Create namespace folder
        try:
            os.mkdir(f'missile_toad/include/missile_toad/{namespace_folder}/components')
        except FileExistsError:
            pass

        try:
            os.mkdir(f'missile_toad/src/{namespace_folder}/components')
        except FileExistsError:
            pass
    else:
        namespace = 'missiletoad'
        namespace_folder = 'missiletoad'

    print(f'Generating component {name} in namespace {namespace}')

    # Convert snake_case to PascalCase
    pascal_case_name = ''.join([word.capitalize() for word in name.split('_')])

    component_template_h = f'''#pragma once
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>

namespace {namespace}
{{
    class {pascal_case_name}Component
    {{
    public:
        static void register_component(entt::meta_ctx& ctx);
    }};
}}
'''

    component_template_cpp = f'''
#include "missile_toad/{namespace_folder}/components/{name}.component.hpp"
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>


void {namespace}::{pascal_case_name}Component::register_component(entt::meta_ctx &ctx)
{{
    using namespace entt::literals;
    entt::meta<{namespace}::{pascal_case_name}Component>(ctx)
            .type("{namespace}::{pascal_case_name}Component"_hs)
            .ctor<>();
}}'''

    with open(f'missile_toad/include/missile_toad/{namespace_folder}/components/{name}.component.hpp', 'w') as f:
        f.write(component_template_h)

    with open(f'missile_toad/src/{namespace_folder}/components/{name}.component.cpp', 'w') as f:
        f.write(component_template_cpp)

    with open(f'missile_toad/cmake/components.cmake', 'a') as f:
        f.write(
            f'''include_component(missile_toad/{namespace_folder}/components/{name}.component.hpp src/{namespace_folder}/components/{name}.component.cpp {namespace}::{pascal_case_name}Component)\n''')

    print(f'Generated component {name}')


if __name__ == '__main__':
    parser = ArgumentParser(description='Missile Toad utilities')
    parser.set_defaults(func=lambda _: parser.print_help())

    subparsers = parser.add_subparsers(help='Sub commands')

    # Generate system
    parser_generate_system = subparsers.add_parser('system', help='Generate a new system')
    parser_generate_system.add_argument('name', help='System name in snake_case')
    parser_generate_system.set_defaults(func=generate_system)

    # Generate component
    parser_generate_component = subparsers.add_parser('component', help='Generate a new component')
    parser_generate_component.add_argument('name', help='Component name in snake_case')
    parser_generate_component.set_defaults(func=generate_component)

    args = parser.parse_args(sys.argv[1:])
    args.func(args)
