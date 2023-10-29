# ##############################################################################
# __  __ _         _ _        _____             _                              #
# |  \/  (_)___ ___(_) | ___  | ____|_ __   __ _(_)_ __   ___                  #
# | |\/| | / __/ __| | |/ _ \ |  _| | '_ \ / _` | | '_ \ / _ \                 #
# | |  | | \__ \__ \ | |  __/ | |___| | | | (_| | | | | |  __/                 #
# |_|  |_|_|___/___/_|_|\___| |_____|_| |_|\__, |_|_| |_|\___|                 #
#                                          |___/                               #
# ##############################################################################

clean_systems_and_components()

include(cmake/systems.cmake)
include(cmake/components.cmake)

message(STATUS "Systems to include ${SYSTEMS}")
message(STATUS "Components to include ${COMPONENTS}")

generate_components(missileengine)
generate_systems(missileengine)

set(MISSILETOAD_CORE_SOURCES
    src/asset_manager.cpp
    src/texture.cpp
    src/texture_loader.cpp
    src/music.cpp
    src/music_loader.cpp
    src/game.cpp
    src/common.cpp
    src/scene.cpp
    src/timer.cpp
    src/game_descriptor.cpp
    src/scene_descriptor.cpp
    src/game_register.cpp
    src/scene_manager.cpp
    src/input_manager.cpp
    src/ldtk_loader.cpp)

set(MISSILETOAD_CORE_LIBS
    raylib
    raylib_cpp
    fmt::fmt
    physfs-static
    Microsoft.GSL::GSL
    box2d
    nuklear::nuklear
    glm::glm
    EnTT::EnTT
    spdlog::spdlog_header_only
    LDtkLoader
    rapidjson)

set(MISSILEENGINE_SOURCES
    ${MISSILETOAD_CORE_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/systems.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/components.cpp ${SYSTEMS_SOURCE_FILES}
    ${COMPONENTS_SOURCE_FILES})

add_library(missileengine ${MISSILEENGINE_SOURCES})
add_library(missiletoad::engine-lib ALIAS missileengine)
add_library(missileengine-main STATIC main.cpp)
add_library(missiletoad::engine ALIAS missileengine-main)

target_link_libraries(missileengine PUBLIC ${MISSILETOAD_CORE_LIBS})
target_link_libraries(missileengine-main PUBLIC missileengine)

# Workaround for RapidJSON include path
target_include_directories(missileengine PUBLIC include)

if(${PLATFORM} EQUAL "Nintendo Switch")
  set_target_properties(missileengine PROPERTIES LINK_DEPENDS
                                                 ${DEVKITPRO}/libnx/switch.ld)
endif()

if(MSVC)
  target_compile_options(missileengine PRIVATE /W4 /WX)
else()
  target_compile_options(missileengine PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
