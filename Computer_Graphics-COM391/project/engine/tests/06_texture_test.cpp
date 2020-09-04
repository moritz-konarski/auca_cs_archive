//TODO
// - check if all the sphere parameters work
#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"
#include "constants.hpp"

static const float CAMERA_Z{6.0f};

static const float HEIGHT_PLANE{3.0f};
static const float WIDTH_PLANE{5.0f};

static const float RADIUS_SPHERE{HEIGHT_PLANE / 2.0f};

static const float ROTATION_SPEED{0.003};

static const unsigned int SEGMENT_COUNT{25};

static const std::string NAME_WINDOW{"texture test"};

static const glm::vec3 POSITION_PLANE{
        (RADIUS_SPHERE + WIDTH_PLANE / 2.0f + 0.5f) / 2.0f, 0.0f, 0.0f};
static const glm::vec3 POSITION_SPHERE{
        -(RADIUS_SPHERE + WIDTH_PLANE / 2.0f + 0.5f) / 2.0f, 0.0f, 0.0f};

static const glm::vec4 COLOR_MESH{color::WHITE};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    using namespace helper_functions;

    auto window = std::make_shared<SDLWindow>(NAME_WINDOW,
                                              constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    std::shared_ptr<ES2ConstantMaterial> texture_material = std::make_shared<ES2ConstantMaterial>();

    auto photo_texture = generate_texture(paths::CITY_TEXTURE);

    texture_material->set_texture_1(photo_texture);
    texture_material->set_face_culling_enabled(false);

    Rectangle_Data rectangle_data = {WIDTH_PLANE, HEIGHT_PLANE, SEGMENT_COUNT,
                                     SEGMENT_COUNT};
    Mesh_Data rectangle_mesh_data = {texture_material,
                                     std::vector<glm::vec4>{COLOR_MESH},
                                     "textured rectangle"};
    rectangle_mesh_data.position = POSITION_PLANE;

    std::shared_ptr<Mesh> plane = generate_rectangle_mesh(rectangle_data,
                                                          rectangle_mesh_data);

    Sphere_Data sphere_data = {RADIUS_SPHERE, SEGMENT_COUNT, SEGMENT_COUNT};
    Mesh_Data sphere_mesh_data = {texture_material,
                                  std::vector<glm::vec4>{COLOR_MESH},
                                  "textured sphere", Geometry::Type::Triangles,
                                  POSITION_SPHERE};

    std::shared_ptr<Mesh> sphere = generate_sphere_mesh(sphere_data,
                                                        sphere_mesh_data);

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
