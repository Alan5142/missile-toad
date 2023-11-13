cmake_minimum_required(VERSION 3.25)

project(Dummy)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

include(cmake/compiler.cmake)
include(cmake/options.cmake)
include(cmake/CPM.cmake)

cpmusepackagelock(package-lock.cmake)

include(cmake/dependencies.cmake)

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Set library output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

add_subdirectory(third_party)

add_compile_definitions(NX_USB_DEBUGGER=1)

# Add format target
file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp src/*.hpp
     tests/*.cpp tests/*.hpp)

add_custom_target(format COMMAND clang-format -style=file -i
                                 ${ALL_SOURCE_FILES})

# Add clang-tidy files
file(GLOB_RECURSE ALL_SOURCE_FILES src/*.cpp src/*.hpp
     tests/*.cpp tests/*.hpp)

# Add clang-tidy target
add_custom_target(
  tidy
  COMMAND
    python ${PROJECT_SOURCE_DIR}/scripts/run-clang-tidy.py -p
    ${CMAKE_BINARY_DIR} -config-file ${PROJECT_SOURCE_DIR}/.clang-tidy
    ${PROJECT_SOURCE_DIR}/src -quiet -header-filter=.*)

add_custom_target(
  tidy-fix
  COMMAND
    python ${PROJECT_SOURCE_DIR}/scripts/run-clang-tidy.py -p
    ${CMAKE_BINARY_DIR} -config-file ${PROJECT_SOURCE_DIR}/.clang-tidy -fix
    ${PROJECT_SOURCE_DIR}/src -quiet -header-filter=.*)
