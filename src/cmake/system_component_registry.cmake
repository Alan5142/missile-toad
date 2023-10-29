set(SYSTEMS "")
set(SYSTEMS_INCLUDES "")
set(SYSTEMS_SOURCE_FILES "")

# This function adds an ECS system to the project. It generates reflection code
# for the system and adds it to the list of systems. Arguments: include: The
# include file for the system. name: System name. It must include the namespace.
# Example: "missiletoad::systems::physics".
function(include_system include source name)
  # Add the system to the list of systems.
  set(SYSTEMS
      ${SYSTEMS} ${name}
      PARENT_SCOPE)
  set(SYSTEMS_INCLUDES
      ${SYSTEMS_INCLUDES} "#include \"${include}\""
      PARENT_SCOPE)
  set(SYSTEMS_SOURCE_FILES
      ${SYSTEMS_SOURCE_FILES} ${source}
      PARENT_SCOPE)
endfunction()

function(generate_systems prefix)
  set(SYSTEM_GENERATED_FILES
      "\
#include <entt/meta/factory.hpp>\n\
#include <missile_engine/common.hpp>\n\
#include <entt/meta/meta.hpp>\n")

  foreach(SYSTEM_INCLUDE ${SYSTEMS_INCLUDES})
    set(SYSTEM_GENERATED_FILES "${SYSTEM_GENERATED_FILES}\n${SYSTEM_INCLUDE}")
  endforeach()

  set(SYSTEM_GENERATED_FILES "${SYSTEM_GENERATED_FILES}\n\
void ${prefix}_register_system(entt::meta_ctx& ctx)\n{\n")

  # Generate the reflection code for the systems. It must generate a function
  # that calls the static function "register_system" of the system.
  foreach(SYSTEM ${SYSTEMS})
    set(SYSTEM_GENERATED_FILES
        "${SYSTEM_GENERATED_FILES}    ${SYSTEM}::register_system(ctx);\n")
  endforeach()
  # Check if len of SYSTEMS is 0
  if(NOT SYSTEMS)
    set(SYSTEM_GENERATED_FILES "${SYSTEM_GENERATED_FILES}    unused(ctx);\n")
  endif()
  set(SYSTEM_GENERATED_FILES "${SYSTEM_GENERATED_FILES}}\n")

  # Write the generated code to a file.
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/systems.cpp"
       "${SYSTEM_GENERATED_FILES}")
endfunction()

set(COMPONENTS "")
set(COMPONENTS_INCLUDES "")
set(COMPONENTS_SOURCE_FILES "")

# This function adds an ECS system to the project. It generates reflection code
# for the system and adds it to the list of systems. Arguments: include: The
# include file for the system. name: System name. It must include the namespace.
# Example: "missiletoad::systems::physics".
function(include_component include source name)
  # Add the system to the list of systems.
  set(COMPONENTS
      ${COMPONENTS} ${name}
      PARENT_SCOPE)
  set(COMPONENTS_INCLUDES
      ${COMPONENTS_INCLUDES} "#include \"${include}\""
      PARENT_SCOPE)
  set(COMPONENTS_SOURCE_FILES
      ${COMPONENTS_SOURCE_FILES} ${source}
      PARENT_SCOPE)
endfunction()

function(generate_components prefix)
  set(COMPONENTS_GENERATED_FILES
      "\
#include <entt/meta/factory.hpp>\n\
#include <missile_engine/common.hpp>\n\
#include <entt/meta/meta.hpp>\n")

  foreach(COMPONENTS_INCLUDE ${COMPONENTS_INCLUDES})
    set(COMPONENTS_GENERATED_FILES
        "${COMPONENTS_GENERATED_FILES}\n${COMPONENTS_INCLUDE}")
  endforeach()

  set(COMPONENTS_GENERATED_FILES "${COMPONENTS_GENERATED_FILES}\n\
void ${prefix}_register_components(entt::meta_ctx& ctx)\n{\n")

  # Generate the reflection code for the systems. It must generate a function
  # that calls the static function "register_system" of the system.
  foreach(COMPONENT ${COMPONENTS})
    set(COMPONENTS_GENERATED_FILES
        "${COMPONENTS_GENERATED_FILES}    ${COMPONENT}::register_component(ctx);\n"
    )
  endforeach()
  # Check if len of SYSTEMS is 0
  if(NOT COMPONENTS)
    set(COMPONENTS_GENERATED_FILES
        "${COMPONENTS_GENERATED_FILES}    unused(ctx);\n")
  endif()
  set(COMPONENTS_GENERATED_FILES "${COMPONENTS_GENERATED_FILES}}\n")

  # Write the generated code to a file.
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/components.cpp"
       "${COMPONENTS_GENERATED_FILES}")
endfunction()

function(clean_systems_and_components)
  set(SYSTEMS "")
  set(SYSTEMS_INCLUDES "")
  set(SYSTEMS_SOURCE_FILES "")
  set(COMPONENTS "")
  set(COMPONENTS_INCLUDES "")
  set(COMPONENTS_SOURCE_FILES "")
endfunction()
