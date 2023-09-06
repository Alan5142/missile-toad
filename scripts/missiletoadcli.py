from argparse import ArgumentParser, Namespace
import sys

# Utilities scripts for missiletoad
# It contains the following scripts:
# - generate_component: Generate a new component

def generate_system(name_nms:Namespace):
    name:str = name_nms.name
    if not name:
        print('System name is required')
        return
    if not name.islower():
        print('System name must be in snake_case')
        return
    
    print(f'Generating system {name}')
    
    # Convert snake_case to PascalCase
    pascal_case_name = ''.join([word.capitalize() for word in name.split('_')])
    
    component_template_h = f'''
#include "missile_toad/base_system.hpp"
#include "missile_toad/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{{
    class {pascal_case_name}System : public missiletoad::BaseSystem
    {{
    public:
        static void register_system(entt::meta_ctx& ctx);
    }};
}}
'''

    component_template_cpp = f'''
#include "missile_toad/systems/{name}.system.hpp"
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>


void missiletoad::{pascal_case_name}System::register_system(entt::meta_ctx &ctx)
{{
    using namespace entt::literals;
    entt::meta<missiletoad::{pascal_case_name}System>(ctx)
            .type("missiletoad::{pascal_case_name}System"_hs)
            .base<missiletoad::BaseSystem>()
            .ctor<>();
}}'''

    with open(f'missile_toad/include/missile_toad/systems/{name}.system.hpp', 'w') as f:
        f.write(component_template_h)
    
    with open(f'missile_toad/src/systems/{name}.system.cpp', 'w') as f:
        f.write(component_template_cpp)
        
    with open(f'missile_toad/cmake/systems.cmake', 'a') as f:
        f.write(f'''include_system(missile_toad/systems/{name}.system.hpp src/systems/{name}.system.cpp missiletoad::{pascal_case_name}System)''')
        
    print(f'Generated system {name}')

if __name__ == '__main__':
    parser = ArgumentParser(description='Missile Toad utilities')
    parser.set_defaults(func=lambda _: parser.print_help())
    
    subparsers = parser.add_subparsers(help='Sub commands')
    
    # Generate component
    parser_generate_component = subparsers.add_parser('system', help='Generate a new system')
    parser_generate_component.add_argument('name', help='System name in snake_case')
    parser_generate_component.set_defaults(func=generate_system)
    
    args = parser.parse_args(sys.argv[1:])
    args.func(args)
    
        
    
    
    