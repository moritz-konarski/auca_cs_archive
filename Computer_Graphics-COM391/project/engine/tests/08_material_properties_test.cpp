#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const float PLANE_ROT_SPEED{0.001f};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;

    auto window = std::make_shared<SDLWindow>("aur", constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    auto plane1_material = std::make_shared<ES2PhongMaterial>();
    auto plane_texture = generate_texture(paths::CHECKERBOARD_TEXTURE);
    plane1_material->set_texture_1(plane_texture);

    Square_Data square_data = {20.0f, 2};
    Mesh_Data square_mesh_data1 = {plane1_material};

    auto plane1 = generate_square_mesh(square_data, square_mesh_data1);
    plane1->set_position(glm::vec3(0.0f, 0.0f, -10.0f));


    auto plane2_material = std::make_shared<ES2PhongMaterial>();
    plane2_material->set_texture_1(plane_texture);
    plane2_material->set_emission_color(
            glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));

    Mesh_Data square_mesh_data2 = {plane2_material};
    auto plane2 = generate_square_mesh(square_data, square_mesh_data2);

    plane2->set_position(glm::vec3(0.0f, -10.0f, 0.0f));
    plane2->set_rotation(glm::vec3(-M_PI / 2, 0.0f, 0.0f));


    auto sphere_material = std::make_shared<ES2PhongMaterial>();
    sphere_material->set_diffuse_color(color::RED);
    sphere_material->set_specular_exponent(40.f);
    Sphere_Data sphere_data = {1.0f, 20, 20};
    Mesh_Data sphere_mesh_data = {sphere_material};

    auto sphere_texture = generate_texture(paths::CHECKERBOARD_TEXTURE);
    sphere_material->set_texture_1(sphere_texture);
    auto sphere = generate_sphere_mesh(sphere_data, sphere_mesh_data);

    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    sphere_data.radius = 0.2f;
    sphere_mesh_data.material = {lamp_material};
    lamp_material->set_emission_color(color::WHITE);
    auto lamp1 = generate_sphere_mesh(sphere_data, sphere_mesh_data);
    auto lamp2 = generate_sphere_mesh(sphere_data, sphere_mesh_data);

    std::vector<std::shared_ptr<Object>> objects{plane1, plane2, sphere};
    auto scene = std::make_shared<Scene>(objects);

    Point_Light_Data point_light_data = {0.45f,
                                         glm::vec3{0.0f, 2.0f, 10.0f}};

    auto point_light1 = generate_point_light(point_light_data);
    auto point_light2 = generate_point_light(point_light_data);
    point_light1->add_child(lamp1);
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light1);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light1);
    scene->get_point_lights().push_back(point_light2);

    auto camera = scene->get_camera();
    camera->set_z(8.0f);

    helper_functions::set_camera(camera);
    window->set_on_key_down(process_keystrokes);

    bool plane1_rotation_enabled{false};
    glm::vec4 plane1_emission_color{plane1_material->get_emission_color()};
    Texture_Data plane_texture_data;
    Texture_Data sphere_texture_data = {false};

    float sphere_z = sphere->get_z();

    Material_Data sphere_material_data;
    get_phong_material_properties(sphere_material, &sphere_material_data);

    Fog_Data fog_data;

    static float point_light_angle1 = 0.0f;
    static float point_light_angle2 = 0.0f;
    const static float point_light_radius1 = 8.0f;
    const static float point_light_radius2 = 8.5f;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Parameters", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            helper_functions::create_texture_box("Plane Texture", "1",
                                                 &plane_texture_data,
                                                 plane1_emission_color,
                                                 plane1_rotation_enabled);
            helper_functions::create_texture_box("Sphere Texture", "2",
                                                 &sphere_texture_data);

            helper_functions::create_material_box("Sphere", "3",
                                                  &sphere_material_data,
                                                  sphere_z);;

            create_fog_box("4", &fog_data);
        }
        ImGui::End();

        if (plane1_rotation_enabled) {
            plane1->add_to_rotation_y(PLANE_ROT_SPEED);
        }
        plane1_material->set_emission_color(plane1_emission_color);
        set_material_fog_properties(plane1_material, &fog_data);

        set_texture_attributes(plane_texture, &plane_texture_data);
        set_texture_attributes(sphere_texture, &sphere_texture_data);

        sphere->set_z(sphere_z);
        set_phong_material_properties(sphere_material, &sphere_material_data);
        set_material_fog_properties(sphere_material, &fog_data);

        set_material_fog_properties(plane2_material, &fog_data);

        point_light1->set_x(cosf(point_light_angle1) * point_light_radius1);
        point_light1->set_z(sinf(point_light_angle1) * point_light_radius1);

        point_light2->set_x(cosf(point_light_angle2) * point_light_radius2);
        point_light2->set_z(sinf(point_light_angle2) * point_light_radius2);

        point_light_angle1 += 0.01f;
        point_light_angle2 -= 0.01f;

        renderer.render();
    }
}
