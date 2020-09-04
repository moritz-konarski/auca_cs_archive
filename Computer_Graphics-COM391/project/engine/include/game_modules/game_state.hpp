#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game_modules.hpp"
#include "aur.hpp"
#include "constants.hpp"
#include "helpers.hpp"

namespace game_modules {

    enum State {
        Menu_State,
        Window_Test_State,
        Triangle_Test_State,
        Geometry_Test_State,
        Scene_Graph_Test_State,
        Light_Test_1_State,
        Light_Test_2_State,
        Texture_Test_State,
        Textured_Plane_Test_State,
        Material_Properties_Test_State,
        Normal_Mapping_Test_1_State,
        Normal_Mapping_Test_2_State,
        Game_Test_State
    };

    class Game_State {
    public:

        virtual ~Game_State() = default;

        virtual std::vector<std::shared_ptr<aur::Object>> get_objects() {
            return _objects;
        }

        virtual void draw_loop_actions() {};

        std::shared_ptr<aur::SDLWindow> get_window() {
            return _window;
        }

        std::shared_ptr<aur::Scene> get_scene() {
            return _scene;
        }

        std::shared_ptr<aur::Camera> get_camera() {
            return _camera;
        }

    protected:
        std::vector<std::shared_ptr<aur::Object>> _objects;
        std::shared_ptr<aur::SDLWindow> _window;
        std::shared_ptr<aur::Scene> _scene;
        std::shared_ptr<aur::Camera> _camera;
    };
}

#endif
