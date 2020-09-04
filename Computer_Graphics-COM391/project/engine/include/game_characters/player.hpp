#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "aur.hpp"
#include "constants.hpp"
#include "helpers.hpp"
#include "entity.hpp"

namespace game_characters {

    class Player : public Entity {
    public:
        explicit Player(glm::vec3 position) {
            _position = position;
            _stride_length = 0.05f;
            _animation_texture_count = 10;
            _health_points = _full_health = 150;
            _damage_output = 100;

            _texture_data.transformation_matrix_enabled = true;
            _texture_data.transformation_matrix[0][0] =
                    1.0f / static_cast<float>(_animation_texture_count);
            _texture = helper_functions::generate_texture(paths::GUN_TEXTURE);
            helper_functions::set_texture_attributes(_texture, &_texture_data);
            _material->set_texture_1(_texture);
            _material->set_overlay(true);
            _material->set_blending_enabled(true);

            _mesh_data.material = _material;
            _mesh_data.position = _mesh_position;
            _mesh_data.name = "player";
            _mesh = helper_functions::generate_square_mesh(_square_data, _mesh_data);

            _sphere = std::make_shared<aur::Sphere>(_position, 0.9f);
        }

        void attack() override {
            if (!_is_dead) {
                if (_ammunition_count > 0) {
                    _is_attacking = true;
                    _is_shooting = true;
                    --_ammunition_count;
                    _empty_call_counter = 0;
                    _animation_index = _shoot_animation_offset;
                }
            }
        }

        void set_position(glm::vec3 position) override {
            _position = position;
        }

        void gets_hurt(unsigned int damage) override {
            if (!_is_dead) {
                _health_points -= damage;
                if (_health_points <= 0) {
                    _is_dying = true;
                }
            }
        }

        unsigned int get_max_health() {
            return _full_health;
        }

        int get_health() {
            return _health_points;
        }

        bool is_attacking() override {
            return _is_attacking;
        }

        unsigned int get_damage() override {
            if (_is_shooting) {
                _is_shooting = false;
                return _damage_output;
            } else {
                return 0;
            }
        }

        glm::vec3 get_position() override {
            return _position;
        }

        void reload() {
            if (!_is_dead) {
                _is_reloading = true;
                _animation_index = _reload_animation_offset;
            }
        }

        void move(glm::vec3 direction) override {
            _position += direction * _stride_length;
        }

        void advance_animation() override {
            // TODO: turn screen red to show death
            if (!_is_dead) {
                if (_is_attacking) {
                    ++_animation_index;
                    if (_animation_index >
                        _shoot_animation_count + _shoot_animation_offset) {
                        _animation_index = 1;
                        _is_attacking = false;
                    }
                    _texture_data.transformation_matrix[0][3] =
                            static_cast<float>(_animation_index - 1) *
                            1.0f / static_cast<float>(_animation_texture_count);
                    _texture->set_transformation_matrix(
                            _texture_data.transformation_matrix);
                } else if (_is_reloading) {
                    ++_animation_index;
                    if (_animation_index >
                        _reload_animation_count + _reload_animation_offset) {
                        _animation_index = 1;
                        _is_reloading = false;
                        _ammunition_count = _ammunition_max;
                    }
                    _texture_data.transformation_matrix[0][3] =
                            static_cast<float>(_animation_index - 1) *
                            1.0f / static_cast<float>(_animation_texture_count);
                    _texture->set_transformation_matrix(
                            _texture_data.transformation_matrix);
                } else if (_is_dying) {
                    _mesh->get_material()->set_fog_density(100.0f);
                    _is_dead = true;
                } else {
                    if (abs(_mesh->get_y() - _mesh_position.y) >
                        _idle_gun_movement) {
                        _idle_gun_movement_speed *= -1.0f;
                    }
                    _mesh->add_to_y(_idle_gun_movement_speed);
                }
            }
        }

    private:
        std::shared_ptr<aur::Sphere> _sphere;
        std::shared_ptr<aur::ES2Texture> _texture;
        helper_functions::Texture_Data _texture_data;
        std::shared_ptr<aur::ES2PhongMaterial> _material = std::make_shared<aur::ES2PhongMaterial>();
        glm::vec3 _position{};
        unsigned int _ammunition_count = 2, _ammunition_max = 2;
        unsigned int _reload_animation_count = 7, _reload_animation_offset = 1;
        unsigned int _shoot_animation_count = 2, _shoot_animation_offset = 8;
        helper_functions::Square_Data _square_data{5.0f, 1};
        bool _is_reloading = false;
        bool _is_shooting = false;
        float _idle_gun_movement = 0.02f;
        float _idle_gun_movement_speed = 0.006f;
        glm::vec3 _mesh_position{0.0f, -0.55f, 0.0f};
        unsigned int _full_health;
        int _empty_call_limit = 2;
        int _empty_call_counter = 0;
    };
}

#endif
