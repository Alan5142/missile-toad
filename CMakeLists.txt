cmake_minimum_required(VERSION 3.18)

project(Dummy)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

include(cmake/options.cmake)
include(cmake/CPM.cmake)

CPMUsePackageLock(package-lock.cmake)

include(cmake/dependencies.cmake)

# Set binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# Set library output directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if (CLANG_TIDY_EXE)
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else ()
        message(FATAL_ERROR "clang-tidy requested but executable not found")
    endif ()
endif ()

add_subdirectory(missile_toad)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()

add_compile_definitions(NX_USB_DEBUGGER=1)
