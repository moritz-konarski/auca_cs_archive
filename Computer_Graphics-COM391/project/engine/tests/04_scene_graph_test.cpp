#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"
#include <time.h>

static const std::string TITLE{"scene graph test"};

static const float INITIAL_CAMERA_Z{5.0f};

static const float Y_ROTATION_SPEED_CLOCK{0.003f};

static const std::vector<glm::vec4> COLOR_SQUARE{color::BLUE};
static const std::vector<glm::vec4> COLOR_SMALL_CIRCLE{color::RED};
static const std::vector<glm::vec4> COLOR_MEDIUM_CIRCLE{color::RED};
static const std::vector<glm::vec4> COLOR_MAIN_SPHERE{color::RED};
static const std::vector<glm::vec4> COLOR_SECOND_HAND{color::RED};
static const std::vector<glm::vec4> COLOR_MINUTE_HAND{color::RED};
static const std::vector<glm::vec4> COLOR_HOUR_HAND{color::RED};

static const int COUNT_VERTEX{30};
static const int COUNT_SPHERE_RING{12};
static const int COUNT_SMALL_CIRCLES{60};
static const int COUNT_MEDIUM_CIRCLES{12};
static const int COUNT_SQUARES{4};
static const int MODULUS_SMALL_CIRCLES{COUNT_SMALL_CIRCLES + 1};
static const int MODULUS_MEDIUM_CIRCLES{COUNT_MEDIUM_CIRCLES / COUNT_SQUARES};
static const int MODULUS_SQUARES{COUNT_SQUARES + 1};

static const float RADIUS_CLOCK{1.5f};
static const float RADIUS_SMALL_CIRCLE{0.02f};
static const float RADIUS_MEDIUM_CIRCLE{0.04f};
static const float RADIUS_MAIN_SPHERE{RADIUS_MEDIUM_CIRCLE};
static const float RADIUS_OFFSET_SQUARE{0.1f};

static const float LENGTH_SQUARE_SIDE{2.0f * RADIUS_MEDIUM_CIRCLE};
static const float LENGTH_HOUR_HAND{0.5f * RADIUS_CLOCK};
static const float LENGTH_MINUTE_HAND{0.75f * RADIUS_CLOCK};
static const float LENGTH_SECOND_HAND{0.95f * RADIUS_CLOCK};
static const float WIDTH_SECOND_HAND{LENGTH_SQUARE_SIDE / 3.0f};
static const float WIDTH_MINUTE_HAND{LENGTH_SQUARE_SIDE / 2.0f};
static const float WIDTH_HOUR_HAND{LENGTH_SQUARE_SIDE / 1.5f};
static const float Z_OFFSET{0.05f};

void update_hand_angles(struct tm *time_struct, float *second_hand_angle,
                        float *minute_hand_angle,
                        float *hour_hand_angle);

void rotate_y(std::shared_ptr<aur::Mesh> element, float rotation_speed);

