#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const float PLANE_ROT_SPEED{0.001f};

static const std::string TITLE{"textured plane test"};

static const unsigned int SEGMENT_COUNT{2};
static const float PLANE_1_WIDTH{5.0f};
static const float PLANE_1_HEIGHT{3.0f};
static const float PLANE_2_WIDTH{100.0f};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;

    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    //changed, TODO: change back
    auto texture1 = generate_texture(paths::CITY_TEXTURE);
    auto plane1_material = std::make_shared<ES2PhongMaterial>();
    plane1_material->set_texture_1(texture1);
    plane1_material->set_specular_exponent(20.0f);
    plane1_material->set_face_culling_enabled(false);

    Rectangle_Data plane1_data = {PLANE_1_WIDTH, PLANE_1_HEIGHT, SEGMENT_COUNT,
                                  SEGMENT_COUNT};
    Mesh_Data plane1_mesh_data = {plane1_material};
    auto plane1 = generate_rectangle_mesh(plane1_data, plane1_mesh_data);

    auto texture2 = generate_texture(paths::CHECKERBOARD_TEXTURE);
    auto texture3 = generate_texture(paths::CITY_TEXTURE);
    auto plane2_material = std::make_shared<ES2PhongMaterial>();
    plane2_material->set_texture_1(texture2);
    plane2_material->set_texture_2(texture3);
    plane2_material->set_specular_exponent(20.0f);

    Square_Data plane2_data = {PLANE_2_WIDTH, SEGMENT_COUNT};
    Mesh_Data plane2_mesh_data = {plane2_material};
    auto plane2 = generate_square_mesh(plane2_data, plane2_mesh_data);

    plane2->set_position(glm::vec3{0.0f, -10.0f, -50.0f});
    plane2->set_rotation_x(-M_PI / 2);

    std::vector<std::shared_ptr<Object>> objects{plane1, plane2};
    auto scene = std::make_shared<Scene>(objects);

    Point_Light_Data point_light_data1 = {0.86f, glm::vec3{0.0f, 2.0f, 10.0f}};
    Point_Light_Data point_light_data2 = {0.75f, glm::vec3{0.0f, 2.0f, 10.0f}};

    auto point_light1 = generate_point_light(point_light_data1);
    auto point_light2 = generate_point_light(point_light_data2);

    scene->get_point_lights().push_back(point_light1);
    scene->get_point_lights().push_back(point_light2);

    auto camera = scene->get_camera();
    camera->set_z(8.0f);

    helper_functions::set_camera(camera);
    window->set_on_key_down(process_keystrokes);

    Texture_Data texture1_data;
    bool plane1_rotation_enabled{false};
    glm::vec4 diffuse_color1{plane1_material->get_diffuse_color()};

    Texture_Data texture2_data;
    bool plane2_rotation_enabled{false};
    glm::vec4 diffuse_color2{plane2_material->get_diffuse_color()};

    Texture_Data texture3_data;
    texture3_data.enabled = false;
    texture3_data.texturing_mode = Texture::Mode::Addition;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Parameters", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            helper_functions::create_texture_box("City Texture Small", "1",
                                                 &texture1_data, diffuse_color1,
                                                 plane1_rotation_enabled);
            helper_functions::create_texture_box("Checkerboard Texture", "2",
                                                 &texture2_data, diffuse_color2,
                                                 plane2_rotation_enabled);
            helper_functions::create_texture_box("City Texture Big", "3",
                                                 &texture3_data);
        }
        ImGui::End();

        if (plane1_rotation_enabled) {
            plane1->add_to_rotation_y(PLANE_ROT_SPEED);
        }
        plane1_material->set_diffuse_color(diffuse_color1);
        set_texture_attributes(texture1, &texture1_data);

        if (plane2_rotation_enabled) {
            plane2->add_to_rotation_y(PLANE_ROT_SPEED);
        }
        plane2_material->set_diffuse_color(diffuse_color2);
        set_texture_attributes(texture2, &texture2_data);

        set_texture_attributes(texture3, &texture3_data);

        renderer.render();
    }
}