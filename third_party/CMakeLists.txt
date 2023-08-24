##################################################################
# Third party modules that don't come with a CMakelists.txt file #
##################################################################

# Raygui
add_library(raygui INTERFACE)
target_include_directories(raygui SYSTEM INTERFACE raygui/src)