//TODO
// - fix lighting and look of it
#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const std::string TITLE{"light test 01"};

static const float CAMERA_Y{-4.5f};
static const float CAMERA_Z{6.7f};
static const float CAMERA_ROTATION_X{0.55f};

static const float SPECULAR_EXPONENT{4.5f};
static const glm::vec3 POSITION_PLANE{0.0f, 0.0f, -2.0f};
static const float LENGTH_PLANE_SIDE{75.0f};
static const unsigned int VERTEX_COUNT_PLANE{200};

static const float RADIUS_SPHERE{0.7f};
static const unsigned int RING_COUNT_SPHERE{100};
static const unsigned int VERTEX_COUNT_SPHERE{100};

static const float BODY_RADIUS_LIGHT{0.1f};
static const float INTENSITY_LIGHT{0.3f};
static const unsigned int RING_COUNT_LIGHT{30};
static const unsigned int VERTEX_COUNT_LIGHT{30};

static const std::vector<glm::vec4> COLOR_PLANE{color::WHITE};
static const std::vector<glm::vec4> COLOR_PHONG_SPHERE{color::LIGHT_GRAY};

static const float ROTATION_SPEED_LIGHT_1{0.01f};
static const float ROTATION_SPEED_LIGHT_2{-0.0125f};
static const float ROTATION_SPEED_LIGHT_3{0.015f};
static const float Z_VALUE_LIGHTS{1.5f};
static const float RADIUS_LIGHT_1{2.0f};
static const float RADIUS_LIGHT_2{3.5f};
static const float RADIUS_LIGHT_3{4.0f};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;
    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    auto phong_material = std::make_shared<ES2PhongMaterial>();
    phong_material->set_specular_exponent(SPECULAR_EXPONENT);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    Sphere_Data sphere_data = {RADIUS_SPHERE, VERTEX_COUNT_SPHERE,
                               RING_COUNT_SPHERE};
    Mesh_Data sphere_mesh_data = {phong_material, COLOR_PHONG_SPHERE, "phong sphere",
                                  Geometry::Type::TriangleStrip};
    auto phong_sphere = generate_sphere_mesh(sphere_data, sphere_mesh_data);

    Square_Data square_data = {LENGTH_PLANE_SIDE, VERTEX_COUNT_PLANE};
    Mesh_Data square_mesh_data = {phong_material, COLOR_PLANE, "phong plane",
                                  Geometry::Type::Triangles, POSITION_PLANE};
    auto phong_plane = generate_square_mesh(square_data, square_mesh_data);

    Sphere_Data lamp_base = {BODY_RADIUS_LIGHT, VERTEX_COUNT_LIGHT,
                             RING_COUNT_LIGHT};
    Mesh_Data lamp_mesh_base_red = {constant_material,
                                    std::vector<glm::vec4>{color::RED}, "lamp base",
                                    Geometry::Type::TriangleStrip};
    Mesh_Data lamp_mesh_base_green = {constant_material,
                                      std::vector<glm::vec4>{color::GREEN},
                                      "lamp base", Geometry::Type::TriangleStrip};
    Mesh_Data lamp_mesh_base_blue = {constant_material,
                                     std::vector<glm::vec4>{color::BLUE},
                                     "lamp base", Geometry::Type::TriangleStrip};

    std::vector<std::shared_ptr<Object>> objects{phong_plane, phong_sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();

    camera->set_z(CAMERA_Z);
    camera->set_y(CAMERA_Y);
    camera->set_rotation_x(CAMERA_ROTATION_X);

    scene->get_directional_lights().clear();
    scene->get_point_lights().clear();

    auto point_light1 = generate_point_light(scene, lamp_base, lamp_mesh_base_red,
                                             INTENSITY_LIGHT);
    point_light1->set_ambient_color(color::RED);
    auto point_light2 = generate_point_light(scene, lamp_base, lamp_mesh_base_green,
                                             INTENSITY_LIGHT);
    point_light2->set_ambient_color(color::GREEN);
    auto point_light3 = generate_point_light(scene, lamp_base, lamp_mesh_base_blue,
                                             INTENSITY_LIGHT);
    point_light3->set_ambient_color(color::BLUE);

    helper_functions::set_camera(camera);
    window->set_on_key_down(process_keystrokes);

    // offset starting angles
    static float angle_light_1 = 0;
    static float angle_light_2 = 2.0f * M_PI / 3.0f;
    static float angle_light_3 = 4.0f * M_PI / 3.0f;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        point_light1->set_position(
                glm::vec3(RADIUS_LIGHT_1 * cos(angle_light_1),
                          RADIUS_LIGHT_1 * sin(angle_light_1),
                          Z_VALUE_LIGHTS));
        angle_light_1 += ROTATION_SPEED_LIGHT_1;
        point_light2->set_position(
                glm::vec3(RADIUS_LIGHT_2 * cos(angle_light_2),
                          RADIUS_LIGHT_2 * sin(angle_light_2),
                          Z_VALUE_LIGHTS));
        angle_light_2 += ROTATION_SPEED_LIGHT_2;
        point_light3->set_position(
                glm::vec3(RADIUS_LIGHT_3 * cos(angle_light_3),
                          RADIUS_LIGHT_3 * sin(angle_light_3),
                          Z_VALUE_LIGHTS));
        angle_light_3 += ROTATION_SPEED_LIGHT_3;
        renderer.render();
    }
}
