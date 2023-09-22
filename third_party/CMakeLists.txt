##################################################################
# Third party modules that don't come with a CMakelists.txt file #
##################################################################

# Raygui
add_library(nuklear-gui STATIC nuklear/src/nuklear.cpp)
target_link_libraries(nuklear-gui PUBLIC raylib raylib_nuklear)

add_library(nuklear::nuklear ALIAS nuklear-gui)

add_library(rapidjson INTERFACE)
target_include_directories(rapidjson SYSTEM INTERFACE ${RAPIDJSON_INCLUDE_DIRS})
