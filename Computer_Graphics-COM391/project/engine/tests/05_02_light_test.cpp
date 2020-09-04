//TODO
// - fix camera angle
// - fix light behavior
#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"
#include <cstdlib>

static const std::string TITLE{"light test 02"};

// camera helper_functions
static const glm::vec3 CAMERA_ROTATION{0.7f, -0.7f, 0.0f};
static const glm::vec3 CAMERA_POSITION{-8.0f, -8.0f, 8.0f};

// phong plane helper_functions
static const float SPECULAR_EXPONENT{4.5f};
static const float LENGTH_PLANE_SIDE{10.0f};
static const float CUBE_BOUNDARY{LENGTH_PLANE_SIDE / 2.0f};
static const glm::vec3 POSITION_PLANE_1{LENGTH_PLANE_SIDE / 2.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_PLANE_2{0.0f, LENGTH_PLANE_SIDE / 2.0f, 0.0f};
static const glm::vec3 POSITION_PLANE_3{0.0f, 0.0f, -LENGTH_PLANE_SIDE / 2.0f};
static const unsigned int VERTEX_COUNT_PLANE{25};

static const float RADIUS_SPHERE{LENGTH_PLANE_SIDE / 10.0f};
static const unsigned int RING_COUNT_SPHERE{100};
static const unsigned int VERTEX_COUNT_SPHERE{100};

static const float RADIUS_LIGHT{0.15f};
static const float INTENSITY_LIGHT{0.2f};
static const float MAX_SPEED{0.08f};
static const float MIN_SPEED{-MAX_SPEED};
static const unsigned int RING_COUNT_LIGHT{30};
static const unsigned int VERTEX_COUNT_LIGHT{30};

// color helper_functions
static const std::vector<glm::vec4> COLOR_PLANE{color::WHITE};
static const std::vector<glm::vec4> COLOR_PHONG_SPHERE{color::LIGHT_GRAY};

float random_number(float min, float max);

glm::vec3 generate_random_glm_vec3(float min, float max);

glm::vec3 move_object(std::shared_ptr<aur::Object> object, glm::vec3 move_vector);

glm::vec3
check_boundaries(std::shared_ptr<aur::Object> object, glm::vec3 move_vector);

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;
    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    // initialize the random number generator
    srand(time(NULL));

    auto phong_material = std::make_shared<ES2PhongMaterial>();
    phong_material->set_specular_exponent(SPECULAR_EXPONENT);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    Sphere_Data sphere_data = {RADIUS_SPHERE, VERTEX_COUNT_SPHERE,
                               RING_COUNT_SPHERE};
    Mesh_Data sphere_mesh_data = {phong_material, COLOR_PHONG_SPHERE, "phong sphere",
                                  Geometry::Type::TriangleStrip};
    auto phong_sphere = generate_sphere_mesh(sphere_data, sphere_mesh_data);

    Square_Data square_data = {LENGTH_PLANE_SIDE, VERTEX_COUNT_PLANE};
    Mesh_Data square_mesh_data = {phong_material, COLOR_PLANE, "phong plane 1",
                                  Geometry::Type::Triangles, POSITION_PLANE_1};
    auto phong_plane_1 = generate_square_mesh(square_data, square_mesh_data);
    phong_plane_1->set_rotation(glm::vec3(0.0f, -M_PI / 2.0f, 0.0f));

    square_mesh_data.name = "phong plane 2";
    square_mesh_data.position = POSITION_PLANE_2;
    auto phong_plane_2 = generate_square_mesh(square_data, square_mesh_data);
    phong_plane_2->set_rotation(glm::vec3(M_PI / 2.0f, 0.0f, 0.0f));

    square_mesh_data.name = "phong plane 3";
    square_mesh_data.position = POSITION_PLANE_3;
    auto phong_plane_3 = generate_square_mesh(square_data, square_mesh_data);

    Sphere_Data lamp_base = {RADIUS_LIGHT, VERTEX_COUNT_LIGHT,
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
    Mesh_Data lamp_mesh_base_magenta = {constant_material,
                                     std::vector<glm::vec4>{color::MAGENTA},
                                     "lamp base", Geometry::Type::TriangleStrip};

    std::vector<std::shared_ptr<Object>> objects{phong_plane_1, phong_plane_2,
                                                 phong_plane_3,
                                                 phong_sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();

    camera->set_rotation(CAMERA_ROTATION);
    camera->set_position(CAMERA_POSITION);

    scene->get_directional_lights().clear();
    scene->get_point_lights().clear();

    // generate red point light at random position with random speed
    auto point_light_red = generate_point_light(scene, lamp_base, lamp_mesh_base_red,
                                                INTENSITY_LIGHT);
    point_light_red->set_ambient_color(color::RED);
    point_light_red->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT,
                                     CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_red_direction = generate_random_glm_vec3(MIN_SPEED,
                                                                   MAX_SPEED);

    auto point_light_green = generate_point_light(scene, lamp_base, lamp_mesh_base_green,
                                                  INTENSITY_LIGHT);
    point_light_green->set_ambient_color(color::GREEN);
    point_light_green->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT,
                                     CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_green_direction = generate_random_glm_vec3(MIN_SPEED,
                                                                     MAX_SPEED);

    auto point_light_blue = generate_point_light(scene, lamp_base, lamp_mesh_base_blue,
                                                 INTENSITY_LIGHT);
    point_light_blue->set_ambient_color(color::BLUE);
    point_light_blue->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT,
                                     CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_blue_direction = generate_random_glm_vec3(MIN_SPEED,
                                                                    MAX_SPEED);

    auto point_light_magenta = generate_point_light(scene, lamp_base, lamp_mesh_base_magenta,
                                                    INTENSITY_LIGHT);
    point_light_magenta->set_ambient_color(color::MAGENTA);
    point_light_magenta->set_position(
            generate_random_glm_vec3(-CUBE_BOUNDARY + RADIUS_LIGHT,
                                     CUBE_BOUNDARY - RADIUS_LIGHT));
    glm::vec3 point_light_magenta_direction = generate_random_glm_vec3(MIN_SPEED,
                                                                       MAX_SPEED);

    helper_functions::set_camera(camera);
    window->set_on_key_down(process_keystrokes);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        point_light_red_direction = move_object(point_light_red,
                                                point_light_red_direction);
        point_light_green_direction = move_object(point_light_green,
                                                  point_light_green_direction);
        point_light_blue_direction = move_object(point_light_blue,
                                                 point_light_blue_direction);
        point_light_magenta_direction = move_object(point_light_magenta,
                                                    point_light_magenta_direction);
        renderer.render();
    }
}

glm::vec3 generate_random_glm_vec3(float min, float max) {
    return glm::vec3(random_number(min, max), random_number(min, max),
                     random_number(min, max));
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
    }
    if (abs(object->get_y()) >= CUBE_BOUNDARY - RADIUS_LIGHT - MAX_SPEED) {
        move_vector.y *= -1.0f;
    }
    if (abs(object->get_z()) >= CUBE_BOUNDARY - RADIUS_LIGHT - MAX_SPEED) {
        move_vector.z *= -1.0f;
    }
    return move_vector;
}
