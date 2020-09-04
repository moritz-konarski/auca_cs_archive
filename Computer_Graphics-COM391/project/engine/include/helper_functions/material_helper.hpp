#ifndef MATERIAL_HELPER_HPP
#define MATERIAL_HELPER_HPP

namespace helper_functions {

    void set_phong_material_properties(std::shared_ptr<ES2PhongMaterial> material,
                                       Material_Data *data) {
        material->set_diffuse_color(data->diffuse_color);
        material->set_specular_color(data->specular_color);
        material->set_specular_exponent(data->specular_exponent);
        material->set_emission_color(data->emission_color);
        material->set_ambient_color(data->ambient_color);
        material->set_blending_constant_color(data->blending_constant_color);
        material->set_depth_mask_enabled(data->depth_mask_enabled);
        material->set_depth_test_enabled(data->depth_test_enabled);
        material->set_depth_test_function(data->depth_test_function);
        material->set_face_culling_enabled(data->face_culling_enabled);
        material->set_cull_face_mode(data->cull_face_mode);
        material->set_front_face_order(data->front_face_order);
        material->set_blending_enabled(data->blending_enabled);
        material->set_color_blending_equation(data->color_blending_equation);
        material->set_alpha_blending_equation(data->alpha_blending_equation);
        material->set_source_color_blending_function(
                data->source_alpha_blending_function);
        material->set_source_alpha_blending_function(
                data->source_alpha_blending_function);
        material->set_destination_color_blending_function(
                data->destination_color_blending_function);
        material->set_destination_alpha_blending_function(
                data->destination_alpha_blending_function);
    }

    void get_phong_material_properties(std::shared_ptr<ES2PhongMaterial> material,
                                       Material_Data *data) {
        data->diffuse_color = material->get_diffuse_color();
        data->specular_color = material->get_specular_color();
        data->specular_exponent = material->get_specular_exponent();
        data->emission_color = material->get_emission_color();
        data->ambient_color = material->get_ambient_color();
        data->blending_constant_color = material->get_blending_constant_color();
        data->depth_mask_enabled = material->is_depth_mask_enabled();
        data->depth_test_enabled = material->is_depth_test_enabled();
        data->depth_test_function = material->get_depth_test_function();
        data->face_culling_enabled = material->is_face_culling_enabled();
        data->cull_face_mode = material->get_cull_face_mode();
        data->front_face_order = material->get_front_face_order();
        data->blending_enabled = material->is_blending_enabled();
        data->color_blending_equation = material->get_color_blending_equation();
        data->alpha_blending_equation = material->get_alpha_blending_equation();
        data->source_color_blending_function = material->get_source_color_blending_function();
        data->source_alpha_blending_function = material->get_source_alpha_blending_function();
        data->destination_color_blending_function = material->get_destination_color_blending_function();
        data->destination_alpha_blending_function = material->get_destination_alpha_blending_function();
    }

    void
    set_material_fog_properties(std::shared_ptr<Material> material, Fog_Data *data) {
        material->set_fog_enabled(data->enabled);
        material->set_fog_type(data->type);
        material->set_fog_depth(data->depth);
        material->set_fog_color(data->color);
        material->set_fog_near_plane(data->near_plane);
        material->set_fog_far_plane(data->far_plane);
        material->set_fog_density(data->density);
    }

    std::shared_ptr<ES2PhongMaterial>
    create_normal_map_material(std::string texture_path, std::string normal_path) {
        auto material = std::make_shared<ES2PhongMaterial>();
        material->set_texture2_normal_map(true);

        auto texture = generate_texture(texture_path);
        material->set_texture_1(texture);

        auto normal_map = generate_texture(normal_path);
        material->set_texture_2(normal_map);

        return material;
    }
}
#endif
