#!/bin/bash

# Creating directories and files

mkdir "./$1"
mkdir "./$1/build/"
touch "./$1/$1.cpp" "./$1/CMakeLists.txt" 

# Adding content to CMakeLists.txt

echo "project($1)

cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_STANDARD 17)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(GL REQUIRED gl)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLM REQUIRED glm)

include_directories(
    \${SDL2_INCLUDE_DIRS} 
    \${GL_INCLUDE_DIRS} 
    \${GLEW_INCLUDE_DIRS} 
    \${GLM_INCLUDE_DIRS}
    \"./include\"
)

set(AUR_SOURCES 
    include/scene/scene.hpp
    include/objects/object.hpp
    include/objects/camera.hpp
    include/objects/mesh.hpp
    include/geometries/vertex.hpp
    include/geometries/geometry.hpp
    include/geometries/es2_geometry.hpp
    include/geometries/geometry_generators.hpp
    include/materials/material.hpp
    include/materials/constant_material.hpp
    include/materials/es2_constant_material.hpp
    include/materials/phong_material.hpp
    include/materials/es2_phong_material.hpp
    include/lights/ambient_light.hpp
    include/lights/light.hpp
    include/lights/directional_light.hpp
    include/lights/point_light.hpp
    include/lights/spot_light.hpp
    include/textures/texture.hpp
    include/textures/es2_texture.hpp
    include/renderer/renderer.hpp
    include/renderer/es2_renderer.hpp
    include/renderer/shader.hpp
    include/renderer/es2_shader.hpp
    include/window/window.hpp
    include/window/sdl_window.hpp
    include/utilities/utilities.hpp
    include/aur.hpp
) 

add_executable(
    $1 
    \${AUR_SOURCES} 
    $1.cpp
)

target_link_libraries(
    $1 
    \${SDL2_LIBRARIES} 
    \${GL_LIBRARIES} 
    \${GLEW_LIBRARIES} 
    \${GLM_LIBRARIES}
)
" > "./$1/CMakeLists.txt"
