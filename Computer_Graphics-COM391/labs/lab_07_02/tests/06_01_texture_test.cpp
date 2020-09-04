#include "aur.hpp"
#include "helper_functions/mesh_generators.hpp"
#include "helper_functions/texture_generators.hpp"

static const float CAMERA_Z{6.0f};
static const float HEIGHT_PLANE{3.0f};
static const float WIDTH_PLANE{5.0f};
static const float RADIUS_SPHERE{HEIGHT_PLANE / 2.0f};
static const float ROTATION_SPEED{0.001};
static const unsigned int SEGMENT_COUNT{25};
static const std::string NAME_WINDOW{"texture test 1"};
static const std::string NAME_PLANE{"texture test plane"};
static const std::string NAME_SPHERE{"texture test sphere"};
static const std::string PATH_CITY_IMAGE{"data/images/city.jpg"};
static const glm::vec3 POSITION_PLANE{(RADIUS_SPHERE + WIDTH_PLANE / 2.0f + 0.5f) / 2.0f,
                                      0.0f,
                                      0.0f};
static const glm::vec3 POSITION_SPHERE{
        -(RADIUS_SPHERE + WIDTH_PLANE / 2.0f + 0.5f) / 2.0f, 0.0f,
        0.0f};
static const glm::vec4 COLOR_WHITE{1.0f, 1.0f, 1.0f, 1.0f};
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_BLACK{0.0f, 0.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_MESH{COLOR_WHITE};

static const unsigned int FULL_SCREEN{0};
static const unsigned int WINDOW_SIZE{FULL_SCREEN};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace mesh_generators;
    using namespace texture_generators;

    auto window = std::make_shared<SDLWindow>(NAME_WINDOW, WINDOW_SIZE, WINDOW_SIZE);

    std::shared_ptr<ES2ConstantMaterial> texture_material = std::make_shared<ES2ConstantMaterial>();

    auto photo_texture = generate_texture(PATH_CITY_IMAGE);

    texture_material->set_texture_1(photo_texture);

    std::shared_ptr<Mesh> plane = generate_rectangle_mesh(WIDTH_PLANE, HEIGHT_PLANE,
                                                          NAME_PLANE,
                                                          POSITION_PLANE, COLOR_MESH,
                                                          SEGMENT_COUNT, SEGMENT_COUNT,
                                                          Geometry::Type::Triangles,
                                                          texture_material);

    std::shared_ptr<Mesh> sphere = generate_sphere_mesh(RADIUS_SPHERE, NAME_SPHERE,
                                                        POSITION_SPHERE,
                                                        COLOR_MESH, SEGMENT_COUNT,
                                                        SEGMENT_COUNT,
                                                        Geometry::Type::TriangleStrip,
                                                        texture_material);

    std::vector<std::shared_ptr<Object>> objects{plane, sphere};
    auto scene = std::make_shared<Scene>(objects);
    auto camera = scene->get_camera();

    camera->set_z(CAMERA_Z);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        plane->add_to_rotation_y(ROTATION_SPEED);
        sphere->add_to_rotation_y(-ROTATION_SPEED);

        renderer.render();
    }
}
