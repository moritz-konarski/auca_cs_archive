#ifndef FPS_COUNTER_HPP
#define FPS_COUNTER_HPP

#include <chrono>

namespace helper_functions {

    unsigned int _prev_time = 0, _sum = 0, _index = 0;
    float _fps;

    unsigned int _get_time_ms() {
        return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
        ).count());
    }

    unsigned int _estimate_fps(unsigned int previous_time) {
        return static_cast<unsigned int>(1000.0f / (_get_time_ms() - previous_time));
    }

    void create_fps_counter(unsigned int x, unsigned int y) {
        _sum += _estimate_fps(_prev_time);
        _prev_time = _get_time_ms();

        if (_index == 12) {
            _fps = _sum / 12.0f;
            _index = _sum = 0;
        }
        ++_index;
        ImGui::SetNextWindowPos(ImVec2(x, y));
        ImGui::Begin("FPS", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            ImGui::SetWindowFontScale(1.3f);
            ImGui::Text(" %.1f ", _fps);
        }
        ImGui::End();
    }

    void show_position(glm::vec3 position) {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("FPS", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            ImGui::SetWindowFontScale(1.3f);
            ImGui::Text(" %.1f %.1f %.1f", position.x, position.y, position.z);
        }
        ImGui::End();
    }
}

#endif
