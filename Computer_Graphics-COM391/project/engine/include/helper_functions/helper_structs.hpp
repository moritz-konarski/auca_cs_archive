#ifndef MESH_DATA_HPP
#define MESH_DATA_HPP

#include "constants.hpp"

namespace helper_functions {
    using namespace aur;

    struct Mesh_Data {
        std::shared_ptr<Material> material;
        std::vector<glm::vec4> color_array{color::WHITE};
        std::string name{"mesh"};
        Geometry::Type geometry_type{Geometry::Type::Triangles};
        glm::vec3 position{0.0f};
    };

    struct Triangle_Data {
        float size{1.0f};
    };

    struct Rectangle_Data {
        float width{1.0f};
        float height{1.0f};
        unsigned int width_segments_count{5};
        unsigned int height_segments_count{5};
    };

    struct Square_Data {
        float side_length{1.0f};
        unsigned int segment_count{5};
    };

    struct Circle_Data {
        float radius{1.0f};
        unsigned int segment_count{36};
    };

    struct Sphere_Data {
        float radius{1.0f};
        unsigned int segment_count{36};
        unsigned int ring_count{12};
    };

    struct Texture_Data {
        bool enabled{true};
        Texture::Mode texturing_mode{Texture::Mode::Modulation};
        Texture::FilterType magnification_filter_type{Texture::FilterType::Nearest};
        Texture::FilterType minification_filter_type{Texture::FilterType::Nearest};
        Texture::WrapMode wrap_mode_s{Texture::WrapMode::Repeat};
        Texture::WrapMode wrap_mose_t{Texture::WrapMode::Repeat};
        bool transformation_matrix_enabled{false};
        glm::mat4 transformation_matrix{1.0f};
        int anisotropy{0};
        bool mipmaps_enabled{true};
    };

    struct Normal_Map_Data{
        bool texture_enabled{true};
        bool normals_enabled{true};
        Texture::Mode texturing_mode{Texture::Mode::Modulation};
        Texture::FilterType magnification_filter_type{Texture::FilterType::Nearest};
        Texture::FilterType minification_filter_type{Texture::FilterType::Nearest};
        Texture::WrapMode wrap_mode_s{Texture::WrapMode::Repeat};
        Texture::WrapMode wrap_mose_t{Texture::WrapMode::Repeat};
        bool transformation_matrix_enabled{false};
        glm::mat4 transformation_matrix{1.0f};
        int anisotropy{0};
        bool mipmaps_enabled{true};
    };

    struct Point_Light_Data {
        float intensity = 1.0f;
        glm::vec3 position{0.0f};
        bool is_two_sided{true};
        glm::vec3 color{1.0f};
    };

    struct Material_Data {
        glm::vec4 diffuse_color;
        glm::vec3 specular_color;
        float specular_exponent;
        glm::vec4 emission_color;
        glm::vec3 ambient_color;
        glm::vec4 blending_constant_color;
        bool depth_mask_enabled;
        bool depth_test_enabled;
        Material::DepthTestFunction depth_test_function;
        bool face_culling_enabled;
        Material::CullFaceMode cull_face_mode;
        Material::FrontFaceOrder front_face_order;
        bool blending_enabled;
        Material::BlendingEquation color_blending_equation;
        Material::BlendingEquation alpha_blending_equation;
        Material::BlendingFunction source_color_blending_function;
        Material::BlendingFunction source_alpha_blending_function;
        Material::BlendingFunction destination_color_blending_function;
        Material::BlendingFunction destination_alpha_blending_function;
    };

    struct Fog_Data {
        bool enabled{false};
        Material::FogType type{Material::FogType::Linear};
        Material::FogDepth depth{Material::FogDepth::Planar};
        glm::vec3 color{1.0f};
        float near_plane{1.0f};
        float far_plane{100.0f};
        float density{0.00042f};
    };
}

#endif