// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
// https://learnopengl.com/Advanced-Lighting/Normal-Mapping
#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const std::string TITLE{"normal mapping test 1"};
static const float LIGHT_Z{-0.7f};
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

    auto normal_map_material = create_normal_map_material(paths::TEXTURE_BRICK,
                                                          paths::NORMAL_MAP_BRICK);

    Square_Data square_data = {2.0f, 1};
    Mesh_Data square_mesh_data = {normal_map_material};

    auto square = generate_square_mesh(square_data, square_mesh_data);
    square->set_z(-2.0f);

    std::vector<std::shared_ptr<Object>> objects{square};
    auto scene = std::make_shared<Scene>(objects);

    auto texture = generate_texture(paths::TEXTURE_BRICK);
    normal_map_material->set_texture_1(texture);
    auto normal_map = generate_texture(paths::NORMAL_MAP_BRICK);
    normal_map_material->set_texture_2(normal_map);

    Point_Light_Data light_data = {0.3f, glm::vec3{1.0f, 0.0f, LIGHT_Z}};
    Sphere_Data lamp_data = {0.01f};
    Mesh_Data lamp_mesh_data = {constant_material};
    auto point_light = generate_point_light(scene, lamp_data, lamp_mesh_data,
                                            LIGHT_INTENSITY);
    scene->get_point_lights().push_back(point_light);

    auto camera = scene->get_camera();

    helper_functions::set_camera(camera);
    window->set_on_key_down(process_keystrokes);

    Normal_Map_Data normal_map_data = {false, true};

    static float angle = 0;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Parameters", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            helper_functions::create_texture_and_normal_map_box(
                    "Plane Texture and Normals", "1",
                    &normal_map_data);
        }
        ImGui::End();

        set_normal_map_attributes(normal_map_material, normal_map_data);

        point_light->set_position(
                glm::vec3{LIGHT_RADIUS * cosf(angle), LIGHT_RADIUS * sinf(angle),
                          LIGHT_Z});
        angle += LIGHT_ROT_SPEED;

        renderer.render();
    }
}
