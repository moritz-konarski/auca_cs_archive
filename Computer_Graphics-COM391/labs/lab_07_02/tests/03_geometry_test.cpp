#include "aur.hpp"
#include "helper_functions/mesh_generators.hpp"

// window constants
static const int WINDOW_FULL_SCREEN{0};
static const int WINDOW_SIZE{WINDOW_FULL_SCREEN};
static const std::string TITLE{"geometry test"};

// camera constants
static const float SPEED_CAMERA{0.1f};
static const float ROTATION_SPEED_CAMERA{0.05f};
static const float Z_POSITION_CAMERA{5.0f};
static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

// rectangle constants
static const float RECTANGLE_SIDE_LENGTH{1.0f};
static const std::string NAME_RECTANGLE_1{"rectangle 1"};
static const std::string NAME_RECTANGLE_2{"rectangle 2"};
static const std::string NAME_RECTANGLE_3{"rectangle 3"};
static const glm::vec3 POSITION_RECTANGLE_1{-2.0f, 2.0f, 0.0f};
static const glm::vec3 POSITION_RECTANGLE_2{0.0f, 2.0f, 0.0f};
static const glm::vec3 POSITION_RECTANGLE_3{2.0f, 2.0f, 0.0f};

// circle constants
static const float RADIUS_CIRCLE{sqrt(2 * RECTANGLE_SIDE_LENGTH) / 2.0f};
static const std::string NAME_CIRCLE_1{"circle 1"};
static const std::string NAME_CIRCLE_2{"circle 2"};
static const std::string NAME_CIRCLE_3{"circle 3"};
static const glm::vec3 POSITION_CIRCLE_1{-2.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_CIRCLE_2{0.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_CIRCLE_3{2.0f, 0.0f, 0.0f};

// sphere constants
static const float RADIUS_SPHERE{sqrt(2 * RECTANGLE_SIDE_LENGTH) / 2.0f};
static const std::string NAME_SPHERE_1{"sphere 1"};
static const std::string NAME_SPHERE_2{"sphere 2"};
static const std::string NAME_SPHERE_3{"sphere 3"};
static const glm::vec3 POSITION_SPHERE_1{-2.0f, -2.0f, 0.0f};
static const glm::vec3 POSITION_SPHERE_2{0.0f, -2.0f, 0.0f};
static const glm::vec3 POSITION_SPHERE_3{2.0f, -2.0f, 0.0f};
static const unsigned int RING_COUNT_SPHERE{16};

// general constants
static const float ROTATION_SPEED_GEOMETRIES{0.01f};
static const float POINT_SIZE{3.0f};
static const int SMALL_SEGMENT_COUNT{8};
static const int MEDIUM_SEGMENT_COUNT{14};
static const int HIGH_SEGMENT_COUNT{26};

// color constants
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_GREEN{0.0f, 1.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_BLUE{0.0f, 0.0f, 1.0f, 1.0f};
static const std::vector<glm::vec4> COLOR_ARRAY{{COLOR_RED},
                                                {COLOR_GREEN},
                                                {COLOR_BLUE}};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace mesh_generators;

    auto window = std::make_shared<SDLWindow>(TITLE, WINDOW_SIZE, WINDOW_SIZE);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();
    constant_material->set_point_size(POINT_SIZE);

    // rectangles
    auto rectangle1 = generate_rectangle_mesh(RECTANGLE_SIDE_LENGTH,
                                              RECTANGLE_SIDE_LENGTH,
                                              NAME_RECTANGLE_1, POSITION_RECTANGLE_1,
                                              COLOR_ARRAY,
                                              SMALL_SEGMENT_COUNT, SMALL_SEGMENT_COUNT,
                                              Geometry::Type::Triangles,
                                              constant_material);

    auto rectangle2 = generate_rectangle_mesh(RECTANGLE_SIDE_LENGTH,
                                              RECTANGLE_SIDE_LENGTH,
                                              NAME_RECTANGLE_2, POSITION_RECTANGLE_2,
                                              COLOR_ARRAY,
                                              MEDIUM_SEGMENT_COUNT, MEDIUM_SEGMENT_COUNT,
                                              Geometry::Type::LineLoop,
                                              constant_material);

    auto rectangle3 = generate_rectangle_mesh(RECTANGLE_SIDE_LENGTH,
                                              RECTANGLE_SIDE_LENGTH,
                                              NAME_RECTANGLE_3, POSITION_RECTANGLE_3,
                                              COLOR_ARRAY,
                                              HIGH_SEGMENT_COUNT, HIGH_SEGMENT_COUNT,
                                              Geometry::Type::Points, constant_material);

    // circles
    auto circle1 = generate_circle_mesh(RADIUS_CIRCLE, NAME_CIRCLE_1, POSITION_CIRCLE_1,
                                        COLOR_ARRAY, SMALL_SEGMENT_COUNT,
                                        Geometry::Type::TriangleFan, constant_material);

    auto circle2 = generate_circle_mesh(RADIUS_CIRCLE, NAME_CIRCLE_2, POSITION_CIRCLE_2,
                                        COLOR_ARRAY, MEDIUM_SEGMENT_COUNT,
                                        Geometry::Type::LineLoop,
                                        constant_material);

    auto circle3 = generate_circle_mesh(RADIUS_CIRCLE, NAME_CIRCLE_3, POSITION_CIRCLE_3,
                                        COLOR_ARRAY, HIGH_SEGMENT_COUNT,
                                        Geometry::Type::Points,
                                        constant_material);

    // spheres
    auto sphere1 = generate_sphere_mesh(RADIUS_SPHERE, NAME_SPHERE_1, POSITION_SPHERE_1,
                                        COLOR_ARRAY, SMALL_SEGMENT_COUNT,
                                        RING_COUNT_SPHERE,
                                        Geometry::Type::Triangles, constant_material);

    auto sphere2 = generate_sphere_mesh(RADIUS_SPHERE, NAME_SPHERE_2, POSITION_SPHERE_2,
                                        COLOR_ARRAY, MEDIUM_SEGMENT_COUNT,
                                        RING_COUNT_SPHERE,
                                        Geometry::Type::LineLoop, constant_material);

    auto sphere3 = generate_sphere_mesh(RADIUS_SPHERE, NAME_SPHERE_3, POSITION_SPHERE_3,
                                        COLOR_ARRAY, HIGH_SEGMENT_COUNT,
                                        RING_COUNT_SPHERE,
                                        Geometry::Type::Points, constant_material);

    std::vector<std::shared_ptr<Object>> objects{rectangle1, rectangle2, rectangle3,
                                                 circle1,
                                                 circle2, circle3, sphere1, sphere2,
                                                 sphere3};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();
    camera->set_z(Z_POSITION_CAMERA);

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
        rectangle1->add_to_rotation(glm::vec3(-ROTATION_SPEED_GEOMETRIES, 0.0f,
                                              ROTATION_SPEED_GEOMETRIES));
        rectangle2->add_to_rotation(glm::vec3(0.0f, ROTATION_SPEED_GEOMETRIES,
                                              ROTATION_SPEED_GEOMETRIES));
        rectangle3->add_to_rotation(
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
