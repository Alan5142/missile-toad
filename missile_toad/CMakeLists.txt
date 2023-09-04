set(MISSILETOAD_SOURCES
    src/dummy.cpp
    src/game.cpp
)

add_library(missiletoad ${MISSILETOAD_SOURCES})

if (WIN32)
    add_executable(missiletoad-game WIN32 main.cpp)
else()
    add_executable(missiletoad-game main.cpp)
endif()

target_link_libraries(missiletoad PUBLIC raylib raylib_cpp fmt::fmt physfs-static Microsoft.GSL::GSL box2d nuklear::nuklear glm::glm)
target_link_libraries(missiletoad-game PRIVATE missiletoad)
target_include_directories(missiletoad PUBLIC include)

if (${PLATFORM} EQUAL "Nintendo Switch")
    set_target_properties(missiletoad PROPERTIES LINK_DEPENDS ${DEVKITPRO}/libnx/switch.ld)
endif ()

if (MSVC)
    target_compile_options(missiletoad PRIVATE /W4 /WX)
    target_compile_options(missiletoad-game PRIVATE /W4 /WX)
else()
    target_compile_options(missiletoad PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(missiletoad-game PRIVATE -Wall -Wextra -pedantic -Werror)
endif()