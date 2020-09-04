#include "aur.hpp"
#include "geometries/mesh_generators.hpp"
#include "lights/light_generators.hpp"
#include <cstdlib>

// window constants
static const int WINDOW_FULL_SCREEN{0};
static const int WINDOW_SIZE{WINDOW_FULL_SCREEN};
static const std::string TITLE{"light test 02"};

// camera constants
static const float SPEED_CAMERA{0.1f};
static const float ROTATION_SPEED_CAMERA{0.05f};
static const glm::vec3 CAMERA_ROTATION{0.7f, -0.7f, 0.0f};
static const glm::vec3 CAMERA_POSITION{-8.0f, -8.0f, 8.0f};
static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

// phong plane constants
static const float SPECULAR_EXPONENT{4.5f};
static const float LENGTH_PLANE_SIDE{10.0f};
static const float CUBE_BOUNDARY{LENGTH_PLANE_SIDE / 2.0f};
static const glm::vec3 POSITION_PLANE_1{LENGTH_PLANE_SIDE / 2.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_PLANE_2{0.0f, LENGTH_PLANE_SIDE / 2.0f, 0.0f};
static const glm::vec3 POSITION_PLANE_3{0.0f, 0.0f, -LENGTH_PLANE_SIDE / 2.0f};
static const unsigned int VERTEX_COUNT_PLANE{25};

// phong sphere constants
static const glm::vec3 POSITION_SPHERE{0.0f, 0.0f, 0.0f};
static const float RADIUS_SPHERE{LENGTH_PLANE_SIDE / 10.0f};
static const unsigned int RING_COUNT_SPHERE{100};
static const unsigned int VERTEX_COUNT_SPHERE{100};

// light constants
static const glm::vec3 POSITION_ORIGIN{0.0f, 0.0f, 0.0f};
static const float RADIUS_LIGHT{0.15f};
static const float INTENSITY_LIGHT{0.2f};
static const float MAX_SPEED{0.08f};
static const float MIN_SPEED{-MAX_SPEED};
static const unsigned int RING_COUNT_LIGHT{30};
static const unsigned int VERTEX_COUNT_LIGHT{30};

// color constants
static const glm::vec4 COLOR_LIGHT_GRAY{0.85f, 0.85f, 0.85f, 1.0f};
static const glm::vec4 COLOR_WHITE{1.0f, 1.0f, 1.0f, 1.0f};
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0};
static const glm::vec4 COLOR_GREEN{0.0f, 1.0f, 0.0f, 1.0};
static const glm::vec4 COLOR_BLUE{0.0f, 0.0f, 1.0f, 1.0};
static const glm::vec4 COLOR_MAGENTA{1.0f, 0.0f, 1.0f, 1.0};
static const glm::vec4 COLOR_PLANE{COLOR_WHITE};
static const glm::vec4 COLOR_PHONG_SPHERE{COLOR_LIGHT_GRAY};

float random_number(float min, float max);

glm::vec3 generate_random_glm_vec3(float min, float max);

glm::vec3 move_object(std::shared_ptr<aur::Object> object, glm::vec3 move_vector);

