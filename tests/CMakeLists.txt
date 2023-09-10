# Missile toad tests

## Running the tests

set(TEST_SOURCES src/core/resource_ptr.cpp)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE missiletoad Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE include)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
catch_discover_tests(tests)
