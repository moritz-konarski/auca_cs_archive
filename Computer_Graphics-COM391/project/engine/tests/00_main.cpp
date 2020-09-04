#include "aur.hpp"
#include "game_modules.hpp"

[[noreturn]]
int main(int argc, char **argv) {
    using namespace aur;
    game_modules::State state = game_modules::Geometry_Test_State;
    std::shared_ptr<game_modules::Game_State> game_state;
    bool state_changed = true;
    //game_state = std::shared_ptr<game_modules::Window_Test>();

menu_choice:
    if (state_changed) {
        state_changed = false;
        switch (state) {
            case game_modules::Menu_State:
                break;
            case game_modules::Window_Test_State:
                game_state = std::make_shared<game_modules::Window_Test>();
                break;
            case game_modules::Triangle_Test_State:
                game_state = std::make_shared<game_modules::Triangle_Test>();
                break;
            case game_modules::Geometry_Test_State:
                //game_state = NULL;
                game_state = std::make_shared<game_modules::Geometry_Test>();
                break;
            case game_modules::Scene_Graph_Test_State:
                break;
            case game_modules::Light_Test_1_State:
                break;
            case game_modules::Light_Test_2_State:
                break;
            case game_modules::Texture_Test_State:
                break;
            case game_modules::Textured_Plane_Test_State:
                break;
            case game_modules::Material_Properties_Test_State:
                break;
            case game_modules::Normal_Mapping_Test_1_State:
                break;
            case game_modules::Normal_Mapping_Test_2_State:
                break;
            case game_modules::Game_Test_State:
                break;
        }
    }

    game_modules::State old_state;
    ES2Renderer renderer(game_state->get_scene(), game_state->get_window());
    for (;;) {
        game_state->get_window()->poll();

        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::Begin("Parameters", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoMove);
        {
            if ("Chose Menu") {
                old_state = state;
                ImGui::Checkbox("Was Changed", &state_changed);
                ImGui::Combo("Choose Game State",
                             reinterpret_cast<int *>(&state),
                             "Menu\0Window Test\0Triangle Test\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            }
        }
        ImGui::End();

        game_state->draw_loop_actions();
        renderer.render();

        if (state_changed || old_state != state) {
            break;
            goto loop_end;
        }
    }
    loop_end:
        goto menu_choice;
}
