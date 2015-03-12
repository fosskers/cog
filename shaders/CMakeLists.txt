add_library(cogs shaders.c)

target_include_directories(cogs PUBLIC $(CMAKE_CURRENT_SOURCE_FILE))
