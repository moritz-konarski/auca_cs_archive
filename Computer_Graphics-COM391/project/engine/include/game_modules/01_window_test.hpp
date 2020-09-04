#ifndef WINDOW_TEST_HPP
#define WINDOW_TEST_HPP

#include "constants.hpp"
#include "helpers.hpp"
#include "game_modules.hpp"

namespace game_modules {
    class Window_Test : public Game_State {

    public:
        Window_Test() {
            using namespace helper_functions;
            _window = std::make_shared<SDLWindow>(_title,
                                                  constant::WINDOW_FULL_SCREEN,
                                                  constant::WINDOW_FULL_SCREEN);

            _scene = std::make_shared<Scene>(_objects);
        }

    private:
        std::string _title{"window test"};
    };
}

#endif
