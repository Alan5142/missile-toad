# Missile toad tests

# Running the tests

set(TEST_SOURCES
        src/core/timer.cpp src/core/physics.cpp
        src/core/game_descriptor.cpp
        src/core/meta_loader.cpp
        src/core/sprite_animation_component.cpp
        src/core/input_manager.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE missileengine Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE include)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(tests)
