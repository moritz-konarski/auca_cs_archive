#include "aur.hpp"
#include "geometries/mesh_generators.hpp"
#include "geometries/mesh_group_generators.hpp"
#include <time.h>

// window constants
static const int WINDOW_FULL_SCREEN{0};
static const int WINDOW_SIZE{WINDOW_FULL_SCREEN};
static const std::string TITLE{"scene graph test"};

// camera constants
static const float SPEED_CAMERA{0.1f};
static const float ROTATION_SPEED_CAMERA{0.05f};
static const float INITIAL_CAMERA_Z{5.0f};
static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

// general constants
static const glm::vec3 ORIGIN_POSITION{0.0f, 0.0f, 0.0f};
static const float Y_ROTATION_SPEED_CLOCK{0.003f};

// color constants
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_GREEN{0.0f, 1.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_BLUE{0.0f, 0.0f, 1.0f, 1.0f};
static const glm::vec4 COLOR_SQUARE{COLOR_BLUE};
static const glm::vec4 COLOR_SMALL_CIRCLE{COLOR_RED};
static const glm::vec4 COLOR_MEDIUM_CIRCLE{COLOR_RED};
static const glm::vec4 COLOR_MAIN_SPHERE{COLOR_RED};
static const glm::vec4 COLOR_SECOND_HAND{COLOR_RED};
static const glm::vec4 COLOR_MINUTE_HAND{COLOR_RED};
static const glm::vec4 COLOR_HOUR_HAND{COLOR_RED};

// mesh count constants
static const int COUNT_VERTEX{30};
static const int COUNT_SPHERE_RING{12};
static const int COUNT_SMALL_CIRCLES{60};
static const int COUNT_MEDIUM_CIRCLES{12};
static const int COUNT_SQUARES{4};
static const int MODULUS_SMALL_CIRCLES{COUNT_SMALL_CIRCLES + 1};
static const int MODULUS_MEDIUM_CIRCLES{COUNT_MEDIUM_CIRCLES / COUNT_SQUARES};
static const int MODULUS_SQUARES{COUNT_SQUARES + 1};

// names
static const std::string NAME_MAIN_SPHERE{"main sphere"};
static const std::string NAME_SECOND_HAND{"second hand"};
static const std::string NAME_MINUTES_HAND{"minutes hand"};
static const std::string NAME_HOUR_HAND{"hour hand"};

// radius constants
static const float RADIUS_CLOCK{1.5f};
static const float RADIUS_SMALL_CIRCLE{0.02f};
static const float RADIUS_MEDIUM_CIRCLE{0.04f};
static const float RADIUS_MAIN_SPHERE{RADIUS_MEDIUM_CIRCLE};
static const float RADIUS_OFFSET_SQUARE{0.1f};

// length and width constants
static const float LENGTH_SQUARE_SIDE{2.0f * RADIUS_MEDIUM_CIRCLE};
static const float LENGTH_HOUR_HAND{0.5f * RADIUS_CLOCK};
static const float LENGTH_MINUTE_HAND{0.75f * RADIUS_CLOCK};
static const float LENGTH_SECOND_HAND{0.95f * RADIUS_CLOCK};
static const float WIDTH_SECOND_HAND{LENGTH_SQUARE_SIDE / 3.0f};
static const float WIDTH_MINUTE_HAND{LENGTH_SQUARE_SIDE / 2.0f};
static const float WIDTH_HOUR_HAND{LENGTH_SQUARE_SIDE / 1.5f};
static const float Z_OFFSET{0.05f};

void update_hand_angles(struct tm *time_struct, float *second_hand_angle, float *minute_hand_angle,
                        float *hour_hand_angle);

void rotate_y(std::shared_ptr<aur::Mesh> element, float rotation_speed);

void set_hand_angle(std::shared_ptr<aur::Mesh> clock_hand, float angle, float length);

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace mesh_generators;
    using namespace mesh_group_generators;

    auto window = std::make_shared<SDLWindow>(TITLE, WINDOW_SIZE, WINDOW_SIZE);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    // sphere in the center
    auto main_sphere = generate_sphere_mesh(RADIUS_MAIN_SPHERE, NAME_MAIN_SPHERE, ORIGIN_POSITION,
                                            COLOR_MAIN_SPHERE, COUNT_VERTEX, COUNT_SPHERE_RING,
                                            Geometry::Type::TriangleFan, constant_material);

    // rotate sphere so 0 degrees is straight up
    main_sphere->set_rotation_z(M_PI / 2.0f);

    // create meshes that serve as bases for the rings of the clock
    auto small_circle_base = generate_circle_mesh(RADIUS_SMALL_CIRCLE, "small circle base",
                                                  ORIGIN_POSITION, COLOR_SMALL_CIRCLE, COUNT_VERTEX,
                                                  Geometry::Type::TriangleFan, constant_material);

    auto medium_circle_base = generate_circle_mesh(RADIUS_MEDIUM_CIRCLE, "medium circle base",
                                                   ORIGIN_POSITION, COLOR_MEDIUM_CIRCLE,
                                                   COUNT_VERTEX, Geometry::Type::TriangleFan,
                                                   constant_material);

    auto square_base = generate_rectangle_mesh(LENGTH_SQUARE_SIDE, LENGTH_SQUARE_SIDE,
                                               "square_base", ORIGIN_POSITION, COLOR_SQUARE,
                                               COUNT_VERTEX, COUNT_VERTEX,
                                               Geometry::Type::TriangleFan, constant_material);
    // use the meshes to create rings
    // small minute marks
    generate_circle_of_circle_meshes(main_sphere, small_circle_base, RADIUS_CLOCK,
                                     COUNT_SMALL_CIRCLES, MODULUS_SMALL_CIRCLES, 0.0f);
    // medium 5 minute marks
    generate_circle_of_circle_meshes(main_sphere, medium_circle_base,
                                     RADIUS_CLOCK + RADIUS_OFFSET_SQUARE, COUNT_MEDIUM_CIRCLES,
                                     MODULUS_MEDIUM_CIRCLES, -Z_OFFSET);
    // square_base 15 minute marks
    generate_ring_of_square_meshes(main_sphere, square_base, RADIUS_CLOCK + RADIUS_OFFSET_SQUARE,
                                   COUNT_SQUARES, MODULUS_SQUARES, Z_OFFSET);

    // create the hands of the clock
    // create second hand
    auto second_hand = generate_rectangle_mesh(WIDTH_SECOND_HAND, LENGTH_SECOND_HAND,
                                               NAME_SECOND_HAND, ORIGIN_POSITION, COLOR_SECOND_HAND,
                                               COUNT_VERTEX, COUNT_VERTEX,
                                               Geometry::Type::TriangleFan,
                                               constant_material);
    // create minute hand
    auto minute_hand = generate_rectangle_mesh(WIDTH_MINUTE_HAND, LENGTH_MINUTE_HAND,
                                               NAME_MINUTES_HAND, ORIGIN_POSITION,
                                               COLOR_MINUTE_HAND, COUNT_VERTEX, COUNT_VERTEX,
                                               Geometry::Type::TriangleFan, constant_material);
    // create hour hand
    auto hour_hand = generate_rectangle_mesh(WIDTH_HOUR_HAND, LENGTH_HOUR_HAND, NAME_HOUR_HAND,
                                             ORIGIN_POSITION, COLOR_HOUR_HAND, COUNT_VERTEX,
                                             COUNT_VERTEX, Geometry::Type::TriangleFan,
                                             constant_material);
    // add clock hands to center sphere
    main_sphere->add_child(minute_hand);
    main_sphere->add_child(second_hand);
    main_sphere->add_child(hour_hand);

    std::vector<std::shared_ptr<Object>> objects{main_sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();
    camera->set_z(INITIAL_CAMERA_Z);

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

    static float second_hand_angle, minute_hand_angle, hour_hand_angle;
    static struct tm *time_struct;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        update_hand_angles(time_struct, &second_hand_angle, &minute_hand_angle, &hour_hand_angle);

        rotate_y(main_sphere, Y_ROTATION_SPEED_CLOCK);

        set_hand_angle(second_hand, second_hand_angle, LENGTH_SECOND_HAND);
        set_hand_angle(minute_hand, minute_hand_angle, LENGTH_MINUTE_HAND);
        set_hand_angle(hour_hand, hour_hand_angle, LENGTH_HOUR_HAND);

        renderer.render();
    }
}

void update_hand_angles(struct tm *time_struct, float *second_hand_angle, float *minute_hand_angle,
                        float *hour_hand_angle) {
    time_t t = time(NULL);
    time_struct = localtime(&t);
    *second_hand_angle = -2.0f * M_PI / 60.0f * time_struct->tm_sec;
    *minute_hand_angle = -2.0f * M_PI / 60.0f * time_struct->tm_min;
    *hour_hand_angle =
            -2.0f * M_PI / 12.0f * (time_struct->tm_hour % 12) + *minute_hand_angle / 12.0f;
}

void rotate_y(std::shared_ptr<aur::Mesh> element, float rotation_speed) {
    element->add_to_rotation_y(rotation_speed);
}

void set_hand_angle(std::shared_ptr<aur::Mesh> clock_hand, float angle, float length) {
    clock_hand->set_x(length / 2.0f * cos(angle));
    clock_hand->set_y(length / 2.0f * sin(angle));
    clock_hand->set_rotation_z(angle - M_PI / 2.0f);
}
