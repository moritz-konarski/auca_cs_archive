#include "aur.hpp"
#include "helper_functions/mesh_generators.hpp"

// window constants
static const int WINDOW_FULL_SCREEN{0};
static const int WINDOW_SIZE{WINDOW_FULL_SCREEN};
static const std::string TITLE{"triangle test"};

// camera constants
static const float SPEED_CAMERA{0.1f};
static const float ROTATION_SPEED_CAMERA{0.05f};
static const float CAMERA_Z{5.0f};
static const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};

// triangle constants
static const float TRIANGLE_ROTATION_SPEED{0.02f};
static const float TRIANGLE_SIZE{2.5f};
static const std::string TRIANGLE_NAME{"triangle"};
static const glm::vec3 POSITION_ORIGIN{0.0f, 0.0f, 0.0f};

// color constants
static const glm::vec4 COLOR_RED{1.0f, 0.0f, 0.0f, 1.0f};
static const glm::vec4 COLOR_GREEN{0.0f, 0.0f, 1.0f, 1.0f};
static const glm::vec4 COLOR_BLUE{0.0f, 1.0f, 0.0f, 1.0f};
static const std::vector<glm::vec4> COLOR_ARRAY{{COLOR_RED},
                                                {COLOR_GREEN},
                                                {COLOR_BLUE}};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    auto window = std::make_shared<SDLWindow>(TITLE, WINDOW_SIZE, WINDOW_SIZE);
    auto constant_material = std::make_shared<ES2ConstantMaterial>();

    auto triangle = mesh_generators::generate_triangle_mesh(TRIANGLE_SIZE, TRIANGLE_NAME,
                                                            POSITION_ORIGIN, COLOR_ARRAY,
                                                            constant_material);

    std::vector<std::shared_ptr<Object>> objects{triangle};
    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();
    auto &camera = scene->get_camera();
    camera->set_z(CAMERA_Z);

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
        triangle->add_to_rotation_z(TRIANGLE_ROTATION_SPEED);
        renderer.render();
    }
}
