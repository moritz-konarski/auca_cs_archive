project(lab_07_01)

cmake_minimum_required(VERSION 2.8.0)

set(CMAKE_CXX_STANDARD 17)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(GL REQUIRED gl)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLM REQUIRED glm)
pkg_search_module(SDL2-IMAGE REQUIRED SDL2_image)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2-IMAGE_INCLUDE_DIRS}
        ${GL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        "./include"
        "./tests"
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
        include/geometries/mesh_generators.hpp
        include/geometries/mesh_group_generators.hpp
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
        include/lights/light_generators.hpp
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
        01_window_test
        ${AUR_SOURCES}
        tests/01_window_test.cpp
)

target_link_libraries(
        01_window_test
        ${SDL2_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(
        02_triangle_test
        ${AUR_SOURCES}
        tests/02_triangle_test.cpp)
target_link_libraries(
        02_triangle_test
        ${SDL2_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(
        03_geometry_test
        ${AUR_SOURCES}
        tests/03_geometry_test.cpp)
target_link_libraries(
        03_geometry_test
        ${SDL2_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(
        04_scene_graph_test
        ${AUR_SOURCES}
        tests/04_scene_graph_test.cpp)
target_link_libraries(
        04_scene_graph_test
        ${SDL2_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(
        05_01_light_test
        ${AUR_SOURCES}
        tests/05_01_light_test.cpp)
target_link_libraries(
        05_01_light_test
        ${SDL2_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(
        05_02_light_test
        ${AUR_SOURCES}
        tests/05_02_light_test.cpp)
target_link_libraries(
        05_02_light_test
        ${SDL2_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(
        06_01_texture_test
        ${AUR_SOURCES}
        tests/06_01_texture_test.cpp)
target_link_libraries(
        06_01_texture_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)
