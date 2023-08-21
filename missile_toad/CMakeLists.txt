set(MISSILETOAD_SOURCES
    src/dummy.cpp
)

add_library(libmissiletoad ${MISSILETOAD_SOURCES})

if (WIN32)
    add_executable(missiletoad WIN32 main.cpp)
else()
    add_executable(missiletoad main.cpp)
endif()

target_link_libraries(libmissiletoad PUBLIC raylib raylib_cpp fmt::fmt physfs-static Microsoft.GSL::GSL)
target_link_libraries(missiletoad PRIVATE libmissiletoad)
target_include_directories(libmissiletoad PUBLIC include)

if (${PLATFORM} EQUAL "Nintendo Switch")
    set_target_properties(missiletoad PROPERTIES LINK_DEPENDS ${DEVKITPRO}/libnx/switch.ld)
endif ()