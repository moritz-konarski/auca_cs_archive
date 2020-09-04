#ifndef IMGUI_HELPER_CPP
#define IMGUI_HELPER_CPP

#include <cstdio>

namespace helper_functions {

    void create_texture_box(std::string name, std::string number,
                            Texture_Data *texture_data,
                            glm::vec4 &diffuse_color, bool &plane_rotation_enabled) {
        std::string title{name + " Parameters "};
        std::string rotate{"Rotate##" + number};
        std::string emission_color{"Emission Color##" + number};
        std::string enabled{"Enabled##" + number};
        std::string texturing_mode{"Texturing Mode##" + number};
        std::string first_wrap_mode{"First Coordinate Wrap Mode##" + number};
        std::string second_wrap_mode{"Second Coordinate Wrap Mode##" + number};
        std::string magnification_filter{"Magnification Filter##" + number};
        std::string minification_filter{"Minification Filter##" + number};
        std::string enable_transformation_matrix{
                "Enable Transformation Matrix##" + number};
        std::string anisotropy{"Anisotropy##" + number};
        std::string mipmaps{"Use Mipmaps##" + number};
        int int_number;
        std::vector<std::string> string_vector;
        sscanf(number.c_str(), "%d", &int_number);
        for (int i = int_number; i < int_number + 4; ++i) {
            string_vector.emplace_back("##" + std::to_string(i));
        }

        if (ImGui::CollapsingHeader(title.c_str())) {
            ImGui::Checkbox(rotate.c_str(), &plane_rotation_enabled);
            ImGui::InputFloat4(emission_color.c_str(), glm::value_ptr(diffuse_color),
                               "%.2f");
            ImGui::Checkbox(enabled.c_str(), &texture_data->enabled);
            ImGui::Combo(texturing_mode.c_str(),
                         reinterpret_cast<int *>(&texture_data->texturing_mode),
                         "Addition\0Subtraction\0ReverseSubtraction\0Modulation\0Decaling\0");
            ImGui::Combo(first_wrap_mode.c_str(),
                         reinterpret_cast<int *>(&texture_data->wrap_mode_s),
                         "Repeat\0Mirrored Repeat\0Clamp To Edge\0");
            ImGui::Combo(second_wrap_mode.c_str(),
                         reinterpret_cast<int *>(&texture_data->wrap_mose_t),
                         "Repeat\0Mirrored Repeat\0Clamp To Edge\0");
            ImGui::Combo(magnification_filter.c_str(),
                         reinterpret_cast<int *>(&texture_data->magnification_filter_type),
                         "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            ImGui::Combo(minification_filter.c_str(),
                         reinterpret_cast<int *>(&texture_data->minification_filter_type),
                         "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            ImGui::Checkbox(enable_transformation_matrix.c_str(),
                            &texture_data->transformation_matrix_enabled);
            ImGui::InputFloat4(string_vector.at(0).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix),
                               "%.2f");
            ImGui::InputFloat4(string_vector.at(1).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix) +
                               4, "%.2f");
            ImGui::InputFloat4(string_vector.at(2).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix) +
                               8, "%.2f");
            ImGui::InputFloat4(string_vector.at(3).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix) +
                               12, "%.2f");
            ImGui::SliderInt(anisotropy.c_str(), &texture_data->anisotropy, 0, 16);
            ImGui::Checkbox(mipmaps.c_str(), &texture_data->mipmaps_enabled);
        }
    }

    void create_texture_box(std::string name, std::string number,
                            Texture_Data *texture_data) {
        std::string title{name + " Parameters "};
        std::string enabled{"Enabled##" + number};
        std::string texturing_mode{"Texturing Mode##" + number};
        std::string first_wrap_mode{"First Coordinate Wrap Mode##" + number};
        std::string second_wrap_mode{"Second Coordinate Wrap Mode##" + number};
        std::string magnification_filter{"Magnification Filter##" + number};
        std::string minification_filter{"Minification Filter##" + number};
        std::string enable_transformation_matrix{
                "Enable Transformation Matrix##" + number};
        std::string anisotropy{"Anisotropy##" + number};
        std::string mipmaps{"Use Mipmaps##" + number};
        int int_number;
        std::vector<std::string> string_vector;
        sscanf(number.c_str(), "%d", &int_number);
        int_number += (int_number - 1) * 4;
        for (int i = int_number; i < int_number + 4; ++i) {
            string_vector.emplace_back("##" + std::to_string(i));
        }

        if (ImGui::CollapsingHeader(title.c_str())) {
            ImGui::Checkbox(enabled.c_str(), &texture_data->enabled);
            ImGui::Combo(texturing_mode.c_str(),
                         reinterpret_cast<int *>(&texture_data->texturing_mode),
                         "Addition\0Subtraction\0ReverseSubtraction\0Modulation\0Decaling\0");
            ImGui::Combo(first_wrap_mode.c_str(),
                         reinterpret_cast<int *>(&texture_data->wrap_mode_s),
                         "Repeat\0Mirrored Repeat\0Clamp To Edge\0");
            ImGui::Combo(second_wrap_mode.c_str(),
                         reinterpret_cast<int *>(&texture_data->wrap_mose_t),
                         "Repeat\0Mirrored Repeat\0Clamp To Edge\0");
            ImGui::Combo(magnification_filter.c_str(),
                         reinterpret_cast<int *>(&texture_data->magnification_filter_type),
                         "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            ImGui::Combo(minification_filter.c_str(),
                         reinterpret_cast<int *>(&texture_data->minification_filter_type),
                         "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            ImGui::Checkbox(enable_transformation_matrix.c_str(),
                            &texture_data->transformation_matrix_enabled);
            ImGui::InputFloat4(string_vector.at(0).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix),
                               "%.2f");
            ImGui::InputFloat4(string_vector.at(1).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix) +
                               4, "%.2f");
            ImGui::InputFloat4(string_vector.at(2).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix) +
                               8, "%.2f");
            ImGui::InputFloat4(string_vector.at(3).c_str(),
                               glm::value_ptr(texture_data->transformation_matrix) +
                               12, "%.2f");
            ImGui::SliderInt(anisotropy.c_str(), &texture_data->anisotropy, 0, 16);
            ImGui::Checkbox(mipmaps.c_str(), &texture_data->mipmaps_enabled);
        }
    }

    void create_texture_and_normal_map_box(std::string name, std::string number,
                            Normal_Map_Data *normal_map_data) {
        std::string title{name + " Parameters "};
        std::string texture_enabled{"Texture Enabled##" + number};
        std::string normals_enabled{"Normals Enabled##" + number};
        std::string texturing_mode{"Texturing Mode##" + number};
        std::string first_wrap_mode{"First Coordinate Wrap Mode##" + number};
        std::string second_wrap_mode{"Second Coordinate Wrap Mode##" + number};
        std::string magnification_filter{"Magnification Filter##" + number};
        std::string minification_filter{"Minification Filter##" + number};
        std::string enable_transformation_matrix{
                "Enable Transformation Matrix##" + number};
        std::string anisotropy{"Anisotropy##" + number};
        std::string mipmaps{"Use Mipmaps##" + number};
        int int_number;
        std::vector<std::string> string_vector;
        sscanf(number.c_str(), "%d", &int_number);
        int_number += (int_number - 1) * 4;
        for (int i = int_number; i < int_number + 4; ++i) {
            string_vector.emplace_back("##" + std::to_string(i));
        }

        if (ImGui::CollapsingHeader(title.c_str())) {
            ImGui::Checkbox(texture_enabled.c_str(), &normal_map_data->texture_enabled);
            ImGui::Checkbox(normals_enabled.c_str(), &normal_map_data->normals_enabled);
            ImGui::Combo(texturing_mode.c_str(),
                         reinterpret_cast<int *>(&normal_map_data->texturing_mode),
                         "Addition\0Subtraction\0ReverseSubtraction\0Modulation\0Decaling\0");
            ImGui::Combo(first_wrap_mode.c_str(),
                         reinterpret_cast<int *>(&normal_map_data->wrap_mode_s),
                         "Repeat\0Mirrored Repeat\0Clamp To Edge\0");
            ImGui::Combo(second_wrap_mode.c_str(),
                         reinterpret_cast<int *>(&normal_map_data->wrap_mose_t),
                         "Repeat\0Mirrored Repeat\0Clamp To Edge\0");
            ImGui::Combo(magnification_filter.c_str(),
                         reinterpret_cast<int *>(&normal_map_data->magnification_filter_type),
                         "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            ImGui::Combo(minification_filter.c_str(),
                         reinterpret_cast<int *>(&normal_map_data->minification_filter_type),
                         "Nearest\0Linear\0Nearest Mipmap Nearest\0Nearest Mipmap Linear\0Linear Mipmap Nearest\0Linear Mipmap Linear\0");
            ImGui::Checkbox(enable_transformation_matrix.c_str(),
                            &normal_map_data->transformation_matrix_enabled);
            ImGui::InputFloat4(string_vector.at(0).c_str(),
                               glm::value_ptr(normal_map_data->transformation_matrix),
                               "%.2f");
            ImGui::InputFloat4(string_vector.at(1).c_str(),
                               glm::value_ptr(normal_map_data->transformation_matrix) +
                               4, "%.2f");
            ImGui::InputFloat4(string_vector.at(2).c_str(),
                               glm::value_ptr(normal_map_data->transformation_matrix) +
                               8, "%.2f");
            ImGui::InputFloat4(string_vector.at(3).c_str(),
                               glm::value_ptr(normal_map_data->transformation_matrix) +
                               12, "%.2f");
            ImGui::SliderInt(anisotropy.c_str(), &normal_map_data->anisotropy, 0, 16);
            ImGui::Checkbox(mipmaps.c_str(), &normal_map_data->mipmaps_enabled);
        }
    }

    void create_fog_box(std::string number, Fog_Data *data) {
        std::string enabled{"Enabled##" + number};
        if (ImGui::CollapsingHeader("Fog Parameters ")) {
            ImGui::Checkbox(enabled.c_str(), &data->enabled);
            ImGui::Combo(
                    "Fog Type", reinterpret_cast<int *>(&data->type),
                    "Linear\0Exp\0Exp2\0"
            );
            ImGui::Combo(
                    "Fog Depth", reinterpret_cast<int *>(&data->depth),
                    "Planar\0PlanarAbsolute\0Radial\0"
            );
            ImGui::InputFloat3("Fog Color", glm::value_ptr(data->color), "%.2f");
            ImGui::SliderFloat("Fog Near Plane", &data->near_plane, 0.01f, 100.0f);
            ImGui::SliderFloat("Fog Far Plane", &data->far_plane, 0.01f, 100.0f);
            ImGui::SliderFloat("Fog Density", &data->density, 0.01f, 1.0f);
        }
    }

    void
    create_material_box(std::string name, std::string number, Material_Data *data,
                        float &z_value) {
        std::string title{name + " Material Parameters "};
        std::string diffuse_color{"Diffuse Color##" + number};
        std::string specular_color{"Specular Color##" + number};
        std::string specular_exponent{"Specular Exponent##" + number};
        std::string emission_color{"Emission Color##" + number};
        std::string ambient_color{"Ambient Color##" + number};
        std::string blending_color{"Ambient Color##" + number};
        std::string z_val{"Z Value##" + number};
        std::string enable_depth_mask{"Enable Depth Mask##" + number};
        std::string enable_depth_test{"Enable Depth Test##" + number};
        std::string depth_test_function{"Depth Test Function##" + number};
        std::string enable_face_culling{"Enable Face Culling##" + number};
        std::string cull_face_mode{"Cull Face Mode##" + number};
        std::string front_face_order{"Front Face Order##" + number};
        std::string enable_blending{"Blending Enabled##" + number};
        std::string color_blending_equation{"Color Blending Equation##" + number};
        std::string alpha_blending_equation{"Alpha Blending Equation##" + number};
        std::string source_color_blending_function{
                "Source Color Blending Equation##" + number};
        std::string source_alpha_blending_function{
                "Source Alpha Blending Equation##" + number};
        std::string destination_color_blending_function{
                "Destination Color Blending Equation##" + number};
        std::string destination_alpha_blending_function{
                "Destination Alpha Blending Equation##" + number};

        if (ImGui::CollapsingHeader(title.c_str())) {
            ImGui::InputFloat4(diffuse_color.c_str(),
                               glm::value_ptr(data->diffuse_color), "%.2f");
            ImGui::InputFloat3(specular_color.c_str(),
                               glm::value_ptr(data->specular_color), "%.2f");
            ImGui::SliderFloat(specular_exponent.c_str(), &data->specular_exponent,
                               0.0f, 100.0f);
            ImGui::InputFloat4(emission_color.c_str(),
                               glm::value_ptr(data->emission_color), "%.2f");
            ImGui::InputFloat3(ambient_color.c_str(),
                               glm::value_ptr(data->ambient_color), "%.2f");
            ImGui::InputFloat4(blending_color.c_str(),
                               glm::value_ptr(data->blending_constant_color),
                               "%.2f");
            ImGui::SliderFloat(z_val.c_str(), &z_value, -20.0f, 20.0f);

            ImGui::Checkbox(enable_depth_mask.c_str(), &data->depth_mask_enabled);
            ImGui::Checkbox(enable_depth_test.c_str(), &data->depth_test_enabled);
            ImGui::Combo(depth_test_function.c_str(),
                         reinterpret_cast<int *>(&data->depth_test_function),
                         "Never\0Always\0Less\0Lower or Equal\0Equal\0Greater\0Greater or Equal\0Not Equal\0");

            ImGui::Checkbox(enable_face_culling.c_str(),
                            &data->face_culling_enabled);
            ImGui::Combo(cull_face_mode.c_str(),
                         reinterpret_cast<int *>(&data->cull_face_mode),
                         "Cull Front Faces\0Cull Back Faces\0Cull Front and Back Faces\0");
            ImGui::Combo(front_face_order.c_str(),
                         reinterpret_cast<int *>(&data->front_face_order),
                         "Clockwise\0Counterclockwise\0");

            ImGui::Checkbox(enable_blending.c_str(), &data->blending_enabled);
            ImGui::Combo(color_blending_equation.c_str(),
                         reinterpret_cast<int *>(&data->color_blending_equation),
                         "Addition\0Subtraction\0Reverse Subtraction\0");
            ImGui::Combo(alpha_blending_equation.c_str(),
                         reinterpret_cast<int *>(&data->alpha_blending_equation),
                         "Addition\0Subtraction\0Reverse Subtraction\0");
            ImGui::Combo(source_color_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->source_color_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");

            ImGui::Combo(source_alpha_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->source_alpha_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");

            ImGui::Combo(destination_color_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->destination_color_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");
            ImGui::Combo(destination_alpha_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->destination_alpha_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");
        }
    }

    void
    create_material_box(std::string name, std::string number,
                        Material_Data *data) {
        std::string title{name + " Material Parameters "};
        std::string diffuse_color{"Diffuse Color##" + number};
        std::string specular_color{"Specular Color##" + number};
        std::string specular_exponent{"Specular Exponent##" + number};
        std::string emission_color{"Emission Color##" + number};
        std::string ambient_color{"Ambient Color##" + number};
        std::string blending_color{"Ambient Color##" + number};
        std::string enable_depth_mask{"Enable Depth Mask##" + number};
        std::string enable_depth_test{"Enable Depth Test##" + number};
        std::string depth_test_function{"Depth Test Function##" + number};
        std::string enable_face_culling{"Enable Face Culling##" + number};
        std::string cull_face_mode{"Cull Face Mode##" + number};
        std::string front_face_order{"Front Face Order##" + number};
        std::string enable_blending{"Blending Enabled##" + number};
        std::string color_blending_equation{
                "Color Blending Equation##" + number};
        std::string alpha_blending_equation{
                "Alpha Blending Equation##" + number};
        std::string source_color_blending_function{
                "Source Color Blending Equation##" + number};
        std::string source_alpha_blending_function{
                "Source Alpha Blending Equation##" + number};
        std::string destination_color_blending_function{
                "Destination Color Blending Equation##" + number};
        std::string destination_alpha_blending_function{
                "Destination Alpha Blending Equation##" + number};

        if (ImGui::CollapsingHeader(title.c_str())) {
            ImGui::InputFloat4(diffuse_color.c_str(),
                               glm::value_ptr(data->diffuse_color), "%.2f");
            ImGui::InputFloat3(specular_color.c_str(),
                               glm::value_ptr(data->specular_color), "%.2f");
            ImGui::SliderFloat(specular_exponent.c_str(),
                               &data->specular_exponent,
                               0.0f, 100.0f);
            ImGui::InputFloat4(emission_color.c_str(),
                               glm::value_ptr(data->emission_color), "%.2f");
            ImGui::InputFloat3(ambient_color.c_str(),
                               glm::value_ptr(data->ambient_color), "%.2f");
            ImGui::InputFloat4(blending_color.c_str(),
                               glm::value_ptr(data->blending_constant_color),
                               "%.2f");

            ImGui::Checkbox(enable_depth_mask.c_str(),
                            &data->depth_mask_enabled);
            ImGui::Checkbox(enable_depth_test.c_str(),
                            &data->depth_test_enabled);
            ImGui::Combo(depth_test_function.c_str(),
                         reinterpret_cast<int *>(&data->depth_test_function),
                         "Never\0Always\0Less\0Lower or Equal\0Equal\0Greater\0Greater or Equal\0Not Equal\0");

            ImGui::Checkbox(enable_face_culling.c_str(),
                            &data->face_culling_enabled);
            ImGui::Combo(cull_face_mode.c_str(),
                         reinterpret_cast<int *>(&data->cull_face_mode),
                         "Cull Front Faces\0Cull Back Faces\0Cull Front and Back Faces\0");
            ImGui::Combo(front_face_order.c_str(),
                         reinterpret_cast<int *>(&data->front_face_order),
                         "Clockwise\0Counterclockwise\0");

            ImGui::Checkbox(enable_blending.c_str(), &data->blending_enabled);
            ImGui::Combo(color_blending_equation.c_str(),
                         reinterpret_cast<int *>(&data->color_blending_equation),
                         "Addition\0Subtraction\0Reverse Subtraction\0");
            ImGui::Combo(alpha_blending_equation.c_str(),
                         reinterpret_cast<int *>(&data->alpha_blending_equation),
                         "Addition\0Subtraction\0Reverse Subtraction\0");
            ImGui::Combo(source_color_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->source_color_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");

            ImGui::Combo(source_alpha_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->source_alpha_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");

            ImGui::Combo(destination_color_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->destination_color_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");
            ImGui::Combo(destination_alpha_blending_function.c_str(),
                         reinterpret_cast<int *>(&data->destination_alpha_blending_function),
                         "Zero\0One\0SourceColor\0OneMinusSourceColor\0DestinationColor\0OneMinusDestinationColor\0SourceAlpha\0OneMinusSourceAlpha\0"                    "DestinationAlpha\0OneMinusDestinationAlpha\0ConstantColor\0OneMinusConstantColor\0ConstantAlpha\0OneMinusConstantAlpha\0"                    "SourceAlphaSaturate\0");
        }
    }
}
#endif
