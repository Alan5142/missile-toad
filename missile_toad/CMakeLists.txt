set(MISSILETOAD_SOURCES
    src/main.cpp
)

if (WIN32)
    add_executable(missiletoad WIN32 ${MISSILETOAD_SOURCES})
else()
    add_executable(missiletoad ${MISSILETOAD_SOURCES})
endif()

target_link_libraries(missiletoad PRIVATE raylib raylib_cpp spdlog fmt::fmt)
