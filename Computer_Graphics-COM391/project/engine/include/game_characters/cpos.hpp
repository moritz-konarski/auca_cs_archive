#ifndef CPOS_HPP
#define CPOS_HPP

#include "aur.hpp"
#include "constants.hpp"
#include "helpers.hpp"
#include "entity.hpp"
#include "enemy.hpp"

namespace game_characters {

    class Cpos : public Enemy {
    public:
        Cpos(glm::vec3 position, float scale)
                : Enemy(position, scale * 5.1f,
                        scale * 5.6f,
                        paths::CPOS_ENEMY_TEXTURE, 14,
                        2, 4, 8, 6, 4, 0, 1.5f) {
            _health_points = _full_health = 200;
            _damage_output = 2;
            _attack_distance = 10.0f;
        }
    };


}

#endif