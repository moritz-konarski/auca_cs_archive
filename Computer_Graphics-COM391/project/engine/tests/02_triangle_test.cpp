#include "aur.hpp"
#include "helpers.hpp"
#include "constants.hpp"

static const std::string TITLE{"triangle test"};

static const float CAMERA_Z{5.0f};

static const float TRIANGLE_ROTATION_SPEED{0.02f};
static const float TRIANGLE_SIZE{2.5f};
static const std::string TRIANGLE_NAME{"triangle"};

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

    Triangle_Data triangle_data = {TRIANGLE_SIZE};
    Mesh_Data triangle_mesh_data = {constant_material, COLOR_ARRAY, TRIANGLE_NAME};

    auto triangle = generate_triangle_mesh(triangle_data, triangle_mesh_data);

    std::vector<std::shared_ptr<Object>> objects{triangle};
    auto scene = std::make_shared<Scene>(objects);

    auto root = scene->get_root();
    auto &camera = scene->get_camera();
    camera->set_z(CAMERA_Z);

    helper_functions::set_camera(camera);
    window->set_on_key_down(helper_functions::process_keystrokes);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        triangle->add_to_rotation_z(TRIANGLE_ROTATION_SPEED);
        renderer.render();
    }
}
