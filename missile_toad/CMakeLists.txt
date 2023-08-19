set(MISSILETOAD_SOURCES
    src/dummy.cpp
)

add_library(libmissiletoad ${MISSILETOAD_SOURCES})

if (WIN32)
    add_executable(missiletoad WIN32 main.cpp)
else()
    add_executable(missiletoad main.cpp)
endif()

target_link_libraries(libmissiletoad PUBLIC raylib raylib_cpp spdlog fmt::fmt)
target_link_libraries(missiletoad PRIVATE libmissiletoad)
target_include_directories(libmissiletoad PUBLIC include)