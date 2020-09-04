#define GLM_ENABLE_EXPERIMENTAL
#include "aur.hpp"

static const std::string TITLE{"window test"};
static const int SIZE_FULL_SCREEN{0};
static const int WINDOW_SIZE{SIZE_FULL_SCREEN};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;

    auto window = std::make_shared<SDLWindow>(TITLE, WINDOW_SIZE, WINDOW_SIZE);

    std::vector<std::shared_ptr<Object>> objects{};
    auto scene = std::make_shared<Scene>(objects);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        renderer.render();
    }
}
