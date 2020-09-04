//TODO: fix the constructors
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "aur.hpp"
#include "constants.hpp"
#include "helpers.hpp"

namespace game_characters {

    class Entity {
    public:
        virtual ~Entity() = default;

        virtual void move(glm::vec3 direction) {
            _mesh->add_to_position(direction * _stride_length);
        }

        virtual void set_position(glm::vec3 position) {
            _mesh->set_position(position);
        }

        virtual void gets_hurt(unsigned int damage) {
            _health_points -= damage;
            if (_health_points <= 0) {
                _is_dying = true;
            }
        }

        virtual bool is_dead() {
            return _is_dead;
        }

        virtual glm::vec3 get_position() {
            return _mesh->get_position();
        }

        virtual void attack() {}

        virtual bool is_attacking() {
            return _is_attacking;
        }

        virtual unsigned int get_damage() {
            return _damage_output;
        }

        std::shared_ptr<aur::Mesh> get_mesh() {
            return _mesh;
        }

        virtual void advance_animation() {}

    protected:
        bool _is_dead = false;
        bool _is_dying = false;
        bool _is_attacking = false;
        std::shared_ptr<aur::Mesh> _mesh;
        float _stride_length{0.3f};
        unsigned int _animation_texture_count, _animation_index{1};
        int _health_points, _damage_output;
        helper_functions::Mesh_Data _mesh_data;
    };
}

#endif
