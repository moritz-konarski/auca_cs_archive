//TODO:
// - fix bugs with hit boxes
// - create a real level
// - create more enemies
// - create some kind of menu
#include "aur.hpp"
#include "helpers.hpp"
#include "characters.hpp"
#include "constants.hpp"

const static unsigned int ENEMY_COUNT{8};

enum Enemy_Type {
    Cpos,
    Head
};

std::shared_ptr<game_characters::Enemy> generate_random_enemy();

[[noreturn]]
int main(int argc, char **argv) {

    srand(time(NULL));
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("Doom Clone",
                                              constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);
    window->set_capture_mouse_enabled(true);
    window->set_relative_mouse_mode_enabled(true);

    // pos x, pos y, width, height on a normal coordinate system
    float floor_corners[4][2]{{25,  25},
                              {25,  -25},
                              {-25, -25},
                              {-25, 25}};

    auto room_ground_material = std::make_shared<ES2PhongMaterial>();
    room_ground_material->set_emission_color(color::LIGHT_GRAY);
    auto ground_texture = helper_functions::generate_texture(
            paths::GAME_FLOOR_TEXTURE);
    ground_texture->set_transformation_enabled(true);
    ground_texture->set_transformation_matrix(
            helper_functions::get_scale_matrix(5.0f));
    ground_texture->set_wrap_mode_s(Texture::WrapMode::Repeat);
    ground_texture->set_wrap_mode_t(Texture::WrapMode::Repeat);
    room_ground_material->set_texture_1(ground_texture);
    helper_functions::Square_Data square_data{50, 1};
    helper_functions::Mesh_Data mesh_data{room_ground_material};
    auto room_ground = helper_functions::generate_square_mesh(square_data,
                                                              mesh_data);
    room_ground->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    room_ground->set_rotation(glm::vec3(-M_PI / 2.0f, 0.0f, 0.0f));

    helper_functions::Rectangle_Data rectangle_data{50, 8, 1, 1};
    auto wall_material = std::make_shared<ES2PhongMaterial>();
    auto wall_texture = helper_functions::generate_texture(
            paths::GAME_WALL_TEXTURE);
    wall_texture->set_transformation_enabled(true);
    wall_texture->set_transformation_matrix(
            helper_functions::get_scale_matrix_x(5.0f));
    wall_texture->set_wrap_mode_s(Texture::WrapMode::Repeat);
    wall_texture->set_wrap_mode_t(Texture::WrapMode::Repeat);
    wall_material->set_texture_1(wall_texture);
    helper_functions::Mesh_Data rectangle_mesh_data{wall_material};
    std::vector<std::shared_ptr<Mesh>> walls;
    for (int i = 0; i < 4; ++i) {
        auto wall = helper_functions::generate_rectangle_mesh(rectangle_data,
                                                              rectangle_mesh_data);
        wall->set_position(glm::vec3{25 * cosf(i * M_PI / 2.0f), 4.0f,
                                     25 * sinf(i * M_PI / 2.0f)});
        wall->set_rotation_y(-i * M_PI / 2.0f - M_PI / 2.0f);
        walls.push_back(wall);
    }

    auto player = std::make_shared<game_characters::Player>(
            glm::vec3{0.0f, 2.5f, 23.0f});

    std::vector<std::shared_ptr<PointLight>> point_lights;
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    helper_functions::Point_Light_Data point_light_data{3000.0f};
    helper_functions::Sphere_Data sphere_data{0.5f};
    helper_functions::Mesh_Data sphere_mesh_data{lamp_material};
    for (float *floor_dimension : floor_corners) {
        point_light_data.position = glm::vec3{floor_dimension[0], 10.0f,
                                              floor_dimension[1]};
        auto point_light = helper_functions::generate_point_light(sphere_data,
                                                                  sphere_mesh_data,
                                                                  point_light_data);
        point_light->set_constant_attenuation(0.0f);
        point_light->set_linear_attenuation(0.2f);
        point_light->set_quadratic_attenuation(0.8f);
        point_lights.push_back(point_light);
    }

    std::vector<std::shared_ptr<Object>> objects{player->get_mesh(),
                                                 room_ground};

    std::vector<std::shared_ptr<game_characters::Enemy>> enemies;
    for (int i = 0; i < ENEMY_COUNT; ++i) {
        enemies.push_back(generate_random_enemy());
    }
    for (auto &enemy : enemies) {
        objects.push_back(enemy->get_mesh());
    }
    for (auto &wall: walls) {
        objects.push_back(wall);
    }

    auto scene = std::make_shared<Scene>(objects);
    for (auto &light : point_lights) {
        scene->get_root()->add_child(light);
        scene->get_point_lights().push_back(light);
    }

    auto camera = scene->get_camera();
    camera->set_zoom(3.0f);
    camera->set_position(player->get_position());

    helper_functions::set_camera(camera);
    helper_functions::set_window(window);
    helper_functions::set_player(player);

    window->set_on_key_down(helper_functions::process_keystrokes_game);

    window->set_on_mouse_down(helper_functions::process_mouse_click);

    window->set_on_mouse_move(helper_functions::process_mouse_move);

    unsigned int index = 0, attack_index = 0;
    unsigned int interval = 5;
    unsigned int attack_interval = 8;
    unsigned int pos_x_fps =
            window->get_width() - 85, pos_y = 10;

    ES2Renderer renderer(scene, window);
    for (;;) {
        ++index;
        window->poll();

        if (index % interval == 0) {
            player->advance_animation();
            if (player->is_dead()) {
                for (auto &light:point_lights) {
                    light->set_ambient_color(
                            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                }
            }
            ++attack_index;
            if (attack_index % attack_interval == 0) {
                for (auto &enemy : enemies) {
                    enemy->turn_towards_camera(camera);
                    enemy->advance_animation();
                    enemy->attack(camera->get_position());
                    player->gets_hurt(enemy->get_damage());
                }
                attack_index = 0;
            } else {
                for (auto &enemy : enemies) {
                    enemy->turn_towards_camera(camera);
                    enemy->advance_animation();
                    player->gets_hurt(enemy->get_damage());
                }
            }
            index = 0;

            if (player->is_attacking()) {
                for (auto &enemy : enemies) {
                    if (!enemy->is_dead()) {
                        auto[intersects, distance] = helper_functions::get_player_view_ray()->intersects_with_sphere(
                                enemy->get_sphere());
                        if (intersects) {
                            //enemy->get_material()->set_emission_color(color::RED);
                            enemy->gets_hurt(player->get_damage());
                        }
                    }
                }
            }
        }

        if (camera->get_x() > 23.0f) {
            camera->set_x(23.0f);
        } else if (camera->get_x() < -23.0f) {
            camera->set_x(-23.0f);
        } else if (camera->get_z() > 23.0f) {
            camera->set_z(23.0f);
        } else if (camera->get_z() < -23.0f) {
            camera->set_z(-23.0f);
        }

        helper_functions::create_fps_counter(pos_x_fps, pos_y);

        renderer.render();
    }
}

std::shared_ptr<game_characters::Enemy> generate_random_enemy() {
    glm::vec3 position = helper_functions::generate_random_glm_vec3(-23.0f, 23.0f);
    auto type = static_cast<Enemy_Type>(helper_functions::random_enemy_type(
            2));
    switch (type) {
        case Enemy_Type::Head:
            return std::make_shared<game_characters::Head>(position, 0.7f);
        case Enemy_Type::Cpos:
            return std::make_shared<game_characters::Cpos>(position, 0.7f);
    }
}
