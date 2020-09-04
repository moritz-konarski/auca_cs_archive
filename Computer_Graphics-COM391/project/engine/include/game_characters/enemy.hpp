#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <utility>

#include "aur.hpp"
#include "constants.hpp"
#include "helpers.hpp"
#include "entity.hpp"

namespace game_characters {

    class Enemy : public Entity {
    public:
        Enemy(glm::vec3 position, float width, float height,
              std::string texture_path, unsigned int animation_texture_count,
              unsigned int attack_animation_count,
              unsigned int attack_animation_offset,
              unsigned int death_animation_count,
              unsigned int death_animation_offset, unsigned int idle_animation_count,
              unsigned int idle_animation_offset, float stride_length) {
            _animation_texture_count = animation_texture_count;
            _attack_animation_count = attack_animation_count;
            _attack_animation_offset = attack_animation_offset;
            _death_animation_count = death_animation_count;
            _death_animation_offset = death_animation_offset;
            _idle_animation_count = idle_animation_count;
            _idle_animation_offset = idle_animation_offset;
            _stride_length = stride_length;

            glm::vec3 temp_position = position;
            temp_position.y += height / 2.0f;

            _texture_data.transformation_matrix_enabled = true;
            _texture_data.transformation_matrix[0][0] =
                    1.0f / static_cast<float>(_animation_texture_count);

            _texture = helper_functions::generate_texture(std::move(texture_path));
            helper_functions::set_texture_attributes(_texture, &_texture_data);
            _material->set_texture_1(_texture);
            _material->set_blending_enabled(true);
            _material->set_face_culling_enabled(false);
            _material->set_transparent(true);
            _material->set_depth_test_enabled(true);
            _material->set_depth_test_function(aur::Material::DepthTestFunction::Less);

            _rectangle_data.width = width;
            _rectangle_data.height = height;
            _rectangle_data.height_segments_count = _rectangle_data.width_segments_count = 2;

            _mesh_data.material = _material;
            _mesh_data.name = "enemy";
            _mesh = helper_functions::generate_rectangle_mesh(_rectangle_data,
                                                              _mesh_data);

            _mesh->set_position(temp_position);
            _sphere = std::make_shared<aur::Sphere>(_mesh->get_position(),
                                                    (width + height) / 2.0f);
        }

        void wake_up() {
            if (!_was_killed) {
                _is_dead = false;
            }
        }

        std::shared_ptr<aur::ES2ConstantMaterial> get_material() {
            return _material;
        }

        std::shared_ptr<aur::Sphere> get_sphere() {
            return _sphere;
        }

        unsigned int get_damage() override {
            if (_is_shooting) {
                _is_shooting = false;
                return _damage_output;
            } else {
                return 0;
            }
        }

        void turn_towards_camera(const std::shared_ptr<aur::Camera> &camera) {
            _mesh->billboard_toward_camera(camera);
        }

        void attack(glm::vec3 player_position) {
            if (!_is_dying) {
                glm::vec3 vector = player_position - _mesh->get_position();
                glm::vec3 direction = glm::normalize(vector);
                if (glm::length(vector) < _attack_distance) {
                    _is_attacking = true;
                    _is_shooting = true;
                    _animation_index = _attack_animation_offset;
                } else {
                    move(direction);
                }
            }
        }

        void revive() {
            _is_dying = false;
            _is_dead = false;
            _was_killed = false;
            _health_points = _full_health;
        }

        void gets_hurt(unsigned int damage) override {
            _health_points -= damage;
            if (_health_points <= 0) {
                _is_dying = true;
                _animation_index = _death_animation_offset;
            }
        }

        void advance_animation() override {
            if (!_is_dead) {
                if (_is_attacking) {
                    ++_animation_index;
                    if (_animation_index >
                        _attack_animation_count + _attack_animation_offset) {
                        _animation_index = 1;
                        _is_attacking = false;
                    }
                } else if (_is_dying) {
                    ++_animation_index;
                    if (_animation_index >
                        _death_animation_offset + _death_animation_count) {
                        _animation_index =
                                _death_animation_count + _death_animation_offset;
                        _is_dead = true;
                        _was_killed = true;
                        _mesh->set_y(_rectangle_data.height / 2.0f);
                    }
                } else {
                    ++_animation_index;
                    if (_animation_index >
                        _idle_animation_offset + _idle_animation_count) {
                        _animation_index = 1;
                    }
                }
                _texture_data.transformation_matrix[0][3] =
                        static_cast<float>(_animation_index - 1) *
                        1.0f / static_cast<float>(_animation_texture_count);
                _texture->set_transformation_matrix(
                        _texture_data.transformation_matrix);
            }
        }

    protected:
        std::shared_ptr<aur::Sphere> _sphere;
        std::shared_ptr<aur::ES2Texture> _texture;
        helper_functions::Texture_Data _texture_data;
        std::shared_ptr<aur::ES2ConstantMaterial> _material =
                std::make_shared<aur::ES2ConstantMaterial>();
        unsigned int _attack_animation_count, _attack_animation_offset;
        unsigned int _death_animation_count, _death_animation_offset;
        unsigned int _idle_animation_count, _idle_animation_offset;
        helper_functions::Rectangle_Data _rectangle_data;
        bool _was_killed = false;
        bool _is_shooting = false;
        unsigned int _full_health;
        float _attack_distance;
    };
}

#endif
