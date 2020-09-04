project(final_project)

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
        include/geometries/tangent_space_math.hpp
        include/materials/material.hpp
        include/materials/constant_material.hpp
        include/materials/es2_constant_material.hpp
        include/materials/phong_material.hpp
        include/materials/es2_phong_material.hpp
        include/math/plane.hpp
        include/math/ray.hpp
        include/math/sphere.hpp
        include/math/aabb.hpp
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
        include/vendor/imgui_impl_sdl.h
        include/vendor/imgui_impl_opengl.h
        include/window/sdl_window.hpp
        include/utilities/utilities.hpp

        include/constants/numbers.hpp
        include/constants/colors.hpp
        include/constants/paths.hpp

        include/helper_functions/helper_structs.hpp
        include/helper_functions/mesh_generators.hpp
        include/helper_functions/mesh_group_generators.hpp
        include/helper_functions/light_generators.hpp
        include/helper_functions/texture_generators.hpp
        include/helper_functions/movement_control.hpp
        include/helper_functions/imgui_helper.hpp
        include/helper_functions/material_helper.hpp
        include/helper_functions/fps_counter.hpp
        include/helper_functions/spawn_enemies.hpp

        include/imgui/imconfig.h
        include/imgui/imgui.cpp
        include/imgui/imgui.h
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_internal.h
        include/imgui/imgui_widgets.cpp
        include/imgui/imstb_rectpack.h
        include/imgui/imstb_textedit.h
        include/imgui/imstb_truetype.h

        include/game_modules/game_state.hpp
        include/game_modules/01_window_test.hpp
        include/game_modules/02_triangle_test.hpp
        include/game_modules/03_geometry_test.hpp

        include/game_characters/entity.hpp
        include/game_characters/enemy.hpp
        include/game_characters/player.hpp
        include/game_characters/head.hpp
        include/game_characters/cpos.hpp

        include/helpers.hpp
        include/constants.hpp
        include/game_modules.hpp
        include/characters.hpp

        include/aur.hpp
        )

add_executable(00_main ${AUR_SOURCES} tests/00_main.cpp)
target_link_libraries(
        00_main
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)


add_executable(01_window_test ${AUR_SOURCES} tests/01_window_test.cpp)
target_link_libraries(
        01_window_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(02_triangle_test ${AUR_SOURCES} tests/02_triangle_test.cpp)
target_link_libraries(
        02_triangle_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(03_geometry_test ${AUR_SOURCES} tests/03_geometry_test.cpp)
target_link_libraries(
        03_geometry_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(04_scene_graph_test ${AUR_SOURCES} tests/04_scene_graph_test.cpp)
target_link_libraries(
        04_scene_graph_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(05_01_light_test ${AUR_SOURCES} tests/05_01_light_test.cpp)
target_link_libraries(
        05_01_light_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(05_02_light_test ${AUR_SOURCES} tests/05_02_light_test.cpp)
target_link_libraries(
        05_02_light_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(06_texture_test ${AUR_SOURCES} tests/06_texture_test.cpp)
target_link_libraries(
        06_texture_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(07_textured_plane_test ${AUR_SOURCES} tests/07_textured_plane_test.cpp)
target_link_libraries(
        07_textured_plane_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(08_material_properties_test ${AUR_SOURCES} tests/08_material_properties_test.cpp)
target_link_libraries(
        08_material_properties_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(09_01_normal_mapping_test ${AUR_SOURCES} tests/09_01_normal_mapping_test.cpp)
target_link_libraries(
        09_01_normal_mapping_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(09_02_normal_mapping_test ${AUR_SOURCES} tests/09_02_normal_mapping_test.cpp)
target_link_libraries(
        09_02_normal_mapping_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)

add_executable(10_game_test ${AUR_SOURCES} tests/10_game_test.cpp)
target_link_libraries(
        10_game_test
        ${SDL2_LIBRARIES}
        ${SDL2-IMAGE_LIBRARIES}
        ${GL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
)
