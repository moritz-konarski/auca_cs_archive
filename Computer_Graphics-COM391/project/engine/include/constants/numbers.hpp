#ifndef NUMBERS_HPP
#define NUMBERS_HPP

namespace constant {
    static const int WINDOW_FULL_SCREEN{0};

    static const float CAMERA_SPEED{0.1f};
    static const float CAMERA_ROTATION_SPEED{0.05f};
    static const float CAMERA_SENSITIVITY_GAME{0.001f};
    static const float CAMERA_SPEED_GAME{0.28f};
    static const glm::vec4 CAMERA_FORWARD{0.0f, -0.001f, 1.0f, 0.0f};
    static const glm::vec4 CAMERA_LEFT{-1.0f, 0.0f, 0.0f, 0.0f};
    static const glm::vec4 CAMERA_RIGHT{1.0f, 0.0f, 0.0f, 0.0f};
}

#endif