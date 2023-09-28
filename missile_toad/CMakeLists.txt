include(cmake/system_component_registry.cmake)

include(cmake/systems.cmake)
include(cmake/components.cmake)

message(STATUS "Systems to include ${SYSTEMS}")
message(STATUS "Components to include ${COMPONENTS}")

generate_systems()
generate_components()

set(MISSILETOAD_CORE_SOURCES
        src/core/asset_manager.cpp
        src/core/texture.cpp
        src/core/texture_loader.cpp
        src/core/music.cpp
        src/core/music_loader.cpp
        src/core/game.cpp
        src/core/common.cpp
        src/core/scene.cpp
        src/core/timer.cpp
        src/core/game_descriptor.cpp
        src/core/scene_descriptor.cpp
        src/core/scene_manager.cpp
        src/core/input_manager.cpp
)

set(MISSILETOAD_CORE_LIBS
        raylib
        raylib_cpp
        fmt::fmt physfs-static
        Microsoft.GSL::GSL
        box2d
        nuklear::nuklear
        glm::glm
        EnTT::EnTT
        spdlog::spdlog_header_only
        LDtkLoader
        rapidjson
)

set(MISSILETOAD_SOURCES
        ${MISSILETOAD_CORE_SOURCES}

        ${CMAKE_CURRENT_BINARY_DIR}/systems.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/components.cpp

        ${SYSTEMS_SOURCE_FILES}
        ${COMPONENTS_SOURCE_FILES}
)

add_library(missiletoad ${MISSILETOAD_SOURCES})

if (WIN32)
    add_executable(missiletoad-game WIN32 main.cpp)
else ()
    add_executable(missiletoad-game main.cpp)
endif ()

target_link_libraries(missiletoad PUBLIC ${MISSILETOAD_CORE_LIBS})
target_link_libraries(missiletoad-game PRIVATE missiletoad)

# Workaround for RapidJSON include path
target_include_directories(missiletoad PUBLIC include)

if (${PLATFORM} EQUAL "Nintendo Switch")
    set_target_properties(missiletoad PROPERTIES LINK_DEPENDS ${DEVKITPRO}/libnx/switch.ld)
endif ()

if (MSVC)
    target_compile_options(missiletoad PRIVATE /W4 /WX)
    target_compile_options(missiletoad-game PRIVATE /W4 /WX)
else ()
    target_compile_options(missiletoad PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(missiletoad-game PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()
