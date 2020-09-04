#ifndef MOVEMENT_CONTROL_HPP
#define MOVEMENT_CONTROL_HPP

#include "aur.hpp"
#include "helpers.hpp"
#include "constants/numbers.hpp"
#include "game_characters/player.hpp"

namespace helper_functions {
    std::shared_ptr<aur::Camera> _camera_for_movement;
    std::shared_ptr<game_characters::Player> _player_for_movement;
    std::shared_ptr<aur::SDLWindow> _window_for_movement;
    std::shared_ptr<aur::Ray> _player_view_ray;

    std::shared_ptr<aur::Ray> get_player_view_ray() {
        return _player_view_ray;
    }

    void set_camera(std::shared_ptr<aur::Camera> camera) {
        _camera_for_movement = std::move(camera);
    }

    void set_player(std::shared_ptr<game_characters::Player> player) {
        _player_for_movement = std::move(player);
    }

    void set_window(std::shared_ptr<aur::SDLWindow> window) {
        _window_for_movement = std::move(window);
    }

    std::function<void(int)> process_keystrokes = [](int key) {
        switch (key) {
            case SDLK_w:
                _camera_for_movement->set_rotation_x(
                        _camera_for_movement->get_rotation_x() + constant::CAMERA_ROTATION_SPEED);
                break;
            case SDLK_a:
                _camera_for_movement->set_rotation_y(
                        _camera_for_movement->get_rotation_y() + constant::CAMERA_ROTATION_SPEED);
                break;
            case SDLK_s:
                _camera_for_movement->set_rotation_x(
                        _camera_for_movement->get_rotation_x() - constant::CAMERA_ROTATION_SPEED);
                break;
            case SDLK_d:
                _camera_for_movement->set_rotation_y(
                        _camera_for_movement->get_rotation_y() - constant::CAMERA_ROTATION_SPEED);
                break;
            case SDLK_e:
                _camera_for_movement->set_y(_camera_for_movement->get_y() + constant::CAMERA_ROTATION_SPEED);
                break;
            case SDLK_q:
                _camera_for_movement->set_y(_camera_for_movement->get_y() - constant::CAMERA_ROTATION_SPEED);
                break;
            case SDLK_UP:
                _camera_for_movement->set_position(_camera_for_movement->get_position() - glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_FORWARD *
                        constant::CAMERA_SPEED));
                break;
            case SDLK_DOWN:
                _camera_for_movement->set_position(_camera_for_movement->get_position() + glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_FORWARD *
                        constant::CAMERA_SPEED));
                break;
            case SDLK_LEFT:
                _camera_for_movement->set_position(_camera_for_movement->get_position() + glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_LEFT *
                        constant::CAMERA_SPEED));
                break;
            case SDLK_RIGHT:
                _camera_for_movement->set_position(_camera_for_movement->get_position() + glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_RIGHT *
                        constant::CAMERA_SPEED));
                break;
            case SDLK_ESCAPE:
                _camera_for_movement = NULL;
                exit(0);
            default:
                break;
        }
    };

    std::function<void(int)> process_keystrokes_game = [](int key) {
        switch (key) {
            case SDLK_w:
                _camera_for_movement->set_position(_camera_for_movement->get_position() - glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_FORWARD *
                        constant::CAMERA_SPEED_GAME));
                break;
            case SDLK_s:
                _camera_for_movement->set_position(_camera_for_movement->get_position() + glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_FORWARD *
                        constant::CAMERA_SPEED_GAME));
                break;
            case SDLK_a:
                _camera_for_movement->set_position(_camera_for_movement->get_position() + glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_LEFT *
                        constant::CAMERA_SPEED_GAME));
                break;
            case SDLK_d:
                _camera_for_movement->set_position(_camera_for_movement->get_position() + glm::vec3(
                        _camera_for_movement->get_model_matrix() * constant::CAMERA_RIGHT *
                        constant::CAMERA_SPEED_GAME));
                break;
            case SDLK_r:
                _player_for_movement->reload();
                break;
            case SDLK_ESCAPE:
                _camera_for_movement = nullptr;
                exit(0);
            default:
                break;
        }
    };

    std::function<void(int, int, int)> process_mouse_click = [](int button, int x,
                                                                int y) {
        if (button == SDL_BUTTON_LEFT) {
            _player_for_movement->attack();
            int cx = static_cast<int>(_window_for_movement->get_width() / 2);
            int cy = static_cast<int>(_window_for_movement->get_height() / 2);
            _player_view_ray = std::make_shared<aur::Ray>(
                    _camera_for_movement->world_ray_from_screen_point(cx, cy,
                                                         static_cast<int>(_window_for_movement->get_width()),
                                                         static_cast<int>(_window_for_movement->get_height())));
        }
    };

    std::function<void(int, int, int, int)> process_mouse_move = [](int x,
                                                                int y, int x_rel, int y_rel) {
        _camera_for_movement->add_to_rotation_y(static_cast<float>(-x_rel) * constant::CAMERA_SENSITIVITY_GAME);
    };

}

#endif
