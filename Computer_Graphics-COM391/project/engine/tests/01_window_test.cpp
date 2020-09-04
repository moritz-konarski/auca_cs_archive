#include "aur.hpp"
#include "constants.hpp"

static const std::string TITLE{"window test"};

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;

    auto window = std::make_shared<SDLWindow>(TITLE, constant::WINDOW_FULL_SCREEN,
                                              constant::WINDOW_FULL_SCREEN);

    std::vector<std::shared_ptr<Object>> objects{};
    auto scene = std::make_shared<Scene>(objects);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();
        renderer.render();
    }
}
