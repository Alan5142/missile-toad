import os
from argparse import ArgumentParser, Namespace
import sys


# Utilities scripts for missiletoad
# It contains the following scripts:
# - generate_component: Generate a new component

def generate_system(params: Namespace):
    name: str = params.name
    folder: str = params.folder
    if not name:
        print('System name is required')
        return
    if not name.islower():
        print('System name must be in snake_case')
        return

    if not folder:
        print('System folder is required')
        return

    # Name might contain a namespace in the form of namespace::name (only one level)
    # If it does, we need to create the namespace folder. If only the name is provided, we don't need to create any folder
    # More than one level of namespace is not supported and will throw an error
    namespace = ''.join(folder.lower().split('_'))

    print(f'Generating system {name} in namespace {namespace}')

    # Convert snake_case to PascalCase
    pascal_case_name = ''.join([word.capitalize() for word in name.split('_')])

    component_template_h = f'''#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{{
    class Game;
}}

namespace {namespace}
{{
    class {pascal_case_name}System : public missileengine::BaseSystem
    {{
    public:
        {pascal_case_name}System(missileengine::Game *game);
        static void register_system(entt::meta_ctx& ctx);
    }};
}}
'''

    component_template_cpp = f'''
#include "{folder}/systems/{name}.system.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>

{namespace}::{pascal_case_name}System::{pascal_case_name}System(missileengine::Game *game)
{{
    // TODO: Add your constructor code here
}}

void {namespace}::{pascal_case_name}System::register_system(entt::meta_ctx &ctx)
{{
    using namespace entt::literals;
    entt::meta<{namespace}::{pascal_case_name}System>(ctx)
            .type("{namespace}::{pascal_case_name}System"_hs)
            .base<missileengine::BaseSystem>()
            .ctor<missileengine::Game*>();
    // TODO: Add your register code here
}}'''

    with open(f'src/{folder}/include/{folder}/systems/{name}.system.hpp', 'w') as f:
        f.write(component_template_h)

    with open(f'src/{folder}/src/systems/{name}.system.cpp', 'w') as f:
        f.write(component_template_cpp)

    with open(f'src/{folder}/cmake/systems.cmake', 'a') as f:
        f.write(
            f'''include_system({folder}/systems/{name}.system.hpp src/systems/{name}.system.cpp {namespace}::{pascal_case_name}System)\n''')

    print(f'Generated system {name}')

def generate_component(args: Namespace):
    '''Generate a new component'''

    name: str = args.name
    folder: str = args.folder
    if not name:
        print('Component name is required')
        return
    if not name.islower():
        print('Component name must be in snake_case')
        return

    if not folder:
        print('Component folder is required')
        return

    # Name might contain a namespace in the form of namespace::name (only one level)
    # If it does, we need to create the namespace folder. If only the name is provided, we don't need to create any folder
    # More than one level of namespace is not supported and will throw an error
    namespace = ''.join(folder.lower().split('_'))

    print(f'Generating component {name} in namespace {namespace}')

    # Convert snake_case to PascalCase
    pascal_case_name = ''.join([word.capitalize() for word in name.split('_')])

    component_template_h = f'''#pragma once
#include "missile_engine/common.hpp"

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
#include "{folder}/components/{name}.component.hpp"
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>


void {namespace}::{pascal_case_name}Component::register_component(entt::meta_ctx &ctx)
{{
    using namespace entt::literals;
    entt::meta<{namespace}::{pascal_case_name}Component>(ctx)
            .type("{namespace}::{pascal_case_name}Component"_hs)
            .ctor<>();
}}'''

    with open(f'src/{folder}/include/{folder}//components/{name}.component.hpp', 'w') as f:
        f.write(component_template_h)

    with open(f'src/{folder}/src/components/{name}.component.cpp', 'w') as f:
        f.write(component_template_cpp)

    with open(f'src/{folder}/cmake/components.cmake', 'a') as f:
        f.write(
            f'''include_component({folder}/components/{name}.component.hpp src/components/{name}.component.cpp {namespace}::{pascal_case_name}Component)\n''')

    print(f'Generated component {name}')

if __name__ == '__main__':
    parser = ArgumentParser(description='Missile Toad utilities')
    parser.set_defaults(func=lambda _: parser.print_help())

    subparsers = parser.add_subparsers(help='Sub commands')

    # Generate system
    parser_generate_system = subparsers.add_parser('system', help='Generate a new system', aliases=['s', 'sys'])
    parser_generate_system.add_argument('folder', help='Folder where the system will be generated')
    parser_generate_system.add_argument('name', help='System name in snake_case')
    parser_generate_system.set_defaults(func=generate_system)

    # Generate component
    parser_generate_component = subparsers.add_parser('component', help='Generate a new component',
                                                      aliases=['c', 'comp'])
    parser_generate_component.add_argument('folder', help='Folder where the component will be generated')
    parser_generate_component.add_argument('name', help='Component name in snake_case')
    parser_generate_component.set_defaults(func=generate_component)

    args = parser.parse_args(sys.argv[1:])
    args.func(args)
