clean_systems_and_components()
include(cmake/systems.cmake)
include(cmake/components.cmake)

message(STATUS "Systems to include ${SYSTEMS}")
message(STATUS "Components to include ${COMPONENTS}")

generate_systems(game)
generate_components(game)

set(MISSILETOAD_SOURCES ${SYSTEMS_SOURCE_FILES} ${COMPONENTS_SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/systems.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/components.cpp src/enemy_utils.cpp)

if(${CMAKE_BUILD_TYPE} STREQUAL "Release" AND MSVC)
  add_executable(missiletoad WIN32 ${MISSILETOAD_SOURCES})
else()
  add_executable(missiletoad ${MISSILETOAD_SOURCES})
endif()

target_include_directories(missiletoad PRIVATE include)

target_link_libraries(missiletoad PRIVATE missiletoad::engine sml::sml)

if(MSVC)
  target_compile_options(missiletoad PRIVATE /W4 /WX)
else()
  target_compile_options(missiletoad PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