glm::vec3 check_boundaries(std::shared_ptr<aur::Object> object, glm::vec3 move_vector);

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace mesh_generators;
    using namespace light_generators;
    auto window = std::make_shared<SDLWindow>(TITLE, WINDOW_SIZE, WINDOW_SIZE);

    // initialize the random number generator
    srand(time(NULL));

    auto phong_material = std::make_shared<ES2PhongMaterial>();
    phong_material->set_specular_exponent(SPECULAR_EXPONENT);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    auto phong_sphere = generate_sphere_mesh(RADIUS_SPHERE, "phong sphere", POSITION_SPHERE,
                                             COLOR_PHONG_SPHERE, VERTEX_COUNT_SPHERE,
                                             RING_COUNT_SPHERE,
                                             aur::Geometry::TriangleStrip, phong_material);

    auto phong_plane_1 = generate_rectangle_mesh(LENGTH_PLANE_SIDE, LENGTH_PLANE_SIDE,
                                                 "phong plane 1",
                                                 POSITION_PLANE_1, COLOR_PLANE,
                                                 VERTEX_COUNT_PLANE,
                                                 VERTEX_COUNT_PLANE, aur::Geometry::Triangles,
                                                 phong_material);
    phong_plane_1->set_rotation(glm::vec3(0.0f, -M_PI / 2.0f, 0.0f));

    auto phong_plane_2 = generate_rectangle_mesh(LENGTH_PLANE_SIDE, LENGTH_PLANE_SIDE,
                                                 "phong plane 2",
                                                 POSITION_PLANE_2, COLOR_PLANE,
                                                 VERTEX_COUNT_PLANE,
                                                 VERTEX_COUNT_PLANE, aur::Geometry::Triangles,
                                                 phong_material);
    phong_plane_2->set_rotation(glm::vec3(M_PI / 2.0f, 0.0f, 0.0f));

    auto phong_plane_3 = generate_rectangle_mesh(LENGTH_PLANE_SIDE, LENGTH_PLANE_SIDE,
                                                 "phong plane 3",
                                                 POSITION_PLANE_3, COLOR_PLANE,
                                                 VERTEX_COUNT_PLANE,
                                                 VERTEX_COUNT_PLANE, aur::Geometry::Triangles,
                                                 phong_material);

    auto lamp_base_red = generate_sphere_mesh(RADIUS_LIGHT, "lamp base red", POSITION_ORIGIN,
                                              COLOR_RED, VERTEX_COUNT_LIGHT, RING_COUNT_LIGHT,
                                              aur::Geometry::TriangleStrip, constant_material);

    auto lamp_base_green = generate_sphere_mesh(RADIUS_LIGHT, "lamp base green", POSITION_ORIGIN,
                                                COLOR_GREEN, VERTEX_COUNT_LIGHT, RING_COUNT_LIGHT,
                                                aur::Geometry::TriangleStrip, constant_material);

    auto lamp_base_blue = generate_sphere_mesh(RADIUS_LIGHT, "lamp base blue", POSITION_ORIGIN,
                                               COLOR_BLUE, VERTEX_COUNT_LIGHT, RING_COUNT_LIGHT,
                                               aur::Geometry::TriangleStrip, constant_material);

    auto lamp_base_magenta = generate_sphere_mesh(RADIUS_LIGHT, "lamp base magenta",
                                                  POSITION_ORIGIN,
                                                  COLOR_MAGENTA, VERTEX_COUNT_LIGHT,
                                                  RING_COUNT_LIGHT,
                                                  aur::Geometry::TriangleStrip, constant_material);

    std::vector<std::shared_ptr<Object>> objects{phong_plane_1, phong_plane_2, phong_plane_3,
                                                 phong_sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();

    camera->set_rotation(CAMERA_ROTATION);
    camera->set_position(CAMERA_POSITION);

    scene->get_directional_lights().clear();
    scene->get_point_lights().clear();

    // generate red point light at random position with random speed
    auto point_light_red = generate_point_light(scene, lamp_base_red, INTENSITY_LIGHT);
    point_light_red->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT, CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_red_direction = generate_random_glm_vec3(MIN_SPEED, MAX_SPEED);

    auto point_light_green = generate_point_light(scene, lamp_base_green, INTENSITY_LIGHT);
    point_light_green->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT, CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_green_direction = generate_random_glm_vec3(MIN_SPEED, MAX_SPEED);

    auto point_light_blue = generate_point_light(scene, lamp_base_blue, INTENSITY_LIGHT);
    point_light_blue->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT, CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_blue_direction = generate_random_glm_vec3(MIN_SPEED, MAX_SPEED);

    auto point_light_magenta = generate_point_light(scene, lamp_base_magenta, INTENSITY_LIGHT);
    point_light_magenta->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT, CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_magenta_direction = generate_random_glm_vec3(MIN_SPEED, MAX_SPEED);

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

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        point_light_red_direction = move_object(point_light_red, point_light_red_direction);
        point_light_green_direction = move_object(point_light_green, point_light_green_direction);
        point_light_blue_direction = move_object(point_light_blue, point_light_blue_direction);
        point_light_magenta_direction = move_object(point_light_magenta,
                                                    point_light_magenta_direction);
        renderer.render();
    }
}

glm::vec3 generate_random_glm_vec3(float min, float max) {
    return glm::vec3(random_number(min, max), random_number(min, max), random_number(min, max));
}

float random_number(float min, float max) {
    int range = max - min;
    double random = rand() % 1000000 / 1000000.0f;
    return (min > 0) ? static_cast<float>(random * range - min) : static_cast<float>(
            random * range + min);
}

glm::vec3 move_object(std::shared_ptr<aur::Object> object, glm::vec3 move_vector) {
    object->add_to_position(move_vector);
    return check_boundaries(object, move_vector);
}

glm::vec3
check_boundaries(std::shared_ptr<aur::Object> object, glm::vec3 move_vector) {
    if (abs(object->get_x()) >= CUBE_BOUNDARY - RADIUS_LIGHT - MAX_SPEED) {
        move_vector.x *= -1.0f;
    } else if (abs(object->get_y()) >= CUBE_BOUNDARY - RADIUS_LIGHT - MAX_SPEED) {
        move_vector.y *= -1.0f;
    } else if (abs(object->get_z()) >= CUBE_BOUNDARY - RADIUS_LIGHT - MAX_SPEED) {
        move_vector.z *= -1.0f;
    }
    return move_vector;
}
