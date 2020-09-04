#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const std::string TITLE{"geometry test"};

static const float Z_POSITION_CAMERA{5.0f};

static const float SQUARE_SIDE_LENGTH{1.0f};
static const glm::vec3 POSITION_RECTANGLE_1{-2.0f, 2.0f, 0.0f};
static const glm::vec3 POSITION_RECTANGLE_2{0.0f, 2.0f, 0.0f};
static const glm::vec3 POSITION_RECTANGLE_3{2.0f, 2.0f, 0.0f};

static const float RADIUS_CIRCLE{sqrt(2 * SQUARE_SIDE_LENGTH) / 2.0f};
static const glm::vec3 POSITION_CIRCLE_1{-2.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_CIRCLE_2{0.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_CIRCLE_3{2.0f, 0.0f, 0.0f};

static const float RADIUS_SPHERE{RADIUS_CIRCLE};
static const glm::vec3 POSITION_SPHERE_1{-2.0f, -2.0f, 0.0f};
static const glm::vec3 POSITION_SPHERE_2{0.0f, -2.0f, 0.0f};
static const glm::vec3 POSITION_SPHERE_3{2.0f, -2.0f, 0.0f};
static const unsigned int RING_COUNT_SPHERE{16};

static const float ROTATION_SPEED_GEOMETRIES{0.01f};
static const int SMALL_SEGMENT_COUNT{8};
static const int MEDIUM_SEGMENT_COUNT{14};
static const int HIGH_SEGMENT_COUNT{26};

static const std::vector<glm::vec4> COLOR_ARRAY{{color::RED},
                                                {color::GREEN},
                                                {color::BLUE}};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;

    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    auto constant_material = std::make_shared<ES2ConstantMaterial>();
    constant_material->set_face_culling_enabled(false);
    constant_material->set_point_sizing_enabled(true);
    constant_material->set_point_size(3.0f);
    constant_material->set_line_width(1.5f);

    // squares
    Square_Data square_data = {SQUARE_SIDE_LENGTH, SMALL_SEGMENT_COUNT};
    Mesh_Data mesh_data = {constant_material, COLOR_ARRAY, "square 1",
                           Geometry::Type::Triangles, POSITION_RECTANGLE_1};

    auto square1 = generate_square_mesh(square_data, mesh_data);

    square_data.segment_count = MEDIUM_SEGMENT_COUNT;
    mesh_data.name = "square 2";
    mesh_data.geometry_type = Geometry::Type::LineLoop;
    mesh_data.position = POSITION_RECTANGLE_2;

    auto square2 = generate_square_mesh(square_data, mesh_data);

    square_data.segment_count = HIGH_SEGMENT_COUNT;
    mesh_data.name = "square 3";
    mesh_data.geometry_type = Geometry::Type::Points;
    mesh_data.position = POSITION_RECTANGLE_3;

    auto square3 = generate_square_mesh(square_data, mesh_data);

    // circles
    Circle_Data circle_data = {RADIUS_CIRCLE, SMALL_SEGMENT_COUNT};
    mesh_data.position = POSITION_CIRCLE_1;
    mesh_data.name = "circle 1";
    mesh_data.geometry_type = Geometry::Type::TriangleFan;

    // circles
    auto circle1 = generate_circle_mesh(circle_data, mesh_data);

    circle_data.segment_count = MEDIUM_SEGMENT_COUNT;
    mesh_data.position = POSITION_CIRCLE_2;
    mesh_data.name = "circle 2";
    mesh_data.geometry_type = Geometry::Type::LineLoop;

    auto circle2 = generate_circle_mesh(circle_data, mesh_data);

    circle_data.segment_count = HIGH_SEGMENT_COUNT;
    mesh_data.position = POSITION_CIRCLE_3;
    mesh_data.name = "circle 3";
    mesh_data.geometry_type = Geometry::Type::Points;

    auto circle3 = generate_circle_mesh(circle_data, mesh_data);

    // spheres
    Sphere_Data sphere_data = {RADIUS_SPHERE, SMALL_SEGMENT_COUNT, RING_COUNT_SPHERE};
    mesh_data.position = POSITION_SPHERE_1;
    mesh_data.name = "sphere 1";
    mesh_data.geometry_type = Geometry::Type::Triangles;

    auto sphere1 = generate_sphere_mesh(sphere_data, mesh_data);

    sphere_data.segment_count = MEDIUM_SEGMENT_COUNT;
    mesh_data.position = POSITION_SPHERE_2;
    mesh_data.name = "sphere 2";
    mesh_data.geometry_type = Geometry::Type::LineLoop;

    auto sphere2 = generate_sphere_mesh(sphere_data, mesh_data);

    sphere_data.segment_count = HIGH_SEGMENT_COUNT;
    mesh_data.position = POSITION_SPHERE_3;
    mesh_data.name = "sphere 3";
    mesh_data.geometry_type = Geometry::Type::Points;

    auto sphere3 = generate_sphere_mesh(sphere_data, mesh_data);

    std::vector<std::shared_ptr<Object>> objects{square1, square2, square3,
                                                 circle1,
                                                 circle2, circle3, sphere1, sphere2,
                                                 sphere3};

    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();
    camera->set_z(Z_POSITION_CAMERA);

    helper_functions::set_camera(camera);
    window->set_on_key_down(helper_functions::process_keystrokes);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        square1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                           ROTATION_SPEED_GEOMETRIES));
        square2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                           ROTATION_SPEED_GEOMETRIES));
        square3->add_to_rotation(
                glm::vec3(ROTATION_SPEED_GEOMETRIES, -ROTATION_SPEED_GEOMETRIES,
                          0.0f));

        circle1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                           ROTATION_SPEED_GEOMETRIES));
        circle2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                           ROTATION_SPEED_GEOMETRIES));
        circle3->add_to_rotation(
                glm::vec3(ROTATION_SPEED_GEOMETRIES, -ROTATION_SPEED_GEOMETRIES,
                          0.0f));

        sphere1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                           ROTATION_SPEED_GEOMETRIES));
        sphere2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                           ROTATION_SPEED_GEOMETRIES));
        sphere3->add_to_rotation(
                glm::vec3(ROTATION_SPEED_GEOMETRIES, -ROTATION_SPEED_GEOMETRIES,
                          0.0f));

        renderer.render();
    }
}
