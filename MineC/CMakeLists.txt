cmake_minimum_required(VERSION 3.5)

project(MineC LANGUAGES C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE MC_SRC_FILES "src/*.c" 
                                 "src/*.h" 
                                 "thirdparty/stb_image/*.c"
                                 "thirdparty/stb_image/*.h")

add_executable(MineC ${MC_SRC_FILES})


target_include_directories(MineC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src 
                                PUBLIC ${MC_INCLUDE_DIRS})

add_compile_definitions(_CRT_SCURE_NO_WARNINGS)
add_compile_definitions(MC_USE_OPENGL MC_USE_SDL2 MC_DEBUG)
# IF YOU CAN SUPPORT OPENGL4.5, DEFINE MC_OPENGL_4_5

target_link_directories(MineC PRIVATE ${MC_LINK_DIRS})

target_link_libraries(MineC PUBLIC SDL2-static SDL2main cglm Glad)