void
set_hand_angle(std::shared_ptr<aur::Mesh> clock_hand, float angle, float length);

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;

    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();
    constant_material->set_face_culling_enabled(false);

    // sphere in the center
    Sphere_Data sphere_data = {RADIUS_MAIN_SPHERE, COUNT_VERTEX, COUNT_SPHERE_RING};
    Mesh_Data mesh_data = {constant_material, COLOR_MAIN_SPHERE, "main sphere",
                           Geometry::Type::TriangleFan};

    auto main_sphere = generate_sphere_mesh(sphere_data, mesh_data);
    main_sphere->set_rotation_z(M_PI / 2.0f);

    Circle_Data small_circle_data = {RADIUS_SMALL_CIRCLE, COUNT_VERTEX};
    Mesh_Data small_circle_mesh_data = {constant_material, COLOR_SMALL_CIRCLE,
                                        "small circle base",
                                        Geometry::Type::TriangleFan};

    // small minute marks
    generate_circle_ring(main_sphere, small_circle_data, small_circle_mesh_data,
                         RADIUS_CLOCK,
                         COUNT_SMALL_CIRCLES, MODULUS_SMALL_CIRCLES, 0.0f);

    Circle_Data medium_circle_data = {RADIUS_MEDIUM_CIRCLE, COUNT_VERTEX};
    Mesh_Data medium_circle_mesh_data = {constant_material, COLOR_MEDIUM_CIRCLE,
                                         "medium circle base",
                                         Geometry::Type::TriangleFan};

    // medium 5 minute marks
    generate_circle_ring(main_sphere, medium_circle_data, medium_circle_mesh_data,
                         RADIUS_CLOCK + RADIUS_OFFSET_SQUARE,
                         COUNT_MEDIUM_CIRCLES, MODULUS_MEDIUM_CIRCLES, -Z_OFFSET);

    Square_Data square_data = {LENGTH_SQUARE_SIDE, COUNT_VERTEX};
    Mesh_Data square_mesh_data = {constant_material, COLOR_SQUARE, "square base",
                                  Geometry::Type::TriangleFan};

    // square_base 15 minute marks
    generate_square_ring(main_sphere, square_data, square_mesh_data,
                         RADIUS_CLOCK + RADIUS_OFFSET_SQUARE,
                         COUNT_SQUARES, MODULUS_SQUARES, Z_OFFSET);

    // create second hand
    Rectangle_Data hand_data = {WIDTH_SECOND_HAND, LENGTH_SECOND_HAND,
                                COUNT_VERTEX, COUNT_VERTEX};
    Mesh_Data hand_mesh_data = {constant_material, COLOR_SECOND_HAND, "second hand",
                                Geometry::Type::TriangleFan};
    auto second_hand = generate_rectangle_mesh(hand_data, hand_mesh_data);
    main_sphere->add_child(second_hand);

    hand_data.height = LENGTH_MINUTE_HAND;
    hand_data.width = WIDTH_MINUTE_HAND;
    hand_mesh_data.color_array = COLOR_MINUTE_HAND;
    hand_mesh_data.name = "minute hand";
    // create minute hand
    auto minute_hand = generate_rectangle_mesh(hand_data, hand_mesh_data);
    main_sphere->add_child(minute_hand);

    hand_data.height = LENGTH_HOUR_HAND;
    hand_data.width = WIDTH_HOUR_HAND;
    hand_mesh_data.color_array = COLOR_HOUR_HAND;
    hand_mesh_data.name = "hour hand";
    // create hour hand
    auto hour_hand = generate_rectangle_mesh(hand_data, hand_mesh_data);
    main_sphere->add_child(hour_hand);

    std::vector<std::shared_ptr<Object>> objects{main_sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();

    auto &camera = scene->get_camera();
    camera->set_z(INITIAL_CAMERA_Z);

    helper_functions::set_camera(camera);
    window->set_on_key_down(helper_functions::process_keystrokes);

    static float second_hand_angle, minute_hand_angle, hour_hand_angle;
    static struct tm *time_struct;

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        update_hand_angles(time_struct, &second_hand_angle, &minute_hand_angle,
                           &hour_hand_angle);

        rotate_y(main_sphere, Y_ROTATION_SPEED_CLOCK);

        set_hand_angle(second_hand, second_hand_angle, LENGTH_SECOND_HAND);
        set_hand_angle(minute_hand, minute_hand_angle, LENGTH_MINUTE_HAND);
        set_hand_angle(hour_hand, hour_hand_angle, LENGTH_HOUR_HAND);

        renderer.render();
    }
}

void update_hand_angles(struct tm *time_struct, float *second_hand_angle,
                        float *minute_hand_angle,
                        float *hour_hand_angle) {
    time_t t = time(NULL);
    time_struct = localtime(&t);
    *second_hand_angle = -2.0f * M_PI / 60.0f * time_struct->tm_sec;
    *minute_hand_angle = -2.0f * M_PI / 60.0f * time_struct->tm_min;
    *hour_hand_angle =
            -2.0f * M_PI / 12.0f * (time_struct->tm_hour % 12) +
            *minute_hand_angle / 12.0f;
}

void rotate_y(std::shared_ptr<aur::Mesh> element, float rotation_speed) {
    element->add_to_rotation_y(rotation_speed);
}

void
set_hand_angle(std::shared_ptr<aur::Mesh> clock_hand, float angle, float length) {
    clock_hand->set_x(length / 2.0f * cos(angle));
    clock_hand->set_y(length / 2.0f * sin(angle));
    clock_hand->set_rotation_z(angle - M_PI / 2.0f);
}
