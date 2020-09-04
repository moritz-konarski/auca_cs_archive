#ifndef SPAWN_ENEMIES_HPP
#define SPAWN_ENEMIES_HPP

#include "aur.hpp"
#include <cstdlib>

namespace helper_functions {
    float random_number(float min, float max) {
        int range = max - min;
        double random = rand() % 1000000 / 1000000.0f;
        return (min > 0) ? static_cast<float>(random * range - min) : static_cast<float>(
                random * range + min);
    }

    glm::vec3 generate_random_glm_vec3(float min, float max) {
        return glm::vec3(random_number(min, max), 0.0f,
                         random_number(min, max));
    }

    unsigned int random_enemy_type(int enemy_count) {
        return static_cast<unsigned int>(random_number(-0.3f, enemy_count));
    }
}

#endif
