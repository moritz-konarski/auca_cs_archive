#include "aur.hpp"
#include "helper_functions/mesh_generators.hpp"
#include "helper_functions/light_generators.hpp"

// window constants
static const int WINDOW_FULL_SCREEN{0};
static const int WINDOW_SIZE{WINDOW_FULL_SCREEN};
static const std::string TITLE{"light test 01"};

// camera constants
static const float SPEED_CAMERA{0.1f};
static const float ROTATION_SPEED_CAMERA{0.05f};
static const float CAMERA_Y{-4.5f};
static const float CAMERA_Z{6.7f};
static const float CAMERA_ROTATION_X{0.55f};
static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

// phong plane constants
static const float SPECULAR_EXPONENT{4.5f};
static const glm::vec3 POSITION_PLANE{0.0f, 0.0f, -2.0f};
static const float LENGTH_PLANE_SIDE{75.0f};
static const unsigned int VERTEX_COUNT_PLANE{200};

// phong sphere constants
static const glm::vec3 POSITION_SPHERE{0.0f, 0.0f, 0.0f};
static const float RADIUS_SPHERE{0.7f};
static const unsigned int RING_COUNT_SPHERE{100};
static const unsigned int VERTEX_COUNT_SPHERE{100};

// light constants
static const glm::vec3 POSITION_ORIGIN{0.0f, 0.0f, 0.0f};
static const float RADIUS_LIGHT{0.1f};
static const float INTENSITY_LIGHT{0.3f};
static const unsigned int RING_COUNT_LIGHT{30};
static const unsigned int VERTEX_COUNT_LIGHT{30};

// color constants
static const glm::vec4 COLOR_LIGHT_GRAY{0.85f, 0.85f, 0.85f, 1.0f};
static const glm::vec4 COLOR_WHITE{1.0f, 1.0f, 1.0f, 1.0f};
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0};
static const glm::vec4 COLOR_GREEN{0.0f, 1.0f, 0.0f, 1.0};
static const glm::vec4 COLOR_BLUE{0.0f, 0.0f, 1.0f, 1.0};
static const glm::vec4 COLOR_PLANE{COLOR_WHITE};
static const glm::vec4 COLOR_PHONG_SPHERE{COLOR_LIGHT_GRAY};

// rotation constants
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
    using namespace mesh_generators;
    using namespace light_generators;
    auto window = std::make_shared<SDLWindow>(TITLE, WINDOW_SIZE, WINDOW_SIZE);

    auto phong_material = std::make_shared<ES2PhongMaterial>();
    phong_material->set_specular_exponent(SPECULAR_EXPONENT);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    auto phong_sphere = generate_sphere_mesh(RADIUS_SPHERE, "phong sphere",
                                             POSITION_SPHERE,
                                             COLOR_PHONG_SPHERE, VERTEX_COUNT_SPHERE,
                                             RING_COUNT_SPHERE,
                                             aur::Geometry::TriangleStrip,
                                             phong_material);

    auto phong_plane = generate_rectangle_mesh(LENGTH_PLANE_SIDE, LENGTH_PLANE_SIDE,
                                               "phong plane",
                                               POSITION_PLANE, COLOR_PLANE,
                                               VERTEX_COUNT_PLANE,
                                               VERTEX_COUNT_PLANE,
                                               aur::Geometry::Triangles,
                                               phong_material);

    auto lamp_base_red = generate_sphere_mesh(RADIUS_LIGHT, "lamp base red",
                                              POSITION_ORIGIN,
                                              COLOR_RED, VERTEX_COUNT_LIGHT,
                                              RING_COUNT_LIGHT,
                                              aur::Geometry::TriangleStrip,
                                              constant_material);

    auto lamp_base_green = generate_sphere_mesh(RADIUS_LIGHT, "lamp base green",
                                                POSITION_ORIGIN,
                                                COLOR_GREEN, VERTEX_COUNT_LIGHT,
                                                RING_COUNT_LIGHT,
                                                aur::Geometry::TriangleStrip,
                                                constant_material);

    auto lamp_base_blue = generate_sphere_mesh(RADIUS_LIGHT, "lamp base blue",
                                               POSITION_ORIGIN,
                                               COLOR_BLUE, VERTEX_COUNT_LIGHT,
                                               RING_COUNT_LIGHT,
                                               aur::Geometry::TriangleStrip,
                                               constant_material);

    std::vector<std::shared_ptr<Object>> objects{phong_plane, phong_sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();

    camera->set_z(CAMERA_Z);
    camera->set_y(CAMERA_Y);
    camera->set_rotation_x(CAMERA_ROTATION_X);

    scene->get_directional_lights().clear();
    scene->get_point_lights().clear();

    auto point_light1 = generate_point_light(scene, lamp_base_red, INTENSITY_LIGHT);
    point_light1->set_ambient_color(COLOR_RED);
    auto point_light2 = generate_point_light(scene, lamp_base_green, INTENSITY_LIGHT);
    point_light2->set_ambient_color(COLOR_GREEN);
    auto point_light3 = generate_point_light(scene, lamp_base_blue, INTENSITY_LIGHT);
    point_light3->set_ambient_color(COLOR_BLUE);

    window->set_on_key([&](int key) {
        switch (key) {
            case SDLK_w:
                camera->set_rotation_x(
                        camera->get_rotation_x() + ROTATION_SPEED_CAMERA);
                break;
            case SDLK_a:
                camera->set_rotation_y(
                        camera->get_rotation_y() + ROTATION_SPEED_CAMERA);
                break;
            case SDLK_s:
                camera->set_rotation_x(
                        camera->get_rotation_x() - ROTATION_SPEED_CAMERA);
                break;
            case SDLK_d:
                camera->set_rotation_y(
                        camera->get_rotation_y() - ROTATION_SPEED_CAMERA);
                break;
            case SDLK_e:
                camera->set_y(camera->get_y() + ROTATION_SPEED_CAMERA);
                break;
            case SDLK_q:
                camera->set_y(camera->get_y() - ROTATION_SPEED_CAMERA);
                break;
            case SDLK_UP:
                camera->set_position(camera->get_position() - glm::vec3(
                        camera->get_model_matrix() * FORWARD * SPEED_CAMERA));
                break;
            case SDLK_DOWN:
                camera->set_position(camera->get_position() + glm::vec3(
                        camera->get_model_matrix() * FORWARD * SPEED_CAMERA));
                break;
            case SDLK_ESCAPE:
                exit(0);
            default:
                break;
        }
    });

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
