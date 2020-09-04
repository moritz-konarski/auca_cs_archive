#ifndef TEXTURE_GENERATORS_HPP
#define TEXTURE_GENERATORS_HPP

#include "aur.hpp"

namespace helper_functions {
    using namespace aur;

    std::shared_ptr<ES2Texture> generate_texture(const std::string image_path) {

        auto[image_data, image_width, image_height, image_channels] = file_utilities::read_image_file(
                image_path);
        return std::make_shared<ES2Texture>(image_data, image_width, image_height,
                                            image_channels);
    }

    void
    set_texture_attributes(std::shared_ptr<ES2Texture> texture, Texture_Data *data) {
        texture->set_enabled(data->enabled);
        texture->set_mode(data->texturing_mode);
        texture->set_wrap_mode_s(data->wrap_mode_s);
        texture->set_wrap_mode_t(data->wrap_mose_t);
        texture->set_magnification_filter(data->magnification_filter_type);
        texture->set_minification_filter(data->minification_filter_type);
        texture->set_transformation_enabled(data->transformation_matrix_enabled);
        texture->set_transformation_matrix(data->transformation_matrix);
        texture->set_anisotropy(static_cast<float>(data->anisotropy));
        texture->set_mipmaps_enabled(data->mipmaps_enabled);
    };

    void
    set_texture_attributes(std::shared_ptr<ES2Texture> texture, Normal_Map_Data data,
                           bool is_normal) {
        if (is_normal) {
            texture->set_enabled(data.normals_enabled);
        } else {
            texture->set_enabled(data.texture_enabled);
        }
        texture->set_mode(data.texturing_mode);
        texture->set_wrap_mode_s(data.wrap_mode_s);
        texture->set_wrap_mode_t(data.wrap_mose_t);
        texture->set_magnification_filter(data.magnification_filter_type);
        texture->set_minification_filter(data.minification_filter_type);
        texture->set_transformation_enabled(data.transformation_matrix_enabled);
        texture->set_transformation_matrix(data.transformation_matrix);
        texture->set_anisotropy(static_cast<float>(data.anisotropy));
        texture->set_mipmaps_enabled(data.mipmaps_enabled);
    };

    void set_normal_map_attributes(std::shared_ptr<ES2PhongMaterial> material,
                                   Normal_Map_Data data) {
        set_texture_attributes(material->get_texture_1(), data, false);
        set_texture_attributes(material->get_texture_2(), data, true);
        material->set_texture2_normal_map(data.normals_enabled);
    };

    glm::mat4 get_scale_matrix(float scale) {
        glm::mat4 matrix{1.0f};
        matrix[0][0] = scale;
        matrix[1][1] = scale;
        return matrix;
    }

    glm::mat4 get_scale_matrix_x(float scale) {
        glm::mat4 matrix{1.0f};
        matrix[0][0] = scale;
        return matrix;
    }

    glm::mat4 get_scale_matrix_y(float scale) {
        glm::mat4 matrix{1.0f};
        matrix[1][1] = scale;
        return matrix;
    }
}
#endif