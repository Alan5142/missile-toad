cmake_minimum_required(VERSION 3.20)

project(Dummy)

set(CMAKE_CXX_STANDARD 20)

include(cmake/CPM.cmake)

CPMUsePackageLock(package-lock.cmake)

include(cmake/dependencies.cmake)

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Set library output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(missile_toad)