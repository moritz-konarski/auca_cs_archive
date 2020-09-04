#ifndef HEAD_HPP
#define HEAD_HPP

#include "aur.hpp"
#include "constants.hpp"
#include "helpers.hpp"
#include "entity.hpp"
#include "enemy.hpp"

namespace game_characters {

    class Head : public Enemy {
    public:
        Head(glm::vec3 position, float scale)
                : Enemy(position, scale * 8.3f,
                        scale * 7.6f,
                        paths::HEAD_ENEMY_TEXTURE, 12,
                        3,
                        1, 8,
                        4, 2, 0, 1.0f) {
            _health_points = _full_health = 130;
            _damage_output = 3;
            _attack_distance = 8.0f;
        }
    };

}

#endif