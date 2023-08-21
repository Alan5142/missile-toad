# Raylib
CPMAddPackage("https://github.com/Alan5142/raylib-nx.git#9b47785")

# Raylib cpp
CPMAddPackage("https://github.com/RobLoach/raylib-cpp.git#bf0be19")

# Catch2
CPMAddPackage("https://github.com/catchorg/Catch2.git@3.4.0")

# fmt
CPMAddPackage("https://github.com/fmtlib/fmt.git#10.1.0")

# PhysFS
CPMAddPackage("https://github.com/Alan5142/physfs-nx.git#switch")

# GSL
CPMAddPackage("https://github.com/microsoft/GSL.git#4300304")

# Disable all warnings for raylib and physfs
if (MSVC)
    target_compile_options(raylib PRIVATE /W0)
    target_compile_options(physfs-static PRIVATE /W0)
else ()
    target_compile_options(raylib PRIVATE -w)
    target_compile_options(physfs-static PRIVATE -w)
endif ()
