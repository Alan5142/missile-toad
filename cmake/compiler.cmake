
# On MSVC set entry point to mainCRTStartup to avoid a console window
if (MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif ()

# For release builds, add LTO
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (MSVC)
        add_compile_options(/GL)
        add_link_options(/LTCG)
    else ()
        add_compile_options(-flto)
        add_link_options(-flto)
    endif ()
endif ()
