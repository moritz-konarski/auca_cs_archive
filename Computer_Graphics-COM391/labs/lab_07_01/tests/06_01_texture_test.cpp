#include "aur.hpp"
#include <geometries/mesh_generators.hpp>

static const float CAMERA_Z{6.0f};
static const float HEIGHT_PLANE{3.0f};
static const float WIDTH_PLANE{5.0f};
static const float RADIUS_SPHERE{HEIGHT_PLANE / 2.0f};
static const float ROTATION_SPEED{0.001};
static const unsigned int SEGMENT_COUNT{25};
static const std::string NAME_PLANE{"texture test plane"};
static const std::string NAME_SPHERE{"texture test sphere"};
static const glm::vec3 POSITION_PLANE{(RADIUS_SPHERE + WIDTH_PLANE / 2.0f + 0.5f) / 2.0f, 0.0f,
                                      0.0f};
static const glm::vec3 POSITION_SPHERE{-(RADIUS_SPHERE + WIDTH_PLANE / 2.0f + 0.5f) / 2.0f, 0.0f,
                                       0.0f};
static const glm::vec4 COLOR_WHITE{1.0f, 1.0f, 1.0f, 1.0f};
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_MESH{COLOR_WHITE};

static const unsigned int FULL_SCREEN{0};
static const unsigned int WINDOW_SIZE{FULL_SCREEN};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace mesh_generators;

    auto window = std::make_shared<SDLWindow>("aur", WINDOW_SIZE, WINDOW_SIZE);

    std::shared_ptr<ES2ConstantMaterial> texture_material = std::make_shared<ES2ConstantMaterial>();

    auto[img_data, img_width, img_height, img_channels] = file_utilities::read_image_file(
            "data/images/photo.jpg");

    auto photo_texture = std::make_shared<ES2Texture>(img_data, img_width, img_height,
                                                      img_channels);

    texture_material->set_texture(photo_texture);

    std::shared_ptr<Mesh> plane = generate_rectangle_mesh(WIDTH_PLANE, HEIGHT_PLANE, NAME_PLANE,
                                                          POSITION_PLANE, COLOR_MESH,
                                                          SEGMENT_COUNT, SEGMENT_COUNT,
                                                          Geometry::Type::Triangles,
                                                          texture_material);

    std::shared_ptr<Mesh> sphere = generate_sphere_mesh(RADIUS_SPHERE, NAME_SPHERE, POSITION_SPHERE,
                                                        COLOR_MESH, SEGMENT_COUNT, SEGMENT_COUNT,
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
