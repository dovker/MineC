   
cmake_minimum_required(VERSION 3.5)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "x64")
else()
set(ARCH_DIR "x86")
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/SDL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/glad)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/cglm)

set_target_properties (Glad PROPERTIES
    FOLDER Dependencies
)
set_target_properties (cglm PROPERTIES
    FOLDER Dependencies
)
set_target_properties (SDL2-static PROPERTIES
    FOLDER Dependencies
)
set_target_properties (SDL2 PROPERTIES
    FOLDER Dependencies
)
set_target_properties (uninstall PROPERTIES
    FOLDER Dependencies
)
set_target_properties (SDL2main PROPERTIES
    FOLDER Dependencies
)

set(MC_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/SDL/include
    ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/cglm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/stb_image/include)

set(MC_LINK_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/SDL
                   ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/glad
                   ${CMAKE_CURRENT_SOURCE_DIR}/MineC/thirdparty/cglm)

set(MC_WORKSPACE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(MineC)