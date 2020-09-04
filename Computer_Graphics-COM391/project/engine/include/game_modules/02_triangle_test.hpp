#ifndef TRIANGLE_TEST_HPP
#define TRIANGLE_TEST_HPP

#include "constants.hpp"
#include "helpers.hpp"
#include "game_modules.hpp"

namespace game_modules {
    class Triangle_Test : public Game_State {

    public:
        Triangle_Test() {
            using namespace helper_functions;
            _window = std::make_shared<SDLWindow>(_title,
                                                  constant::WINDOW_FULL_SCREEN,
                                                  constant::WINDOW_FULL_SCREEN);

            auto constant_material = std::make_shared<ES2ConstantMaterial>();

            Triangle_Data triangle_data = {_triangle_size};
            Mesh_Data triangle_mesh_data = {constant_material, _color_array,
                                            _triangle_name};

            _triangle = generate_triangle_mesh(triangle_data, triangle_mesh_data);

            _objects.push_back(_triangle);

            _scene = std::make_shared<Scene>(_objects);
            _camera = _scene->get_camera();
            _camera->set_z(_camera_z);

            helper_functions::set_camera(_camera);
            _window->set_on_key_down(process_keystrokes);
        }

        void draw_loop_actions() override {
            _triangle->add_to_rotation_z(_triangle_rotation_speed);
        };

    private:
        std::shared_ptr<aur::Mesh> _triangle;

        constexpr static const float _camera_z{5.0f};
        constexpr static const float _triangle_rotation_speed{0.02f};
        constexpr static const float _triangle_size{2.5f};

        std::string _title{"triangle test"};
        std::string _triangle_name{"triangle"};
        std::vector<glm::vec4> _color_array{{color::RED},
                                            {color::GREEN},
                                            {color::BLUE}};
    };
}

#endif
