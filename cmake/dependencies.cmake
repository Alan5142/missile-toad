# Raylib
CPMAddPackage("https://github.com/Alan5142/raylib-nx.git#9b47785")

# Raylib cpp
CPMAddPackage("https://github.com/RobLoach/raylib-cpp.git#bf0be19")

# Catch2
CPMAddPackage("https://github.com/catchorg/Catch2.git@3.4.0")

# fmt
CPMAddPackage("https://github.com/fmtlib/fmt.git#10.1.0")

# GSL
CPMAddPackage("https://github.com/microsoft/GSL.git#4300304")

# ENTT
CPMAddPackage("https://github.com/skypjack/entt.git@3.12.2")

# Raylib-nuklear
CPMAddPackage("https://github.com/RobLoach/raylib-nuklear.git#988c447")

# GLM
CPMAddPackage("https://github.com/g-truc/glm.git#47585fd")

# spdlog
CPMAddPackage("https://github.com/gabime/spdlog.git@1.12.0")

# LDtk
CPMAddPackage("https://github.com/Madour/LDtkLoader.git#1.2.2")



# Box2D options
set(BOX2D_BUILD_UNIT_TESTS OFF)
set(BOX2D_BUILD_TESTBED OFF)

# Box2D
CPMAddPackage("https://github.com/erincatto/box2d.git#411acc3")

# RapidJSON options
set(RAPIDJSON_BUILD_DOC OFF)
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_TESTS OFF)
set(RAPIDJSON_BUILD_CXX17 ON)

# RapidJSON
CPMAddPackage("https://github.com/Tencent/rapidjson.git#b4a6da3")

# Check if RapidJSON is found
if (NOT TARGET RapidJSON)
    message(FATAL_ERROR "RapidJSON not found")
endif ()

# Set the target include directories to the target directory
get_target_property(RAPIDJSON_SOURCE_DIR RapidJSON SOURCE_DIR)
set(RAPIDJSON_INCLUDE_DIRS ${RAPIDJSON_SOURCE_DIR}/include)

# Set PhysFS to only build static library
set(PHYSFS_BUILD_SHARED OFF)
set(PHYSFS_BUILD_DOCS OFF)
set(PHYSFS_BUILD_TEST OFF)

# PhysFS
CPMAddPackage("https://github.com/Alan5142/physfs-nx.git#e616454")

# Disable all warnings for raylib and physfs
if (MSVC)
    target_compile_options(raylib PRIVATE /W0)
    target_compile_options(physfs-static PRIVATE /W0)
    set_target_properties(raylib_cpp PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:raylib_cpp,INTERFACE_INCLUDE_DIRECTORIES>)
else ()
    target_compile_options(raylib PRIVATE -w)
    target_compile_options(physfs-static PRIVATE -w)
endif ()

# Disable shared libraries for physfs
set(PHYSFS_BUILD_SHARED OFF)
