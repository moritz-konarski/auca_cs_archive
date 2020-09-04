// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
// https://learnopengl.com/Advanced-Lighting/Normal-Mapping
#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const std::string TITLE{"normal mapping test 2"};
static const float LIGHT_Z{0.0f};
static const float LIGHT_RADIUS{0.5f};
static const float LIGHT_ROT_SPEED{0.01f};
static const float LIGHT_INTENSITY{0.4f};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;

    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    Square_Data cube_data = {1.0f, 1};
    auto normal_map_material = create_normal_map_material(paths::TEXTURE_BRICK,
                                                          paths::NORMAL_MAP_BRICK);
    Mesh_Data cube_mesh_data = {normal_map_material};
    Normal_Map_Data normal_map_data = {false, true};
    auto cube = generate_cube(glm::vec3{0.0f, 0.0f, -1.0f}, cube_data,
                              cube_mesh_data);

    std::vector<std::shared_ptr<Object>> objects{cube};
    auto scene = std::make_shared<Scene>(objects);

    Point_Light_Data light_data = {0.8f, glm::vec3{1.0f, 0.0f, LIGHT_Z}};
    Sphere_Data lamp_data = {0.01f};
    Mesh_Data lamp_mesh_data = {constant_material};

    auto point_light1 = generate_point_light(scene, lamp_data, lamp_mesh_data,
                                             LIGHT_INTENSITY);

    auto camera = scene->get_camera();
    camera->set_z(1.0f);

    helper_functions::set_camera(camera);
    window->set_on_key_down(process_keystrokes);

    static float angle = 0;
    unsigned int pos_x_fps =
            window->get_width() - 85, pos_x_settings = 10, pos_y = 10;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        ImGui::SetNextWindowPos(ImVec2(pos_x_settings, pos_y));
        ImGui::Begin("Parameters", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            helper_functions::create_texture_and_normal_map_box(
                    "Cube Texture and Normals", "1",
                    &normal_map_data);
        }
        ImGui::End();

        create_fps_counter(pos_x_fps, pos_y);

        set_normal_map_attributes(normal_map_material, normal_map_data);

        point_light1->set_position(
                glm::vec3{(LIGHT_RADIUS - 1) * cosf(angle),
                          LIGHT_RADIUS * sinf(angle),
                          LIGHT_Z});
        angle += LIGHT_ROT_SPEED;

        renderer.render();

        cube->add_to_rotation_y(M_PI / 400.0f);
        cube->add_to_rotation_x(M_PI / 400.0f);
    }
}
